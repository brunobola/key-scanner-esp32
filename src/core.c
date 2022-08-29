#include "core.h"

#include <zephyr/zephyr.h>
#include <zephyr/sys/printk.h>

/* size of stack area used by each thread */
#define STACKSIZE 1024

/* scheduling priority used by each thread */
#define PRIORITY 7

/* string concatenation magic macros */
#define STR_(X) #X
#define STR(X) STR_(X)

/* queue to store up to 10 messages (aligned to 4-byte boundary) */
K_MSGQ_DEFINE(core_msgq, PLD_SIZE, 1, 4);

/* core thread method declaration  for K_THREAD_DEFINE macro */
void core(void);

K_THREAD_DEFINE(core_id, STACKSIZE, core, NULL, NULL, NULL,
                PRIORITY, 0, 0);

void core(void) {
    static unsigned int cnt = 0;
    char buf[PLD_SIZE];
    /* indefinitely wait for input from the user */
    while (k_msgq_get(&core_msgq, &buf, K_FOREVER) == 0) {
        printk("payload(%i): %." STR(PLD_SIZE) "s\n", cnt++, buf);
    }
}
