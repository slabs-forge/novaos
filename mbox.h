/******************************************************************************
  NovaOS
******************************************************************************/

#ifndef __NOVAOS_MBOX_H__
#define __NOVAOS_MBOX_H__

#define MBOX_CHANNEL_PROP 8

#define MBOX_TAG_GETCLKRATE   0x30002
#define MBOX_TAG_END          0X00000

void mbox_test();

void mbox_call(unsigned int channel,unsigned int *data);

#endif
