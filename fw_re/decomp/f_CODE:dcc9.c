
void FUN_CODE_dcc9(void)

{
  undefined1 uVar1;
  
  if (BANK1_R2 == '\x02') {
    DAT_EXTMEM_12f5 = 0xff;
    sub_a421(0x1f,0x12f6);
    uVar1 = 2;
  }
  else {
    if (BANK1_R2 != '\x01') {
      _2_4 = 1;
      return;
    }
    uVar1 = sub_a446();
  }
  sub_e318(0,uVar1);
  return;
}

