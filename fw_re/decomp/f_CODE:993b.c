
char FUN_CODE_993b(void)

{
  byte bVar1;
  char cVar2;
  char cVar3;
  
  sub_125f(0x1aa7);
  nop();
  nop();
  nop();
  nop();
  if ((DAT_EXTMEM_11a3 != 0 || DAT_EXTMEM_11a2 != 0) &&
     (DAT_EXTMEM_11a2 < (byte)(DAT_INTMEM_24 - (((DAT_EXTMEM_11a3 < DAT_INTMEM_25 + 1U) << 7) >> 7))
     )) {
    DAT_EXTMEM_f21b = 0x3c;
  }
  if ((DAT_EXTMEM_f007 & 3) != 0) {
    cVar3 = (DAT_INTMEM_32 >> 1) + 0x90;
    cVar2 = '\x01' - (((0x6f < DAT_INTMEM_32 >> 1) << 7) >> 7);
    sub_0e44(0,DAT_INTMEM_32);
    bVar1 = DAT_INTMEM_40;
    if (((byte)(cVar2 - (((DAT_INTMEM_2b < cVar3 + 1U) << 7) >> 7)) <= DAT_INTMEM_2a) &&
       ((DAT_INTMEM_40 & 1) != 0)) {
      DAT_INTMEM_2a = 0;
      DAT_INTMEM_2b = 0;
      DAT_INTMEM_40 = DAT_INTMEM_40 | 2;
      if ((DAT_EXTMEM_f620 & 1) != 0) {
        cVar3 = '\0';
        cVar2 = '\0';
        do {
          if (DAT_EXTMEM_f041 != '\0') {
            DAT_INTMEM_40 = bVar1 & 0xfd;
            break;
          }
          cVar3 = cVar3 + '\x01';
          if (cVar3 == '\0') {
            cVar2 = cVar2 + '\x01';
          }
        } while ((cVar2 != '\x05') || (cVar3 != -0x6c));
        if ((DAT_INTMEM_40 >> 1 & 1) != 0) {
          sub_e132();
          DAT_INTMEM_48 = DAT_INTMEM_48 + '\x01';
        }
      }
      DAT_EXTMEM_f620 = 1;
    }
  }
  if (DAT_EXTMEM_7f02 != '\0') {
    if (DAT_EXTMEM_11ac == '\0') {
      sub_ed82(200);
    }
    sub_e486();
  }
  if (_2_6 != '\0') {
    sub_b874();
    _2_6 = '\0';
  }
  cVar2 = DAT_INTMEM_23 + -1;
  if (DAT_INTMEM_23 != '\0') {
    cVar2 = '\0';
    DAT_INTMEM_23 = '\0';
  }
  return cVar2;
}

