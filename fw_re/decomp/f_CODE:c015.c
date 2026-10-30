
void FUN_CODE_c015(undefined1 param_1,undefined1 param_2)

{
  byte bVar1;
  undefined1 uVar2;
  char cVar3;
  
  cVar3 = '\0';
  DAT_EXTMEM_1a84 = 0;
  DAT_EXTMEM_1a85 = 0;
  _0_0 = 0;
  uVar2 = BANK0_R7;
  DAT_EXTMEM_1a82 = param_1;
  DAT_EXTMEM_1a83 = param_2;
  sub_e9c2();
  DAT_EXTMEM_fde1 = uVar2;
  sub_418e(0xfde2,DAT_EXTMEM_1a82,DAT_EXTMEM_1a83);
  while ((cVar3 == '\0' &&
         (bVar1 = 0x13 - (((DAT_EXTMEM_1a85 < 0x88) << 7) >> 7), cVar3 = DAT_EXTMEM_1a84 - bVar1,
         DAT_EXTMEM_1a84 < bVar1))) {
    sub_e971(1);
    DAT_EXTMEM_1a85 = DAT_EXTMEM_1a85 + 1;
    if (DAT_EXTMEM_1a85 == 0) {
      DAT_EXTMEM_1a84 = DAT_EXTMEM_1a84 + 1;
    }
    cVar3 = sub_41cb();
  }
  sub_41d2(cVar3);
  _0_0 = 1;
  sub_e9c2();
  return;
}

