
void sub_c6eb(byte param_1)

{
  char cVar1;
  byte bVar2;
  
  sub_3883(0x1ae2);
  if ((param_1 < 4) << 7 < '\0') {
    DAT_EXTMEM_1ae5 = 0xfe < param_1;
    cVar1 = '\a';
    bVar2 = param_1 + 1;
    do {
      DAT_EXTMEM_1ae6 = bVar2 << 1;
      DAT_EXTMEM_1ae5 = DAT_EXTMEM_1ae5 << 1 | bVar2 >> 7;
      cVar1 = cVar1 + -1;
      bVar2 = DAT_EXTMEM_1ae6;
    } while (cVar1 != '\0');
  }
  else {
    DAT_EXTMEM_1ae5 = 2;
    DAT_EXTMEM_1ae6 = 0;
  }
  sub_ee2f(0x80,0xf0,0x62);
  sub_379a(0x1ae2,DAT_EXTMEM_1ae5,DAT_EXTMEM_1ae6);
  sub_cd55(0xf9,0);
  sub_0016(0x80,0xf0,0x62);
  return;
}

