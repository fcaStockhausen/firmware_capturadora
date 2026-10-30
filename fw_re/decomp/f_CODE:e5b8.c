
void sub_e5b8(void)

{
  undefined1 uVar1;
  
  if (BANK1_R2 == '\x02') {
    uVar1 = sub_ccc0();
  }
  else {
    if (BANK1_R2 != '\x01') {
      _2_4 = 1;
      return;
    }
    sub_ccf1();
    uVar1 = 0;
  }
  sub_e318(uVar1);
  return;
}

