
void sub_caf9(void)

{
  if (BANK1_R4 == '\x02') {
    if ((((BANK1_R2 != '\x03') && (BANK1_R2 != '\x06')) && (BANK1_R2 != '\a')) &&
       (BANK1_R2 != '\x02')) {
      _2_4 = 1;
      return;
    }
  }
  else {
    if (BANK1_R4 != '\0') {
      _2_4 = 1;
      return;
    }
    if (BANK1_R2 != '\x01') {
      _2_4 = 1;
      return;
    }
  }
  DAT_EXTMEM_12f5 = 0;
  DAT_EXTMEM_12f6 = 0;
  DAT_EXTMEM_12f7 = 0;
  sub_ccc7();
  sub_e318(BANK1_R6,BANK1_R7);
  return;
}

