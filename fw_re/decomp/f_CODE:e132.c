
void sub_e132(void)

{
  byte bVar1;
  char cVar2;
  
  sub_3052();
  sub_3264();
  sub_31a6();
  cVar2 = DAT_INTMEM_30;
  if (DAT_INTMEM_30 == '\x01') {
    bVar1 = EA;
    DAT_EXTMEM_1aab = bVar1 & 1;
    EA = 0;
    sub_7e18();
    cVar2 = DAT_EXTMEM_1aab - 1;
    EA = DAT_EXTMEM_1aab != 0;
  }
  sub_30f0(cVar2);
  return;
}

