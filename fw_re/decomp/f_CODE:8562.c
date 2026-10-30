
char sub_8562(byte param_1,short param_2,char param_3)

{
  return *(char *)(param_2 + 1) + (param_3 - ((CARRY1(*(byte *)(param_2 + 2),param_1) << 7) >> 7));
}

