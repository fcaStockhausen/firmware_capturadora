
void sub_e1ff(void)

{
  if (BANK1_R2 == '\x02') {
    DAT_EXTMEM_12f5 = 0xff;
    sub_ccc8(0x1f,0x12f6);
  }
  else {
    if (BANK1_R2 != '\x01') {
      _2_4 = 1;
      return;
    }
    sub_ccf1();
  }
  sub_e318(0);
  return;
}

