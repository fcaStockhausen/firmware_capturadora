
void sub_d1b5(char param_1,char param_2,char param_3,byte param_4)

{
  char cVar1;
  char cVar2;
  
  DAT_EXTMEM_1aed = 0;
  DAT_EXTMEM_1aec = param_4;
  while( true ) {
    cVar2 = (DAT_EXTMEM_1aed < DAT_EXTMEM_1aec) << 7;
    if (DAT_EXTMEM_1aed >= DAT_EXTMEM_1aec) {
      return;
    }
    cVar1 = '\x01';
    sub_ed82(DAT_EXTMEM_1aed - DAT_EXTMEM_1aec);
    sub_396b();
    sub_e7dc();
    if (((param_1 != '\0' || param_2 != '\0') || param_3 != '\0') || cVar1 != '\0') break;
    param_3 = '\0';
    sub_ae84(1);
    if (cVar2 < '\0') {
      return;
    }
    DAT_EXTMEM_1aed = DAT_EXTMEM_1aed + 1;
  }
  sub_ed52();
  return;
}

