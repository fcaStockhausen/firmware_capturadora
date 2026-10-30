
void sub_cb93(char param_1)

{
  byte bVar1;
  char cVar2;
  short sVar3;
  
  sVar3 = 0x1ae2;
  DAT_EXTMEM_1ae2 = param_1;
  sub_ea2d(BANK0_R7);
  bVar1 = BANK0_R7;
  cVar2 = BANK0_R5;
  sub_ea2d();
  *(byte *)(sVar3 + 1) = cVar2 * '\x04' | bVar1;
  sub_ee2f(0x20,0xf0,5);
  sub_ee2f(0x20,0xf0,0xd);
  sub_e279(DAT_EXTMEM_1ae3,0xf,0xf0,0x3c);
  sub_e279(DAT_EXTMEM_1ae2 << 4 | 8,0xf8,0xf0,0x3d);
  return;
}

