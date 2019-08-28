/******************************************************************************
  NovaOS
******************************************************************************/

#include "kernel.h"
#include "assembly.h"
#include "mbox.h"

#define IO_MBOX_BASE     (IO_BASE + 0xb880)

#define IP_MBOX_READ     ((volatile unsigned int*)(IO_MBOX_BASE + 0x00))
#define IP_MBOX_STATUS   ((volatile unsigned int*)(IO_MBOX_BASE + 0x18))
#define IP_MBOX_WRITE    ((volatile unsigned int*)(IO_MBOX_BASE + 0x20))

#define MBOX_STATUS_EMPTY   0x40000000
#define MBOX_STATUS_FULL    0x80000000

unsigned int __attribute__((aligned(16))) buffer[36];

void mbox_test() {
  buffer[0] = 32;
  buffer[1] = 0X00000000;
  buffer[2] = 0x00030002;
  buffer[3] = 0x00000008;
  buffer[4] = 0x00000000;
  buffer[5] = 0x00000002;
  buffer[6] = 0x00000000;
  buffer[7] = 0x00000000;

  mbox_call(MBOX_CHANNEL_PROP,buffer);
}

void mbox_debug() {

}

void mbox_call(unsigned int channel,unsigned int* data) {
  unsigned long r = ((unsigned long) data  & 0xfffffff0) | (channel & 0x0000000f);

  // Wait for write availability
  while (*IP_MBOX_STATUS & MBOX_STATUS_FULL) nop();

  // Write to MBox
  *IP_MBOX_WRITE = r;

  for(;;) {
    while (*IP_MBOX_STATUS & MBOX_STATUS_EMPTY) nop();

    if (*IP_MBOX_READ == r) break;
  }
  mbox_debug();
}
