
void sub_aba2(char param_1,char param_2)

{
  DAT_EXTMEM_1aaa = param_1;
  sub_e279(param_2 * '\x02',6,0xf5,0xea);
  DAT_EXTMEM_f5e5 = 0x51;
  if (DAT_EXTMEM_1aaa == '\x03') {
    sub_e279(0x10,0x70,0xf5,8);
  }
  else {
    sub_0016(0x70,0xf5,8);
  }
  if (DAT_EXTMEM_1aaa == '\0') {
    sub_0016();
  }
  else {
    sub_ee2f(4,0xf5,7);
  }
  sub_ac16(0x32,0x3f);
  sub_e279(1,7,0xf5,0x10);
  sub_ac16(0,0xf);
  sub_ee2f(8,0xf5,0x10);
  sub_0016(2,0xf5,0x14);
  return;
}

