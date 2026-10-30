
void sub_d7d6(char param_1)

{
  DAT_INTMEM_2e = param_1;
  if (param_1 != '\x18') {
    sub_a601(0);
    sub_0e32(0,100,0,DAT_INTMEM_2e);
    sub_585f(BANK0_R6,BANK0_R7,0);
    sub_da22(0);
    DAT_EXTMEM_ff13 = DAT_EXTMEM_ff13 | 1;
    nop();
    nop();
    nop();
    nop();
  }
  sub_dbaf();
  FUN_CODE_c234();
  return;
}

