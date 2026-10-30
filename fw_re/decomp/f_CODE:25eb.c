
char sub_25eb(byte param_1,char param_2,char param_3,byte param_4)

{
  return param_3 + (param_2 - ((CARRY1(param_1,param_4) << 7) >> 7));
}

