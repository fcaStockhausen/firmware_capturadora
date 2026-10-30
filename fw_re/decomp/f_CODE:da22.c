
byte sub_da22(void)

{
  byte bVar1;
  byte bVar2;
  
  sub_ee06();
  DAT_EXTMEM_1aaa = 0;
  do {
    bVar1 = *(byte *)CONCAT11(-0x2f - (((0xf4 < DAT_EXTMEM_1c5a) << 7) >> 7),DAT_EXTMEM_1c5a + 0xb);
    bVar2 = bVar1 >> 1;
    _0_1 = bVar1 & 1;
    if (_0_1 != 0) {
      return bVar2;
    }
    sub_e971(bVar2,10);
    bVar1 = DAT_EXTMEM_1aaa + 1;
    bVar2 = DAT_EXTMEM_1aaa + 0x9d;
    DAT_EXTMEM_1aaa = bVar1;
  } while ((bVar1 < 100) << 7 < '\0');
  return bVar2;
}

