
void sub_b666(undefined1 param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  byte bVar5;
  byte bVar6;
  undefined1 uVar7;
  
  DAT_EXTMEM_1acb = 0;
  DAT_EXTMEM_1ac8 = param_3;
  DAT_EXTMEM_1ac9 = param_2;
  DAT_EXTMEM_1aca = param_1;
  while( true ) {
    if (0x13 < DAT_EXTMEM_1acb) {
      return;
    }
    bVar6 = DAT_EXTMEM_1acb;
    uVar4 = sub_eaa8(DAT_EXTMEM_1acb - 0x14,param_4);
    param_4 = sub_0db8(uVar4);
    uVar2 = BANK0_R3;
    uVar4 = BANK0_R2;
    bVar5 = (byte)((ushort)bVar6 * 0x12);
    if (*(char *)CONCAT11((char)((ushort)bVar6 * 0x12 >> 8) + (-0x10 - (((0x51 < bVar5) << 7) >> 7))
                          ,bVar5 + 0xae) == BANK0_R6) break;
    DAT_EXTMEM_1acb = DAT_EXTMEM_1acb + 1;
  }
  bVar6 = (byte)((ushort)DAT_EXTMEM_1acb * 0x12);
  uVar7 = sub_eaa8(bVar6 + 0xae,
                   ((char)((ushort)DAT_EXTMEM_1acb * 0x12 >> 8) - (((0x51 < bVar6) << 7) >> 7)) +
                   -0x10,0xff,param_4);
  uVar3 = BANK0_R3;
  uVar1 = BANK0_R2;
  BANK0_R2 = uVar4;
  BANK0_R3 = uVar2;
  sub_0d92(uVar7,uVar1,uVar3,0,0x12);
  return;
}

