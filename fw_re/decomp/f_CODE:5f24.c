
byte sub_5f24(byte param_1,byte param_2,undefined1 param_3)

{
  byte bVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  char cVar6;
  byte bVar7;
  char cVar8;
  char cVar9;
  char in_PSW;
  undefined1 *puVar10;
  
  puVar10 = &LAB_CODE_1a82;
  DAT_EXTMEM_1a82 = param_3;
  uVar5 = sub_38e9();
  puVar10[1] = uVar5;
  sub_125f(puVar10 + 2);
  nop();
  nop();
  nop();
  nop();
  sub_3974();
  while( true ) {
    sub_399b();
    if (-1 < in_PSW) break;
    sub_3857(DAT_EXTMEM_1a82);
    sub_1112();
    in_PSW = CARRY1(DAT_EXTMEM_1a86,0xe2 - (((0x37 < DAT_EXTMEM_1a87) << 7) >> 7)) << 7;
    cVar6 = sub_393e(DAT_EXTMEM_1a87 - 0x38);
    if (cVar6 == '\0') {
      sub_39e1();
    }
  }
  sub_3974();
  do {
    bVar7 = 2;
    cVar6 = BANK0_R5 + '\x01';
    while (cVar6 = cVar6 + -1, cVar6 != '\0') {
      bVar7 = bVar7 >> 1;
    }
    bVar1 = 0xe2 - (((0x2b < DAT_EXTMEM_1a87) << 7) >> 7);
    cVar6 = CARRY1(DAT_EXTMEM_1a86,bVar1) << 7;
    cVar8 = sub_3943(bVar7,CONCAT11(DAT_EXTMEM_1a86 + bVar1,DAT_EXTMEM_1a87 - 0x2c));
    if (cVar8 == '\0') {
      sub_39e1();
    }
    bVar7 = DAT_EXTMEM_1a86;
    if (DAT_EXTMEM_1a86 == 0) {
      bVar7 = DAT_EXTMEM_1a87 ^ 4;
    }
  } while (bVar7 != 0);
  sub_125f(0x1a88);
  nop();
  nop();
  nop();
  nop();
  while (cVar8 = DAT_EXTMEM_1a83, DAT_EXTMEM_1a83 == '\0') {
    bVar7 = 0x13 - (((DAT_EXTMEM_1a85 < 0x88) << 7) >> 7);
    cVar6 = (DAT_EXTMEM_1a84 < bVar7) << 7;
    cVar8 = DAT_EXTMEM_1a84 - bVar7;
    if (DAT_EXTMEM_1a84 >= bVar7) break;
    sub_e971(1);
    DAT_EXTMEM_1a85 = DAT_EXTMEM_1a85 + 1;
    if (DAT_EXTMEM_1a85 == 0) {
      DAT_EXTMEM_1a84 = DAT_EXTMEM_1a84 + 1;
    }
    sub_3974();
    do {
      sub_381a(0x1a88);
      uVar4 = BANK0_R3;
      uVar3 = BANK0_R2;
      uVar2 = BANK0_R1;
      uVar5 = BANK0_R0;
      cVar6 = (0x1f < DAT_EXTMEM_1a87) << 7;
      cVar8 = DAT_EXTMEM_1a87 - 0x20;
      param_1 = DAT_EXTMEM_1a86;
      param_2 = DAT_EXTMEM_1a87;
      sub_384f(DAT_EXTMEM_1a86);
      sub_1125();
      BANK0_R0 = uVar5;
      BANK0_R1 = uVar2;
      BANK0_R2 = uVar3;
      BANK0_R3 = uVar4;
      sub_38d7();
      cVar9 = sub_3944();
      if (cVar9 == '\0') {
        sub_39e1();
      }
      bVar7 = DAT_EXTMEM_1a86;
      if (DAT_EXTMEM_1a86 == 0) {
        bVar7 = DAT_EXTMEM_1a87 ^ 4;
      }
    } while (bVar7 != 0);
    sub_37d1(0x1a88);
    sub_389f();
    DAT_EXTMEM_1a83 = cVar8;
  }
  sub_3974(cVar8);
  while( true ) {
    sub_399b();
    if (-1 < cVar6) break;
    sub_1112(BANK0_R1,param_2 * '\b',0x70,0,0,0);
    cVar6 = CARRY1(param_1,0xef - (((0x17 < param_2) << 7) >> 7)) << 7;
    cVar8 = sub_393e(param_2 - 0x18);
    if (cVar8 == '\0') {
      sub_39e1();
    }
  }
  sub_125f(0x1a88);
  nop();
  nop();
  nop();
  nop();
  if (DAT_EXTMEM_1a83 == '\x01') {
    DAT_EXTMEM_1a84 = 0;
    DAT_EXTMEM_1a85 = 0;
    do {
      sub_381a(0x1a88);
      uVar4 = BANK0_R3;
      uVar3 = BANK0_R2;
      uVar2 = BANK0_R1;
      uVar5 = BANK0_R0;
      sub_3851(DAT_EXTMEM_1a84 + (-0x1e - (((0x2f < DAT_EXTMEM_1a85) << 7) >> 7)),DAT_EXTMEM_1a85,
               DAT_EXTMEM_1a85 - 0x30);
      sub_1125();
      BANK0_R0 = uVar5;
      BANK0_R1 = uVar2;
      BANK0_R2 = uVar3;
      BANK0_R3 = uVar4;
      sub_38d7();
      DAT_EXTMEM_1a85 = DAT_EXTMEM_1a85 + 1;
      if (DAT_EXTMEM_1a85 == 0) {
        DAT_EXTMEM_1a84 = DAT_EXTMEM_1a84 + 1;
      }
      bVar7 = DAT_EXTMEM_1a84;
      if (DAT_EXTMEM_1a84 == 0) {
        bVar7 = DAT_EXTMEM_1a85 ^ 4;
      }
    } while (bVar7 != 0);
    DAT_EXTMEM_1a86 = DAT_EXTMEM_1a8a;
    DAT_EXTMEM_1a87 = DAT_EXTMEM_1a8b;
  }
  return DAT_EXTMEM_1a87;
}

