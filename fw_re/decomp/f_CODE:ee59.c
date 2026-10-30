
byte sub_ee59(void)

{
  byte in_PSW;
  
  return DAT_EXTMEM_f5c0 >> 1 | in_PSW & 0x80;
}

