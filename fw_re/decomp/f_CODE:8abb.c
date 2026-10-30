
void sub_8abb(void)

{
  byte bVar1;
  char cVar2;
  
  _0_1 = '\0';
  DAT_EXTMEM_1aab = '\0';
  DAT_EXTMEM_1aac = 0;
  DAT_EXTMEM_1aad = 0;
  DAT_EXTMEM_1aae = '\0';
  DAT_EXTMEM_1aaf = 0;
  DAT_EXTMEM_1aaa = 0;
  while( true ) {
    cVar2 = (DAT_EXTMEM_1aaa < 0x20) << 7;
    if (DAT_EXTMEM_1aaa >= 0x20) break;
    sub_ea03(DAT_EXTMEM_1aaa - 0x20);
    sub_e90e();
    sub_edf4();
    sub_e971(0x3c);
    sub_ee59();
    if (cVar2 < '\0') {
      if (DAT_EXTMEM_1aae == '\0') {
        DAT_EXTMEM_1aac = DAT_EXTMEM_1aac + 1;
      }
      DAT_EXTMEM_1aaf = DAT_EXTMEM_1aaf + 1;
      _0_1 = '\x01';
    }
    else {
      if (DAT_EXTMEM_1aad + 1 <= DAT_EXTMEM_1aaf) {
        DAT_EXTMEM_1aab = DAT_EXTMEM_1aae;
        DAT_EXTMEM_1aad = DAT_EXTMEM_1aaf;
      }
      DAT_EXTMEM_1aae = DAT_EXTMEM_1aaa + 1;
      DAT_EXTMEM_1aaf = 0;
      _0_1 = '\0';
    }
    DAT_EXTMEM_1aaa = DAT_EXTMEM_1aaa + 1;
  }
  bVar1 = DAT_EXTMEM_1aaa;
  if (_0_1 != '\0') {
    bVar1 = DAT_EXTMEM_1aaf;
    if (0x80U - (((DAT_EXTMEM_1aac + DAT_EXTMEM_1aaf < DAT_EXTMEM_1aad + 1) << 7) >> 7) <=
        (CARRY1(DAT_EXTMEM_1aac,DAT_EXTMEM_1aaf) ^ 0x80U)) {
      DAT_EXTMEM_1aab = DAT_EXTMEM_1aae;
      DAT_EXTMEM_1aad = DAT_EXTMEM_1aaf + DAT_EXTMEM_1aac;
    }
  }
  if (DAT_EXTMEM_1aad == 0) {
    sub_ce33(bVar1);
    sub_e90e();
    return;
  }
  DAT_EXTMEM_1aaa = DAT_EXTMEM_1aab + (DAT_EXTMEM_1aad >> 1) & 0x1f;
  sub_ea03(DAT_EXTMEM_1aaa);
  sub_e90e();
  return;
}

