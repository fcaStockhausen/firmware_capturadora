
void sub_3fd1(byte param_1,undefined1 *param_2,char param_3,undefined1 param_4,char param_5,
             byte param_6)

{
  *param_2 = param_4;
  param_2[1] = param_5 + (param_3 - ((CARRY1(param_1,param_6) << 7) >> 7));
  param_2[2] = param_1 + param_6;
  return;
}

