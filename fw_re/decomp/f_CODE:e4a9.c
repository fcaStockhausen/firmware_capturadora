
void sub_e4a9(char param_1,byte param_2)

{
  byte bVar1;
  
  sub_b80b();
  bVar1 = sub_9f00();
  bVar1 = sub_9f76((char)((ushort)param_2 * 0x15) + bVar1 + 3,8,(char)((ushort)param_2 * 0x15 >> 8),
                   param_1 - (((0xfc < bVar1) << 7) >> 7));
  if ((bVar1 & 1) != 0) {
    return;
  }
  return;
}

