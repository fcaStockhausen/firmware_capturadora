
void sub_4aef(byte param_1,undefined1 param_2,undefined1 param_3)

{
  undefined1 uVar1;
  undefined1 uVar2;
  byte bVar3;
  char cVar4;
  undefined1 uVar5;
  short sVar6;
  
  DAT_EXTMEM_1b90 = param_3;
  DAT_EXTMEM_1ba0 = sub_292a(0x1b98);
  sVar6 = 0x1ba1;
  DAT_EXTMEM_1ba1 = DAT_EXTMEM_1ba0 + '\x01';
  uVar2 = sub_25b0();
  bVar3 = sub_278f(uVar2);
  if (bVar3 < 4) {
    sub_4cfb(bVar3 - 4);
    if ((*(byte *)(sVar6 + 3) & 0x40) != 0) {
      DAT_EXTMEM_1b9b = DAT_EXTMEM_1b9b | 0x40;
      sub_25c4(0x1b9c);
      sub_2a22(0x1b9c);
    }
    cVar4 = sub_29bf(0x1b9c);
    if (cVar4 != '\0') {
      DAT_EXTMEM_1b9a = DAT_EXTMEM_1b9a | 1;
      sub_25c4(0x1b9c);
      sub_27d0(0x1b9c);
    }
    bVar3 = DAT_EXTMEM_1b9a;
    if (DAT_EXTMEM_1b9a == 0) {
      bVar3 = DAT_EXTMEM_1b9b;
    }
    if (bVar3 != 0) {
      sub_25c4(0x1b9c);
      sub_271e();
      sub_df61(0xc2,0);
    }
  }
  sub_25aa(0x1b90);
  sub_25eb();
  bVar3 = sub_28f1();
  uVar1 = BANK0_R7;
  uVar2 = BANK0_R6;
  uVar5 = sub_25b3(0x1b95,param_1 - (((0xf7 < bVar3) << 7) >> 7),bVar3 + 8);
  sub_1158(8,uVar5);
  sub_271f();
  BANK0_R6 = uVar2;
  BANK0_R7 = uVar1;
  sub_df61();
  sub_25aa(0x1b90);
  sub_25eb();
  bVar3 = sub_28f1();
  uVar1 = BANK0_R7;
  uVar2 = BANK0_R6;
  uVar5 = sub_25b3(0x1b95,param_1 - (((0xfb < bVar3) << 7) >> 7),bVar3 + 4);
  sub_1158(4,uVar5);
  sub_271f();
  BANK0_R6 = uVar2;
  BANK0_R7 = uVar1;
  sub_df61();
  sub_25aa(0x1b90);
  sub_25eb();
  uVar5 = sub_28f1();
  uVar1 = BANK0_R7;
  uVar2 = BANK0_R6;
  uVar5 = sub_25b3(0x1b95,param_1,uVar5);
  sub_1138(uVar5);
  sub_271f();
  BANK0_R6 = uVar2;
  BANK0_R7 = uVar1;
  sub_df61();
  cVar4 = sub_26eb(7);
  if (cVar4 == '\0') {
    sub_25aa(0x1b90);
    sub_25eb();
    cVar4 = sub_2795();
    if (cVar4 != '\x01') {
      uVar2 = sub_25c4(0x1b91);
      param_1 = param_1 & 0xfa;
      goto LAB_CODE_4c14;
    }
  }
  uVar2 = sub_25c4(0x1b91);
  param_1 = param_1 | 4;
LAB_CODE_4c14:
                    /* WARNING: Subroutine does not return */
  sub_1253(param_2,0x1b91,param_1,uVar2);
}

