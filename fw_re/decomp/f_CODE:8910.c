
void sub_8910(char param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  char cVar3;
  
  DAT_EXTMEM_1008 = param_1;
  sub_25b0();
  sub_28b3();
  sub_2693(0x1008);
  sub_2632(0x101a);
  cVar3 = sub_2983();
  if (cVar3 == '\0') {
    param_1 = '\x01';
  }
  DAT_EXTMEM_1015 = param_1;
  sub_28e6(9,0x10);
  if (DAT_EXTMEM_1015 != '\0') {
    sub_125f(0x1011);
    nop();
    nop();
    nop();
    nop();
    sub_25b3(0x101a);
    sub_28d6();
                    /* WARNING: Subroutine does not return */
    sub_1253(0x100d);
  }
  sub_25b3(0x101a);
  sub_26cb();
  sub_2a12(0x1016);
  sub_25aa(0x1008);
  sub_25eb();
  sub_267f();
  uVar2 = BANK0_R7;
  uVar1 = BANK0_R6;
  sub_25c4(0x1016);
  sub_271e();
  BANK0_R6 = uVar1;
  BANK0_R7 = uVar2;
  sub_df61();
  return;
}

