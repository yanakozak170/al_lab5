// SPDX-License-Identifier: GPL-2.0 OR BSD-3-Clause

#include <linux/module.h>
#include <linux/moduleparam.h>
#include "hello1.h"

static uint print_count = 1;
module_param(print_count, uint, 0444);
MODULE_PARM_DESC(print_count, "Number of times to print 'Hello, world!'");

static int __init hello2_init(void)
{
	if (print_count == 0 || (print_count >= 5 && print_count <= 10)) {
		pr_warn("Warning: Parameter value is %u, but continuing.\n",
			print_count);
	} else if (print_count > 10) {
		pr_err("Error: Parameter value %u is too large. Module not loaded.\n",
			print_count);
		return -EINVAL;
	}

	print_hello(print_count);
	return 0;
}

static void __exit hello2_exit(void)
{
	pr_info("Goodbye from hello2!\n");
}

module_init(hello2_init);
module_exit(hello2_exit);

MODULE_AUTHOR("Serhii Popovych <serhii.popovych@globallogic.com>");
MODULE_DESCRIPTION("Hello2 module");
MODULE_LICENSE("Dual BSD/GPL");

