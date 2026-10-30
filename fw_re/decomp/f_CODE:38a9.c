
void sub_38a9(undefined1 param_1,char param_2,char param_3)

{
  byte bVar1;
  char in_PSW;
  
  bVar1 = sub_0ec5(param_1,param_3 - (in_PSW >> 7));
  sub_0f75(param_2 << 1 | CARRY1(bVar1,bVar1),bVar1 * '\x02');
  return;
}

