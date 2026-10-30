
char sub_2693(byte *param_1,byte param_2,char param_3)

{
  return param_3 + ((char)((ushort)*param_1 * 0x15 >> 8) -
                   ((CARRY1((byte)((ushort)*param_1 * 0x15),param_2) << 7) >> 7));
}

