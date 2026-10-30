
byte sub_93c6(byte param_1,byte param_2,byte param_3,byte param_4)

{
  char cVar1;
  char cVar2;
  byte bVar3;
  byte bVar4;
  
  bVar4 = 0x4e - (((param_4 < 0x21) << 7) >> 7);
  _0_1 = bVar4 <= param_3;
  DAT_EXTMEM_1aad = param_3;
  DAT_EXTMEM_1aae = param_4;
  sub_db7f(param_3 - bVar4);
  sub_ed52();
  DAT_EXTMEM_1aaf = 0;
  DAT_EXTMEM_1ab0 = 0;
  while( true ) {
    bVar3 = 1;
    bVar4 = sub_0eaf(0,0x1aaf);
    cVar1 = ((bVar3 < 10) << 7) >> 7;
    if ((byte)-cVar1 <= bVar4) break;
    sub_396b(bVar4 + cVar1);
    sub_e7dc();
    param_4 = param_1 | param_2 | bVar4 | param_4;
    if (param_4 != 0) {
      return param_4;
    }
    cVar2 = '\0';
    cVar1 = '\0';
    param_2 = 0;
    param_1 = 2;
    sub_e7dc();
    if (((param_1 != 0 || param_2 != 0) || cVar1 != '\0') || cVar2 != '\0') break;
    param_4 = 1;
    sub_ed82();
  }
  bVar4 = DAT_EXTMEM_1aad;
  bVar3 = DAT_EXTMEM_1aae;
  sub_6c38();
  DAT_EXTMEM_1aaf = bVar4;
  DAT_EXTMEM_1ab0 = bVar3;
  DAT_EXTMEM_1ab1 = bVar3;
  if (-1 < (char)bVar3) {
    bVar4 = bVar3 != 0;
    _0_3 = 1;
    sub_3a00(0x1aad);
    sub_95d7();
    DAT_EXTMEM_1ab1 = bVar4;
  }
  sub_37f9(0,0,0,DAT_EXTMEM_1ab1 & 0xf);
  sub_c925(0xe2,0xe4);
  return DAT_EXTMEM_1ab1;
}

