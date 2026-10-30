
void sub_569e(byte param_1)

{
  bool bVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  byte bVar5;
  char cVar6;
  byte bVar7;
  byte bVar8;
  byte bVar9;
  char cVar10;
  
  DAT_EXTMEM_22ee = DAT_EXTMEM_22be;
  DAT_EXTMEM_22ef = DAT_EXTMEM_22bf;
  bVar9 = DAT_EXTMEM_22b3;
  if ((DAT_EXTMEM_22b3 & 1) != 1) {
    sub_326b(0x22ee);
  }
  DAT_EXTMEM_1ae2 = DAT_EXTMEM_22b8;
  DAT_EXTMEM_1ae3 = DAT_EXTMEM_22b9;
  DAT_EXTMEM_1ae4 = DAT_EXTMEM_22ba;
  DAT_EXTMEM_1ae5 = DAT_EXTMEM_22bb;
  DAT_EXTMEM_1ae6 = DAT_EXTMEM_22de;
  DAT_EXTMEM_1ae7 = DAT_EXTMEM_22df;
  DAT_EXTMEM_1ae8 = DAT_EXTMEM_22e0;
  DAT_EXTMEM_1ae9 = DAT_EXTMEM_22e1;
  bVar1 = (bVar9 & 1) != 1;
  bVar5 = DAT_EXTMEM_22e1;
  if (bVar1) {
    sub_326b(0x1ae4);
  }
  _0_3 = bVar1;
  sub_eb1d();
  bVar8 = DAT_EXTMEM_1ae6;
  bVar7 = sub_31fd(DAT_EXTMEM_1ae7,0x1ae2);
  bVar1 = param_1 < bVar8 - (((bVar7 < bVar5) << 7) >> 7);
  cVar6 = bVar1 << 7;
  DAT_EXTMEM_1aea = bVar8;
  DAT_EXTMEM_1aeb = bVar5;
  if (bVar1) {
    DAT_EXTMEM_1aea = BANK0_R4;
    DAT_EXTMEM_1aeb = BANK0_R5;
  }
  sub_32c1(0x268c);
  if (cVar6 < '\0') {
    DAT_EXTMEM_1aea = param_1;
    DAT_EXTMEM_1aeb = bVar9;
  }
  bVar5 = DAT_EXTMEM_1ae8;
  bVar8 = DAT_EXTMEM_1ae9;
  sub_32c1(0x1ae4);
  DAT_EXTMEM_1aec = bVar5;
  DAT_EXTMEM_1aed = bVar8;
  if (cVar6 < '\0') {
    DAT_EXTMEM_1aec = BANK0_R4;
    DAT_EXTMEM_1aed = BANK0_R5;
  }
  sub_32c1(0x268e);
  if (cVar6 < '\0') {
    DAT_EXTMEM_1aec = param_1;
    DAT_EXTMEM_1aed = bVar9;
  }
  bVar8 = sub_3230(0x1aec);
  cVar6 = -0x20;
  sub_d0aa(0xe,0xd4);
  uVar3 = BANK0_R7;
  uVar2 = BANK0_R6;
  bVar5 = BANK0_R5;
  bVar9 = BANK0_R4;
  sub_33c2(0x22ee,100);
  uVar4 = BANK0_R7;
  BANK0_R4 = bVar9;
  BANK0_R5 = bVar5;
  BANK0_R6 = uVar2;
  BANK0_R7 = uVar3;
  sub_d0aa(0,0,cVar6 - ((CARRY1(bVar8,DAT_INTMEM_32) << 7) >> 7),uVar4,bVar8 + DAT_INTMEM_32);
  cVar10 = '\0';
  cVar6 = sub_10eb(BANK0_R4,BANK0_R5,BANK0_R6,BANK0_R7,0,0,DAT_EXTMEM_1aea,DAT_EXTMEM_1aeb);
  if ((cVar10 < '\0') ||
     (bVar9 = 0x42 - (((DAT_EXTMEM_22bd < 0x69) << 7) >> 7), cVar6 = DAT_EXTMEM_22bc - bVar9,
     bVar9 <= DAT_EXTMEM_22bc)) {
    sub_326b(cVar6,0x1aea);
  }
  bVar9 = DAT_EXTMEM_22b8 ^ 10;
  if ((DAT_EXTMEM_22b8 ^ 10) == 0) {
    bVar9 = DAT_EXTMEM_22b9;
  }
  if (((((bVar9 == 0) &&
        (bVar5 = 4 - (((DAT_EXTMEM_22bb < 0x38) << 7) >> 7), bVar9 = DAT_EXTMEM_22ba - bVar5,
        bVar5 <= DAT_EXTMEM_22ba)) && (bVar9 = DAT_EXTMEM_22de, DAT_EXTMEM_22de == 7)) &&
      ((bVar9 = DAT_EXTMEM_22df, DAT_EXTMEM_22df == 0x80 &&
       (bVar9 = DAT_EXTMEM_22e0, DAT_EXTMEM_22e0 == 4)))) &&
     ((bVar9 = DAT_EXTMEM_22e1, DAT_EXTMEM_22e1 == 0x38 &&
      ((bVar5 = 0x13 - (((DAT_EXTMEM_22bf < 0x24) << 7) >> 7), bVar9 = DAT_EXTMEM_22be - bVar5,
       bVar5 <= DAT_EXTMEM_22be && (bVar9 = DAT_INTMEM_32 - 0x33, 0x32 < DAT_INTMEM_32)))))) {
    DAT_EXTMEM_1aea = 5;
    bVar9 = 0;
    DAT_EXTMEM_1aeb = 0;
  }
  sub_e33f(bVar9,0x17,0x70,0xb,0xb8);
  DAT_EXTMEM_1af1 = 1;
  DAT_EXTMEM_1af2 = 0x1a;
  DAT_EXTMEM_1af3 = 0xea;
  sub_bc02(0xe2,0x1a,1);
  DAT_EXTMEM_1af1 = 1;
  DAT_EXTMEM_1af2 = 0x1a;
  DAT_EXTMEM_1af3 = 0xe6;
  sub_bf01(0xea,0x1a,1);
  sub_ede2();
  sub_ee2f(1,0xf6,0x20);
  return;
}

