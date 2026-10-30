
char sub_bfba(void)

{
  char cVar1;
  
  if (_1_4 == '\0') {
    cVar1 = P2_6;
    if ((cVar1 != '\0') && (DAT_EXTMEM_1027 == 0)) goto LAB_CODE_bfe3;
    P2_6 = 1;
  }
  else {
    DAT_EXTMEM_1027 = DAT_EXTMEM_1027 + 1;
    if (DAT_EXTMEM_1027 < 0x1e) goto LAB_CODE_bfe3;
    if ((_1_4 != '\0') && (cVar1 = P2_6, cVar1 != '\0')) {
      P2_6 = 0;
    }
  }
  DAT_EXTMEM_1027 = 0;
LAB_CODE_bfe3:
  if ((DAT_EXTMEM_fb02 & 1) == 0) {
    cVar1 = P2_7;
    if ((cVar1 != '\0') && (DAT_EXTMEM_1028 == '\0')) {
      return '\0';
    }
    P2_7 = 1;
  }
  else {
    cVar1 = DAT_EXTMEM_1028 + -0x1d;
    if ((DAT_EXTMEM_1028 + 1 < 0x1e) << 7 < '\0') {
      DAT_EXTMEM_1028 = DAT_EXTMEM_1028 + 1;
      return cVar1;
    }
    if (((DAT_EXTMEM_fb02 & 1) != 0) && (cVar1 = P2_7, cVar1 != '\0')) {
      P2_7 = 0;
    }
  }
  DAT_EXTMEM_1028 = 0;
  return '\0';
}

