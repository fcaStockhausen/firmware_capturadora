
byte sub_dbde(void)

{
  byte bVar1;
  
  bVar1 = 0xbc;
  sub_d953(0xe0);
  sub_1112(7);
  DAT_EXTMEM_1ae5 = bVar1 & 6;
  sub_d953(0xe1,0x80);
  sub_10de();
  bVar1 = sub_397c(3);
  return bVar1 | DAT_EXTMEM_1ae5;
}

