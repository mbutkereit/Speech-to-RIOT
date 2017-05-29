/*
 * Copyright (c) 2015-2016 Ken Bannister. All rights reserved.
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       gcoap example
 *
 * @author      Ken Bannister <kb2ma@runbox.com>
 *
 * @}
 */

#include <stdio.h>
#include "msg.h"

#include "net/gcoap.h"
#include "kernel_types.h"
#include "shell.h"
#include "xtimer.h"
#include "tmp006.h"

#include "periph_conf.h"
#include "periph/gpio.h"
#include "board.h"

#define MAIN_QUEUE_SIZE (4)
#define ENABLE_DEBUG 1

static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];

extern int gcoap_cli_cmd(int argc, char **argv);
extern void gcoap_cli_init(void);

static const shell_command_t shell_commands[] = {
    { "coap", "CoAP example", gcoap_cli_cmd },
    { NULL, NULL, NULL }
};

int temperature_value = 0;
char stack[THREAD_STACKSIZE_MAIN];

void *thread_handler(void *arg)
{
      tmp006_t dev;
      int16_t rawtemp, rawvolt;
      float tamb, tobj;
      uint8_t drdy;

      printf("Initializing TMP006 sensor at I2C_%i... ", TEST_TMP006_I2C);
      if (tmp006_init(&dev, TEST_TMP006_I2C, TEST_TMP006_ADDR, TEST_TMP006_CONFIG_CR) == 0) {
          puts("[OK]\n");
      }
      else {
          puts("[Failed]");
          return NULL;
      }

      if (tmp006_set_active(&dev)) {
          puts("Measurement start failed.");
          return NULL;
      }

      while (1) {
      tmp006_read(&dev, &rawvolt, &rawtemp, &drdy);
      tmp006_convert(rawvolt, rawtemp,  &tamb, &tobj);
      //printf("Data Tabm: %d   Tobj: %d\n", (int)(tamb*100), (int)(tobj*100));
      temperature_value = (int)(tobj*100);
      xtimer_usleep(TMP006_CONVERSION_TIME);
  }
    return NULL;
}


int main(void)
{
    /* for the thread running the shell */
    msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);
    gcoap_cli_init();
    thread_create(stack, sizeof(stack),
                    THREAD_PRIORITY_MAIN - 1,
                    THREAD_CREATE_STACKTEST,
                    thread_handler,
                    NULL, "thread");
    puts("gcoap example app");

    /* start shell */
    puts("All up, running the shell now");
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    /* should never be reached */
    return 0;
}
