
void sub_d2f7(char param_1,byte param_2,char param_3,char param_4)

{
  byte bVar1;
  char cVar2;
  char in_PSW;
  
  sub_9c59();
  if (in_PSW < '\0') {
    bVar1 = sub_9c68(0x1bbe);
    cVar2 = bVar1 * '\x02' + 0x32;
    sub_0e44(100,(param_3 << 1 | CARRY1(bVar1,bVar1)) - (((0xcd < bVar1 * '\x02') << 7) >> 7));
    DAT_EXTMEM_f6c1 = cVar2;
  }
  else if (param_2 < 0x65) {
    sub_9c16(param_2 + 0x9b,0x1bbe);
    sub_9bec();
    DAT_EXTMEM_f6c1 = param_1 + param_4;
  }
  DAT_EXTMEM_1c0c = param_2;
  return;
}

