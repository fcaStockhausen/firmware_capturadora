
void sub_bd27(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5,byte param_6,
             byte param_7)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  byte bVar4;
  short sVar5;
  
  DAT_EXTMEM_1b03 = param_6;
  DAT_EXTMEM_1b04 = param_7;
  sub_d953();
  uVar3 = sub_a2cf();
  sub_a2aa(0x1b05,uVar3);
  sub_10de();
  sub_a312(uVar3);
  bVar4 = sub_a2cf();
  uVar2 = BANK0_R2;
  uVar1 = BANK0_R1;
  uVar3 = BANK0_R0;
  sVar5 = 0x1b05;
  sub_a2aa(0x1b05,bVar4);
  sVar5 = sVar5 + 1;
  sub_a2d8(sVar5);
  sub_a312();
  BANK0_R0 = uVar3;
  BANK0_R1 = uVar1;
  BANK0_R2 = uVar2;
                    /* WARNING: Subroutine does not return */
  sub_1253(sVar5 + 1,param_1 | param_4,param_2 | param_5,param_3 | param_6,bVar4 | param_7);
}

