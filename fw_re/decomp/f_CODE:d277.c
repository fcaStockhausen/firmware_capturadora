
void sub_d277(undefined1 param_1)

{
  byte bVar1;
  char cVar2;
  
  cVar2 = '\0';
  DAT_EXTMEM_1aed = 0;
  DAT_EXTMEM_1aee = 0;
  DAT_EXTMEM_fde1 = param_1;
  sub_418e(0xfde2);
  while ((cVar2 == '\0' &&
         (bVar1 = 0x13 - (((DAT_EXTMEM_1aee < 0x88) << 7) >> 7), cVar2 = DAT_EXTMEM_1aed - bVar1,
         DAT_EXTMEM_1aed < bVar1))) {
    sub_e971(1);
    DAT_EXTMEM_1aee = DAT_EXTMEM_1aee + 1;
    if (DAT_EXTMEM_1aee == 0) {
      DAT_EXTMEM_1aed = DAT_EXTMEM_1aed + 1;
    }
    cVar2 = sub_41cb();
  }
  sub_41d2(cVar2);
  return;
}

