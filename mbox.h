/******************************************************************************
  NovaOS
******************************************************************************/

#ifndef __NOVAOS_MBOX_H__
#define __NOVAOS_MBOX_H__

#include "types.h"

#define MBOX_CHANNEL_PROP 8

#define MBOX_TAG_GETCLKRATE     0x30002
#define MBOX_TAG_GETMAXCLKRATE  0x30004
#define MBOX_TAG_SETCLKRATE     0x38002

#define MBOX_TAG_END          0X00000

void mbox_call(uint32_t channel,uint32_t *data);

#endif
