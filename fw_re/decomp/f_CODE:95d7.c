
byte sub_95d7(byte param_1)

{
  byte bVar1;
  
  DAT_EXTMEM_1aea = '\0';
  DAT_EXTMEM_1aeb = '\0';
  DAT_EXTMEM_1ae5 = param_1;
  DAT_EXTMEM_1ae8 = param_1;
  if ((_0_3 != '\0') && (param_1 == 1)) {
    DAT_EXTMEM_1aea = '\x01';
  }
  while( true ) {
    if ((0xfc < DAT_EXTMEM_1ae5 ^ 0x80U) - (((DAT_EXTMEM_1ae8 < DAT_EXTMEM_1ae5 + 3) << 7) >> 7) <
        0x81) {
      bVar1 = 0;
      if (DAT_EXTMEM_1ae9 != 0) {
        bVar1 = sub_ed52();
      }
      return bVar1;
    }
    DAT_EXTMEM_1ae9 = DAT_EXTMEM_1ae8 % 3;
    if (DAT_EXTMEM_1aea == '\x01') {
      if (DAT_EXTMEM_1ae9 == 2) {
        DAT_EXTMEM_1ae9 = 0;
      }
      else if (DAT_EXTMEM_1ae9 == 0) {
        DAT_EXTMEM_1ae9 = 2;
      }
    }
    sub_9310(DAT_EXTMEM_1ae6,DAT_EXTMEM_1ae7,DAT_EXTMEM_1ae9);
    bVar1 = 6;
    sub_d1b5();
    if ((char)bVar1 < '\0') break;
    if (bVar1 == 0) {
      return DAT_EXTMEM_1ae9;
    }
    if ((DAT_EXTMEM_1ae9 == 1) && (DAT_EXTMEM_1aeb == '\0')) {
      DAT_EXTMEM_1aeb = '\x01';
      DAT_EXTMEM_1ae8 = DAT_EXTMEM_1ae8 - 1;
    }
    DAT_EXTMEM_1ae8 = DAT_EXTMEM_1ae8 + 1;
  }
  return bVar1;
}

