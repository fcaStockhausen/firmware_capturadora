
char FUN_CODE_7116(undefined1 param_1,undefined1 param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  char cVar3;
  byte bVar4;
  undefined1 uVar5;
  short sVar6;
  char *pcVar7;
  
  sVar6 = 0x1a83;
  DAT_EXTMEM_1a82 = param_1;
  DAT_EXTMEM_1a83 = param_2;
  sub_38e9(BANK0_R7);
  sub_125f(sVar6 + 1);
  nop();
  nop();
  nop();
  nop();
  DAT_EXTMEM_1a84 = 0;
  while (DAT_EXTMEM_1a84 < 4) {
    sub_385c(DAT_EXTMEM_1a84,0,0,0,BANK0_R3);
    sub_1112();
    sub_38c6();
  }
  DAT_EXTMEM_1a84 = 0;
  while (DAT_EXTMEM_1a84 < 4) {
    sub_38f3(DAT_EXTMEM_1a84 - 4,&LAB_CODE_1a82);
    sub_385b();
    sub_1112();
    sub_38c6();
  }
  DAT_EXTMEM_1a84 = 0;
  do {
    uVar5 = 1;
    cVar3 = BANK0_R6 + '\x01';
    while (cVar3 = cVar3 + -1, cVar3 != '\0') {
      uVar5 = 0;
    }
    pcVar7 = (char *)CONCAT11(-0x1e - (((0x2b < DAT_EXTMEM_1a84) << 7) >> 7),DAT_EXTMEM_1a84 - 0x2c)
    ;
    sub_38cf(uVar5);
  } while (*pcVar7 != '\x04');
  sub_125f(0x1a88);
  nop();
  nop();
  nop();
  nop();
  while ((DAT_EXTMEM_1a85 == '\0' &&
         (bVar4 = 0x13 - (((DAT_EXTMEM_1a87 < 0x88) << 7) >> 7), DAT_EXTMEM_1a86 < bVar4))) {
    sub_e971(DAT_EXTMEM_1a86 - bVar4,1);
    DAT_EXTMEM_1a87 = DAT_EXTMEM_1a87 + 1;
    if (DAT_EXTMEM_1a87 == 0) {
      DAT_EXTMEM_1a86 = DAT_EXTMEM_1a86 + 1;
    }
    DAT_EXTMEM_1a84 = 0;
    do {
      sub_381a(0x1a88);
      uVar2 = BANK0_R3;
      uVar1 = BANK0_R1;
      uVar5 = BANK0_R0;
      cVar3 = DAT_EXTMEM_1a84 - 0x20;
      sub_384f(0,DAT_EXTMEM_1a84);
      sub_1125();
      pcVar7 = &DAT_EXTMEM_1a88;
      BANK0_R0 = uVar5;
      BANK0_R1 = uVar1;
      BANK0_R3 = uVar2;
      sub_38da();
      sub_38d0();
    } while (*pcVar7 != '\x04');
    sub_37d1(0x1a88);
    sub_389f();
    DAT_EXTMEM_1a85 = cVar3;
  }
  DAT_EXTMEM_1a84 = 0;
  while( true ) {
    if (3 < DAT_EXTMEM_1a84) break;
    bVar4 = DAT_EXTMEM_1a84;
    sub_385b(0x70,0,0,0);
    sub_1112();
    sub_38ca(bVar4 - 0x18);
  }
  return DAT_EXTMEM_1a84 - 4;
}

