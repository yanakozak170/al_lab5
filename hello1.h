// SPDX-License-Identifier: GPL-2.0 OR BSD-3-Clause
#ifndef HELLO1_H
#define HELLO1_H

#include <linux/list.h>
#include <linux/ktime.h>

struct hello_event {
    struct list_head list;
    ktime_t time;
};

void print_hello(uint count);
void cleanup_list(void);

#endif /* HELLO1_H */

