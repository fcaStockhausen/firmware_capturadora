
void sub_c1db(void)

{
  undefined1 uVar1;
  
  if (BANK1_R4 == '\x02') {
    if ((((BANK1_R2 != '\x03') && (BANK1_R2 != '\x06')) && (BANK1_R2 != '\a')) &&
       (BANK1_R2 != '\x02')) {
      _2_4 = 1;
      return;
    }
    sub_ccc8(7,0x12f5);
    uVar1 = 0;
  }
  else {
    if (BANK1_R4 != '\0') {
      _2_4 = 1;
      return;
    }
    if ((BANK1_R2 != '\x02') && (BANK1_R2 != '\x01')) {
      _2_4 = 1;
      return;
    }
    uVar1 = sub_ccc8(0,0x12f5);
  }
  sub_e318(uVar1,1);
  return;
}

