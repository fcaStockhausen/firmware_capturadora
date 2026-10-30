
char sub_d0aa(char param_1,char param_2,char param_3,char param_4,char param_5,char param_6,
             char param_7,char param_8)

{
  bool bVar1;
  byte bVar2;
  char cVar3;
  char cVar4;
  
  F0 = 0;
  if (param_1 < '\0') {
    bVar2 = F0;
    F0 = bVar2 ^ 1;
    bVar1 = param_4 != '\0';
    param_4 = -param_4;
    cVar4 = param_3 - ((bVar1 << 7) >> 7);
    param_3 = -cVar4;
    cVar4 = param_2 - (((cVar4 != '\0') << 7) >> 7);
    param_2 = -cVar4;
    param_1 = -(param_1 - (((cVar4 != '\0') << 7) >> 7));
  }
  if (param_5 < '\0') {
    bVar2 = F0;
    F0 = bVar2 ^ 1;
    sub_d0e0();
    sub_104c();
    cVar4 = -(param_1 -
             (((param_2 != ((param_3 != ((param_4 != '\0') << 7) >> 7) << 7) >> 7) << 7) >> 7));
  }
  else {
    cVar4 = sub_104c(param_1,param_2,param_3,param_4);
  }
  cVar3 = F0;
  if (cVar3 != '\0') {
    cVar4 = -(param_5 -
             (((param_6 != ((param_7 != ((param_8 != '\0') << 7) >> 7) << 7) >> 7) << 7) >> 7));
  }
  return cVar4;
}

