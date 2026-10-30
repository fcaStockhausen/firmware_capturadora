
char sub_268d(byte param_1,byte *param_2,char param_3)

{
  return (param_3 - (((0xfc < param_1) << 7) >> 7)) +
         ((char)((ushort)*param_2 * 0x15 >> 8) -
         ((CARRY1((byte)((ushort)*param_2 * 0x15),param_1 + 3) << 7) >> 7));
}

