
void sub_d766(char param_1,byte param_2,char param_3,char param_4)

{
  byte bVar1;
  char cVar2;
  char in_PSW;
  
  sub_9c59();
  if (in_PSW < '\0') {
    bVar1 = sub_9c68(0x1bb8);
    cVar2 = bVar1 + 0x19;
    sub_0e44(0x32,param_3 - (((0xe6 < bVar1) << 7) >> 7));
    DAT_EXTMEM_f6c2 = cVar2;
  }
  else if (param_2 < 0x65) {
    sub_9c16(param_2 + 0x9b,0x1bb8);
    sub_9bec();
    DAT_EXTMEM_f6c2 = param_1 + param_4;
  }
  DAT_EXTMEM_1c0a = param_2;
  return;
}

