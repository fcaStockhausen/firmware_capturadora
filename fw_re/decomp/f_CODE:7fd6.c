
void FUN_CODE_7fd6(undefined1 *param_1)

{
  bool bVar1;
  byte bVar2;
  char cVar3;
  char cVar4;
  char cVar5;
  
  func_0x781e();
  *param_1 = 1;
  param_1[1] = 0;
  param_1[2] = 9;
  sub_89e6();
  bVar2 = BANK1_R7 - 1;
  cVar3 = BANK1_R6 + (-1 - (((BANK1_R7 != '\0') << 7) >> 7));
  bVar1 = CARRY1(BANK3_R7,bVar2);
  BANK3_R7 = BANK3_R7 + bVar2;
  cVar5 = CARRY1(BANK3_R6,cVar3 - ((bVar1 << 7) >> 7)) << 7;
  cVar4 = sub_478f(0,0);
  BANK3_R4 = cVar4 + (BANK3_R4 - (cVar5 >> 7));
  bVar1 = BANK3_R3 < bVar2;
  BANK3_R3 = BANK3_R3 - bVar2;
  BANK3_R2 = BANK3_R2 - (cVar3 - ((bVar1 << 7) >> 7));
  return;
}

