
char sub_e318(char param_1,char param_2)

{
  byte bVar1;
  
  sub_5438(0x1a7d);
  CCAPM4 = 0xfd;
  while (bVar1 = param_1 - (((DAT_EXTMEM_1a7e < param_2 + 1U) << 7) >> 7), bVar1 <= DAT_EXTMEM_1a7d)
  {
    sub_539f(DAT_EXTMEM_1a7d - bVar1,0x1a7f);
  }
  EA = DAT_EXTMEM_1a82 != '\0';
  return DAT_EXTMEM_1a82 + -1;
}

