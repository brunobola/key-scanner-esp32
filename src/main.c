#include <string.h>
#include <zephyr/zephyr.h>
#include <zephyr/sys/printk.h>
#include <zephyr/console/console.h>

#include "core.h"

void main(void) {
    printk("Starting key-scanner-esp32 for board %s.\n", CONFIG_BOARD);

    console_getline_init();

    while (1) {
        printk("Enter code payload: ");
        char *s = console_getline();
        /* if queue is full, message is silently dropped */
        k_msgq_put(&core_msgq, s, K_NO_WAIT);
        k_msleep(500);
    }
}

