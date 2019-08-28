/******************************************************************************
  NovaOS
******************************************************************************/

.global _start

_start:
  # Check cpu
  mrs x1, mpidr_el1
  ands x1,x1, #3
  bne 3f

  # Setup stack
  adr x1, _start
  mov sp, x1

  # Clear BSS
  eor v0.16b, v0.16b, v0.16b
  eor v1.16b, v1.16b, v1.16b
  eor v2.16b, v2.16b, v2.16b
  eor v3.16b, v3.16b, v3.16b
  ldr x6, =__bss_start
  ldr x7, =__bss_end
1:
  cmp x6,x7
  bge 2f
  st4 { v0.2d , v1.2d, v2.2d , v3.2d } , [x6], #64
  b 1b
2:
  # Jump to main
  bl main
3:
  wfi
  b 1b
