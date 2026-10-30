
void sub_c2e4(char param_1)

{
  if (param_1 == '\x01') {
    DAT_EXTMEM_1aa8 = 1;
  }
  else if (param_1 == '\x02') {
    DAT_EXTMEM_1aa8 = 2;
  }
  else if (param_1 == '\b') {
    DAT_EXTMEM_1aa8 = 0x10;
  }
  else if (param_1 == '\0') {
    DAT_EXTMEM_1aa8 = 4;
  }
  DAT_EXTMEM_1aa7 = param_1;
  sub_a1db(0x28);
  sub_ee2f();
  sub_0016(DAT_EXTMEM_1aa8,0xf0,0x26);
  sub_a1db(0x27);
  sub_0016();
  sub_a1a3(0x1aa7);
  sub_0016(0x10);
  return;
}

