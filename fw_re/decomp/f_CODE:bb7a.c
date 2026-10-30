
void sub_bb7a(byte param_1,undefined1 *param_2,char param_3,undefined1 param_4)

{
  *param_2 = param_4;
  param_2[1] = param_3 - (((0x1f < param_1) << 7) >> 7);
  param_2[2] = param_1 - 0x20;
  return;
}

