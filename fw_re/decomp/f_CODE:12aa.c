
void sub_12aa(undefined2 param_1,byte param_2,char param_3,char param_4)

{
  byte bVar1;
  
  bVar1 = (byte)param_1;
  if (param_4 == '\x01') {
    sub_125f((char)((ushort)param_1 >> 8) + (param_3 - ((CARRY1(bVar1,param_2) << 7) >> 7)),
             bVar1 + param_2);
    return;
  }
  if (param_4 == '\0') {
    FUN_CODE_1518(param_2 + bVar1);
    return;
  }
  if (param_4 == -2) {
    FUN_CODE_1531(param_2 + bVar1);
    return;
  }
  return;
}

