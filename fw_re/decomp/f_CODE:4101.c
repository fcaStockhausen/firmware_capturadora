
char sub_4101(byte param_1,char param_2)

{
  return param_2 - ((CARRY1(param_1,DAT_EXTMEM_1af2) << 7) >> 7);
}

