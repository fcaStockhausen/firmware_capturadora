
char sub_84e3(char param_1,char *param_2,byte param_3,char param_4)

{
  *param_2 = param_4;
  param_2[1] = param_1;
  param_2[2] = '\0';
  param_2[3] = param_3 & 3;
  return param_4 + (((param_1 == '\0') << 7) >> 7);
}

