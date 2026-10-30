
undefined1 sub_b373(undefined1 param_1)

{
  byte bVar1;
  char cVar2;
  char cVar3;
  
  cVar2 = '\0';
  sub_416e(&LAB_CODE_1a82);
  DAT_EXTMEM_fde6 = 1;
  DAT_EXTMEM_fde1 = param_1;
  while ((cVar3 = cVar2, cVar2 == '\0' &&
         (bVar1 = 0x13 - (((DAT_EXTMEM_1a83 < 0x88) << 7) >> 7), cVar3 = DAT_EXTMEM_1a82 - bVar1,
         DAT_EXTMEM_1a82 < bVar1))) {
    sub_e971(1);
    DAT_EXTMEM_1a83 = DAT_EXTMEM_1a83 + 1;
    if (DAT_EXTMEM_1a83 == 0) {
      DAT_EXTMEM_1a82 = DAT_EXTMEM_1a82 + 1;
    }
    cVar2 = sub_41cb();
  }
  sub_41d2(cVar3);
  if (cVar2 == '\x02') {
    DAT_EXTMEM_1a84 = DAT_EXTMEM_fde5;
    DAT_EXTMEM_1a85 = DAT_EXTMEM_fde4;
  }
  return DAT_EXTMEM_1a85;
}

