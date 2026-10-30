
char sub_e7a6(void)

{
  char cVar1;
  byte bVar2;
  
  bVar2 = 0xbc;
  sub_d953(0xe0);
  sub_1112(0x1c);
  cVar1 = BANK0_R7;
  if (3 < bVar2) {
    cVar1 = '\x04';
  }
  return bVar2 - cVar1;
}

