
void FUN_CODE_d646(void)

{
  undefined1 uVar1;
  
  if (BANK1_R2 == '\x01') {
    if ((BANK1_R4 == '\t') || (BANK1_R4 == '\x02')) {
      DAT_EXTMEM_12f5 = 0;
    }
    if (BANK1_R4 == '\n') {
      DAT_EXTMEM_12f5 = 0;
    }
    sub_a422();
  }
  else {
    uVar1 = sub_a446();
    sub_a406(uVar1);
  }
  sub_e318();
  return;
}

