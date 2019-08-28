/******************************************************************************
  NovaOS
******************************************************************************/

#include "uart0.h"
#include "mbox.h"

#include "assembly.h"

unsigned int  uart0_get_clock_rate();

/**
 * Get Clock Rate for the uart0
 */
unsigned int uart0_get_clock_rate() {
  unsigned int __attribute__((aligned(16))) buffer[8];

  buffer[0] = sizeof(buffer);
  buffer[1] = 0X00000000;
  buffer[2] = MBOX_TAG_GETCLKRATE;
  buffer[3] = 0x00000008;
  buffer[4] = 0x00000000;
  // Clock #2
  buffer[5] = 0x00000002;
  buffer[6] = 0x00000000;
  buffer[7] = 0x00000000;

  mbox_call(MBOX_CHANNEL_PROP,buffer);

  return buffer[6];
}

/**
 * Initialize the UART0
 */
void uart0_init() {
  unsigned int clk = uart0_get_clock_rate();

  nop();
}
