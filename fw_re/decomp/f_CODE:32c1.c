
char sub_32c1(char *param_1,char param_2,byte param_3)

{
  return *param_1 - (param_2 - ((((byte)param_1[1] < param_3) << 7) >> 7));
}

