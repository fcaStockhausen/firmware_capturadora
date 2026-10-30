
void sub_2628(byte param_1,undefined1 *param_2,byte param_3,char param_4,undefined1 param_5)

{
  byte bVar1;
  
  bVar1 = (byte)((ushort)param_1 * 0x15);
  *param_2 = param_5;
  param_2[1] = param_4 + ((char)((ushort)param_1 * 0x15 >> 8) - ((CARRY1(bVar1,param_3) << 7) >> 7))
  ;
  param_2[2] = bVar1 + param_3;
  return;
}

