#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kprobes.h>
#include <linux/ktime.h>
#include <linux/limits.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/printk.h>       // pr_info

#include "hook.h"

unsigned long hook_func = 0;
module_param(hook_func, ulong, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);

unsigned long audit_counter = 0;
module_param(audit_counter, ulong, S_IRUSR | S_IRGRP | S_IROTH);


MODULE_AUTHOR("Stefano Carnà <stefano.carna.dev@gmail.com>");
MODULE_DESCRIPTION("This module will execute a specified function \
	just after the task switch completion");

/*
 * Pre-execution function hanlder: this executes before the probed function
 */
// static int pre_handler(struct kretprobe_instance *ri, struct pt_regs *regs)
// {
// 	return 0;
// }// pre_handler

/*
 * Post-execution function hanlder: this perfoms the function whose address
 * is contained in the hook_func variable.
 */
static int post_handler(struct kretprobe_instance *ri, struct pt_regs *regs)
{
	h_func *hook;
	audit_counter ++;
	if (!hook_func) goto end;

	hook = (h_func*) hook_func;
	// Execute the function
	hook();

end:
	return 0;
}// post_handler

static struct kretprobe krp = {
	.handler                = post_handler,
	// .entry_handler          = pre_handler,
	// This should be set by default to 2 * NR_CPUS
	// .maxactive
};

static int __init hook_init(void)
{
	int ret;

	krp.kp.symbol_name = switch_func;
	ret = register_kretprobe(&krp);
	if (ret < 0) {
		pr_info("hook init failed, returned %d\n", ret);
		return ret;
	}
	pr_info("hook module correctly loaded\n");
	
	return 0;
}// hook_init

static void __exit hook_exit(void)
{
	unregister_kretprobe(&krp);

	pr_info("Hook invoked %lu times\n", audit_counter);
	/* nmissed > 0 suggests that maxactive was set too low. */
	if (krp.nmissed) pr_info("Missed %u invocations\n", krp.nmissed);

	pr_info("hook module unloaded\n");
}// hook_exit

module_init(hook_init)
module_exit(hook_exit)
MODULE_LICENSE("GPL");