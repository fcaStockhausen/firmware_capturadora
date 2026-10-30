
char sub_a32a(byte param_1,char *param_2,char param_3)

{
  return *param_2 - (param_3 - ((((byte)param_2[1] < param_1) << 7) >> 7));
}

