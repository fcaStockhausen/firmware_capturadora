
byte sub_bf5e(void)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  byte bVar5;
  byte bVar6;
  
  bVar6 = 0x1a;
  sub_8bc1(0x82,0xa0,0xf4,0x1a);
  sub_ee94();
  sub_8bb8(1);
  sub_9477();
  sub_8bb8(3);
  sub_9a8b();
  sub_ee97();
  sub_8c3f(0x1a83,0x10);
  uVar4 = BANK0_R7;
  uVar3 = BANK0_R6;
  uVar2 = BANK0_R5;
  uVar1 = BANK0_R4;
  bVar5 = 0x18;
  sub_8c3f(&LAB_CODE_1a82,0x18);
  BANK0_R3 = uVar4;
  BANK0_R2 = uVar3;
  BANK0_R1 = uVar2;
  BANK0_R0 = uVar1;
  return bVar6 | bVar5;
}

