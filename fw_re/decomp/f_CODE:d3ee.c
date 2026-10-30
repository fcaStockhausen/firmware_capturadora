
undefined1 sub_d3ee(undefined1 param_1,byte param_2,char param_3)

{
  byte bVar1;
  char in_PSW;
  
  bVar1 = sub_0ec5(param_1,param_3 - (in_PSW >> 7));
  sub_0f75(param_2 >> 1,bVar1 >> 1 | param_2 << 7);
  return DAT_EXTMEM_1ae7;
}

