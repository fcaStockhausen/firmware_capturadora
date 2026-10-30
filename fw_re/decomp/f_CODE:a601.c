
void sub_a601(char param_1)

{
  byte bVar1;
  
  if (param_1 == '\x01') {
    DAT_EXTMEM_1aab = 1;
  }
  else if (param_1 == '\x02') {
    DAT_EXTMEM_1aab = 2;
  }
  else if (param_1 == '\b') {
    DAT_EXTMEM_1aab = 0x10;
  }
  else if (param_1 == '\0') {
    DAT_EXTMEM_1aab = 4;
  }
  DAT_EXTMEM_1aaa = param_1;
  sub_a1b4();
  sub_ee2f();
  sub_e971(10);
  sub_a1b6(0x26);
  sub_ee2f();
  sub_e971(10);
  sub_ee2f(DAT_EXTMEM_1aab,0xf0,0x27);
  sub_a1b4();
  sub_0016();
  sub_a1a3(0x1aaa);
  sub_ee2f(0x10);
  bVar1 = DAT_EXTMEM_1c5a;
  *(undefined1 *)CONCAT11(-0x2f - (((0xf8 < DAT_EXTMEM_1c5a) << 7) >> 7),DAT_EXTMEM_1c5a + 7) = 0x2c
  ;
  *(undefined1 *)CONCAT11(-0x2f - (((0xf7 < bVar1) << 7) >> 7),bVar1 + 8) = 0x90;
  return;
}

