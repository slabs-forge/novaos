/******************************************************************************
  NovaOS
******************************************************************************/

#include "kernel.h"
#include "assembly.h"

#include "io.h"
#include "mbox.h"

#define IO_MBOX_BASE     (IO_BASE + 0xb880)

#define IP_MBOX_READ     ((volatile uint32_t*)(IO_MBOX_BASE + 0x00))
#define IP_MBOX_STATUS   ((volatile uint32_t*)(IO_MBOX_BASE + 0x18))
#define IP_MBOX_WRITE    ((volatile uint32_t*)(IO_MBOX_BASE + 0x20))

#define MBOX_STATUS_EMPTY   0x40000000
#define MBOX_STATUS_FULL    0x80000000

uint32_t __attribute__((aligned(16))) buffer[36];

/**
 * MAILBOX Call ARM->cpu
 * channel  : channel to use
 * data     : pointer to the mailbox message
 */
void mbox_call(uint32_t channel,uint32_t* data) {
  unsigned long r = ((unsigned long) data  & 0xfffffff0) | (channel & 0x0000000f);

  // Wait for write availability
  while (*IP_MBOX_STATUS & MBOX_STATUS_FULL) nop();

  // Write to MBox
  *IP_MBOX_WRITE = r;

  for(;;) {
    while (*IP_MBOX_STATUS & MBOX_STATUS_EMPTY) nop();

    if (*IP_MBOX_READ == r) break;
  }
}
