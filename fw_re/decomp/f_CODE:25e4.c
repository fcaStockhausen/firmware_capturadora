
char sub_25e4(byte *param_1,byte param_2,char param_3)

{
  return param_3 + ((char)((ushort)*param_1 * 0x15 >> 8) -
                   ((CARRY1(param_2,(byte)((ushort)*param_1 * 0x15)) << 7) >> 7));
}

