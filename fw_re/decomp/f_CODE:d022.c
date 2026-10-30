
char sub_d022(byte param_1,char param_2,char param_3)

{
  char cVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  char cVar5;
  byte bVar6;
  byte in_PSW;
  
  cVar2 = '\0';
  cVar1 = '\0';
  cVar4 = '`';
  cVar3 = '\0';
  cVar5 = '\x03';
  sub_d336(0,0,0,0x60,3);
  bVar6 = sub_125f(0x1b13);
  nop();
  nop();
  nop();
  DAT_INTMEM_7f = DAT_INTMEM_7f & bVar6;
  in_PSW = in_PSW & 0xdd;
  sub_c925(*(undefined1 *)(ushort)param_1);
  sub_125f(0x1b13);
  nop();
  nop();
  nop();
  if ((char)in_PSW < '\0') {
    sub_c925(*(undefined1 *)(ushort)param_1);
    sub_ed52();
    sub_125f(0x1b13);
    nop();
    nop();
    nop();
    nop();
    cVar1 = sub_c925(0xe2,0xe4);
    return cVar1;
  }
  sub_104c();
  cVar1 = param_1 - (((param_2 != ((cVar1 != ((cVar2 != '\0') << 7) >> 7) << 7) >> 7) << 7) >> 7);
  cVar2 = F0;
  if (cVar2 != '\0') {
    cVar1 = cVar3 - (((cVar4 != ((param_3 != ((cVar5 != '\0') << 7) >> 7) << 7) >> 7) << 7) >> 7);
  }
  return -cVar1;
}

