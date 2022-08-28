#include <string.h>
#include <zephyr/zephyr.h>
#include <zephyr/sys/printk.h>
#include <zephyr/console/console.h>

extern struct k_msgq core_msgq;

void main(void) {
    printk("Starting key-scanner-esp32 for board %s.\n", CONFIG_BOARD);

    console_getline_init();

    printk("Enter code payload\n");

    while (1) {
        char *s = console_getline();
        /* if queue is full, message is silently dropped */
        k_msgq_put(&core_msgq, s, K_NO_WAIT);
    }
}

