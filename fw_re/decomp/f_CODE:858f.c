
void sub_858f(byte param_1,char param_2,char param_3,byte param_4)

{
  sub_0db8(param_1 + param_4,param_2 + (param_3 - ((CARRY1(param_1,param_4) << 7) >> 7)));
  return;
}

