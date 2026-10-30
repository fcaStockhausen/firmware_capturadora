
void sub_e33f(char param_1,char param_2,byte param_3,byte param_4)

{
  byte bVar1;
  
  bVar1 = param_1 - (((param_4 < param_2 + 1U) << 7) >> 7);
  if (bVar1 <= param_3) {
    sub_ee2f();
    sub_ee2f(0x80,0xf5,0x82);
    return;
  }
  sub_0016(param_3 - bVar1,0x22,0xf5,0x8e);
  sub_0016(0x80,0xf5,0x82);
  return;
}

