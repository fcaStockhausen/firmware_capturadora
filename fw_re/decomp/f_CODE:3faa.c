
char sub_3faa(byte param_1,byte param_2)

{
  sub_ed76(param_1);
  return (param_1 ^ 0x80) - (-0x80 - (((param_2 < 0xb) << 7) >> 7));
}

