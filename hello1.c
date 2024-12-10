// SPDX-License-Identifier: GPL-2.0 OR BSD-3-Clause
#include <linux/module.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/ktime.h>
#include "hello1.h"

static LIST_HEAD(hello_list);

void print_hello(uint count)
{
	uint i;
	struct hello_event *event;

	for (i = 0; i < count; i++) {
		event = kmalloc(sizeof(*event), GFP_KERNEL);
		event->time = ktime_get();
		list_add_tail(&event->list, &hello_list);

		pr_info("Hello, world! #%u\n", i + 1);
	}
}
EXPORT_SYMBOL(print_hello);

void cleanup_list(void)
{
	struct hello_event *event, *tmp;

	list_for_each_entry_safe(event, tmp, &hello_list, list) {
		pr_info("Event time: %llu ns\n", ktime_to_ns(event->time));
		list_del(&event->list);
		kfree(event);
	}
}
EXPORT_SYMBOL(cleanup_list);

static void __exit hello1_exit(void)
{
	cleanup_list();
	pr_info("Goodbye from hello1!\n");
}

module_exit(hello1_exit);

MODULE_AUTHOR("Serhii Popovych <serhii.popovych@globallogic.com>");
MODULE_DESCRIPTION("Hello1 module");
MODULE_LICENSE("Dual BSD/GPL");

