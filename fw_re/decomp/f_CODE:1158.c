
void sub_1158(undefined2 param_1,byte param_2,char param_3,char param_4)

{
  char cVar1;
  byte bVar2;
  
  bVar2 = (byte)param_1;
  cVar1 = (char)((ushort)param_1 >> 8);
  if (param_4 == '\x01') {
    FUN_CODE_14be(cVar1 + (param_3 - ((CARRY1(bVar2,param_2) << 7) >> 7)),bVar2 + param_2);
    return;
  }
  if (param_4 == '\0') {
    sub_11c6(param_2 + bVar2);
    return;
  }
  if (param_4 == -2) {
    FUN_CODE_14ca(param_2 + bVar2);
    return;
  }
  sub_11d2(cVar1 + (param_3 - ((CARRY1(bVar2,param_2) << 7) >> 7)),bVar2 + param_2);
  return;
}

