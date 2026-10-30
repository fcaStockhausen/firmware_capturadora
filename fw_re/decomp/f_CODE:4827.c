
char sub_4827(byte param_1,char *param_2,byte param_3)

{
  return (*param_2 - ((CARRY1(param_1,param_3) << 7) >> 7)) -
         (((0xf7 < param_1 + param_3) << 7) >> 7);
}

