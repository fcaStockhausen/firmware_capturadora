
void sub_907f(char param_1,char param_2,byte param_3,byte param_4)

{
  byte bVar1;
  byte bVar2;
  char cVar3;
  
  cVar3 = param_1 + -1;
  bVar1 = 0xff - (((param_1 != '\0') << 7) >> 7);
  bVar2 = 0xff - ((CARRY1(param_4,bVar1) << 7) >> 7);
  sub_1112(8,param_2 + (-1 - ((CARRY1(param_3,bVar2) << 7) >> 7)),param_3 + bVar2,param_4 + bVar1);
  DAT_EXTMEM_f80a = cVar3;
  return;
}

