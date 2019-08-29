/******************************************************************************
  NovaOS
******************************************************************************/

#include "kernel.h"
#include "assembly.h"

#include "io.h"
#include "gpio.h"
#include "uart0.h"
#include "mbox.h"

// 4MHZ Cloack
#define UART0_CLK_HZ 4000000

#define UART0_BASE (IO_BASE + 0x00201000)

#define UART0_DR    ((volatile uint32_t*)UART0_BASE + 0x00)
#define UART0_IBRD  ((volatile uint32_t*)UART0_BASE + 0x24)
#define UART0_FBRD  ((volatile uint32_t*)UART0_BASE + 0x28)
#define UART0_LCRH  ((volatile uint32_t*)UART0_BASE + 0x2c)
#define UART0_CR    ((volatile uint32_t*)UART0_BASE + 0x30)
#define UART0_ICR   ((volatile uint32_t*)UART0_BASE + 0x44)

void uart0_set_clock_rate(uint32_t hz);


void uart0_set_clock_rate(uint32_t hz) {
  uint32_t __attribute__((aligned(16))) buffer[9];
  buffer[0] = sizeof(buffer);
  buffer[1] = 0X00000000;
  buffer[2] = MBOX_TAG_SETCLKRATE;
  buffer[3] = 0x0000000c;
  buffer[4] = 0x00000000;
  // Clock #2
  buffer[5] = 0x00000002;
  buffer[6] = hz;
  buffer[7] = 0x00000000;
  buffer[8] = 0x00000000;

  mbox_call(MBOX_CHANNEL_PROP,buffer);
}

/**
 * Initialize the UART0
 */
void uart0_init() {
  uint32_t val;

  // Disable the UART
  *UART0_CR = 0;

  // Set the clock rate to 4Mhz
  uart0_set_clock_rate(400000);

  // GPIO Setup
  val = *GPFSEL1;
  val &=  ~((0x7<<12)|(0x7<<15));
  val |=   ((0x4<<12)|(0x4<<15));
  *GPFSEL1 = val;

  *GPPUD = 0;
  // Delay
  for (uint32_t i = 0 ; i < 150 ; i++) nop();
  *GPPUDCLK0 = (1 << 14) | (1 << 15);
  for (uint32_t i = 0 ; i < 150 ; i++) nop();
  *GPPUDCLK0 = 0;

  // UART Setup
   *UART0_ICR = 0x7ff;

   // 115200 Baud
   *UART0_IBRD = 0x2;
   *UART0_FBRD = 0xb;

   // 8n1
   *UART0_LCRH = 0x60;

   // Enable the UART , Tx and Rx
   *UART0_CR = 0x301;

   *UART0_DR='Z';
}
