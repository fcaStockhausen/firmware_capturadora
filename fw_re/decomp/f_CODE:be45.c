
byte sub_be45(undefined1 param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4)

{
  byte bVar1;
  undefined1 uVar2;
  undefined1 *puVar3;
  
  DAT_EXTMEM_1a72 = param_3;
  DAT_EXTMEM_1a73 = param_2;
  DAT_EXTMEM_1a74 = param_1;
  DAT_EXTMEM_1a75 = param_4;
  bVar1 = sub_0db8();
  bVar1 = bVar1 & 0x1f;
  if (bVar1 == 1) {
    puVar3 = &DAT_EXTMEM_1a72;
    uVar2 = sub_9f03();
    sub_ead0(uVar2,puVar3[1]);
    DAT_EXTMEM_1a76 = bVar1;
  }
  else if (bVar1 == 2) {
    puVar3 = &DAT_EXTMEM_1a72;
    uVar2 = sub_9f03();
    sub_c4ec(uVar2,puVar3[1]);
    DAT_EXTMEM_1a76 = bVar1;
  }
  else if (bVar1 == 0) {
    puVar3 = &DAT_EXTMEM_1a72;
    uVar2 = sub_9f03();
    sub_aaa4(uVar2,puVar3[1]);
    DAT_EXTMEM_1a76 = bVar1;
  }
  else {
    DAT_EXTMEM_1a76 = 0x16;
  }
  return DAT_EXTMEM_1a76;
}

