/******************************************************************************
  NovaOS
******************************************************************************/

#ifndef __NOVAOS_GPIO_H__
#define __NOVAOS_GPIO_H__

#include "io.h"

#define GPIO_BASE IO_BASE + 0x200000

#define GPFSEL0         ((volatile unsigned int*)(GPIO_BASE+0x00))
#define GPFSEL1         ((volatile unsigned int*)(GPIO_BASE+0x04))
#define GPFSEL2         ((volatile unsigned int*)(GPIO_BASE+0x08))
#define GPFSEL3         ((volatile unsigned int*)(GPIO_BASE+0x0C))
#define GPFSEL4         ((volatile unsigned int*)(GPIO_BASE+0x10))
#define GPFSEL5         ((volatile unsigned int*)(GPIO_BASE+0x14))

#define GPPUD           ((volatile unsigned int*)(GPIO_BASE+0x94))
#define GPPUDCLK0       ((volatile unsigned int*)(GPIO_BASE+0x98))
#define GPPUDCLK1       ((volatile unsigned int*)(GPIO_BASE+0x9c))

#endif
