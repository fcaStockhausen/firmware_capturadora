
byte sub_b80b(undefined1 param_1,byte param_2)

{
  byte bVar1;
  
  DAT_EXTMEM_1a7d = param_1;
  DAT_EXTMEM_1a7e = param_2;
  bVar1 = param_2;
  if ((param_2 & 0xf) == 0) {
    if (-1 < (char)param_2) {
      bVar1 = 0;
    }
  }
  else if ((((DAT_EXTMEM_118f != BANK0_R7) || (BANK0_R6 != '\0')) &&
           ((DAT_EXTMEM_1190 != BANK0_R7 || (BANK0_R6 != '\0')))) &&
          ((bVar1 = DAT_EXTMEM_1191, DAT_EXTMEM_1191 == BANK0_R7 && (bVar1 = 0, BANK0_R6 == '\0'))))
  {
    bVar1 = param_2;
  }
  return bVar1;
}

