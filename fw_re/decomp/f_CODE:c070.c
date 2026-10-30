
void sub_c070(char param_1)

{
  DAT_EXTMEM_1ac0 = param_1;
  sub_a1a8();
  sub_e63a(_0_1 & 1,1);
  if (_0_1 != 0) {
    sub_e971(10);
  }
  if (DAT_EXTMEM_1ac0 == '\x01') {
    DAT_EXTMEM_1ac1 = 4;
  }
  else if (DAT_EXTMEM_1ac0 == '\x02') {
    DAT_EXTMEM_1ac1 = 2;
  }
  else if (DAT_EXTMEM_1ac0 == '\b') {
    DAT_EXTMEM_1ac1 = 1;
  }
  else if (DAT_EXTMEM_1ac0 == '\0') {
    DAT_EXTMEM_1ac1 = 8;
  }
  sub_e63a(_0_1 & 1,DAT_EXTMEM_1ac1,0xf0,0xe);
  return;
}

