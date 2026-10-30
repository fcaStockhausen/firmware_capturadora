
byte sub_6c38(void)

{
  bool bVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  char cVar5;
  byte bVar6;
  byte bVar7;
  
  DAT_EXTMEM_1ab4 = sub_3a72(&LAB_CODE_1ab2);
  _0_1 = '\0';
  DAT_EXTMEM_1ab6 = DAT_EXTMEM_1ab4;
  DAT_EXTMEM_1ab8 = DAT_EXTMEM_1ab4;
  DAT_EXTMEM_1ab9 = DAT_EXTMEM_1ab4;
  for (; bVar6 = DAT_EXTMEM_1ab4 - (7 - DAT_EXTMEM_1ab6), DAT_EXTMEM_1ab4 < 7 - DAT_EXTMEM_1ab6;
      DAT_EXTMEM_1ab4 = DAT_EXTMEM_1ab4 + 1) {
    cVar5 = '\0';
    cVar4 = '\0';
    cVar3 = '\0';
    cVar2 = '\x02';
    sub_e7dc(bVar6);
    if (((cVar2 != '\0' || cVar3 != '\0') || cVar4 != '\0') || cVar5 != '\0') {
      DAT_EXTMEM_1ab6 = 2;
    }
    for (DAT_EXTMEM_1ab5 = 0; bVar6 = DAT_EXTMEM_1ab5 - 3, DAT_EXTMEM_1ab5 < 3;
        DAT_EXTMEM_1ab5 = DAT_EXTMEM_1ab5 + 1) {
      sub_9310(DAT_EXTMEM_1ab2,DAT_EXTMEM_1ab3,DAT_EXTMEM_1ab5);
      bVar6 = 2;
      sub_d1b5();
      if ((char)bVar6 < '\0') {
        DAT_EXTMEM_1ab7 = bVar6;
        return bVar6;
      }
      DAT_EXTMEM_1ab7 = bVar6;
      if ((bVar6 & 1) != 1) {
        _0_1 = '\x01';
        break;
      }
    }
    if (_0_1 == '\x01') break;
  }
  if (_0_1 != '\x01') {
    return bVar6;
  }
  sub_6d69(bVar6,0xd);
  sub_3905();
  sub_d9ef(1);
  if ((char)DAT_EXTMEM_1ab7 < '\0') {
    bVar6 = sub_ed52();
  }
  else {
    if ((DAT_EXTMEM_1ab7 & 1) != 0) {
      DAT_EXTMEM_1ab8 = DAT_EXTMEM_1ab8 | 1;
    }
    bVar6 = 0xf;
    bVar7 = sub_6d69(0xf);
    if ((char)bVar7 < '\0') {
      return bVar7;
    }
    if ((DAT_EXTMEM_1ab7 & 1) == 0) {
      cVar2 = sub_3a79();
      if (cVar2 != '\0') goto LAB_CODE_6d43;
    }
    else {
      DAT_EXTMEM_1ab8 = DAT_EXTMEM_1ab8 | 2;
    }
    sub_9310(DAT_EXTMEM_1ab2,DAT_EXTMEM_1ab3,0xe);
    bVar6 = 4;
    sub_d1b5();
    DAT_EXTMEM_1ab7 = bVar6;
    if (-1 < (char)bVar6) {
      if ((bVar6 & 1) != 0) {
        DAT_EXTMEM_1ab8 = DAT_EXTMEM_1ab8 | 4;
      }
      cVar2 = sub_3a79();
      if (cVar2 == '\0') {
        bVar1 = DAT_EXTMEM_1ab2 < 0xcU - (((DAT_EXTMEM_1ab3 < 0xe5) << 7) >> 7);
        if ((!bVar1) &&
           (bVar6 = 0x30 - (((DAT_EXTMEM_1ab3 < 0xd4U - ((bVar1 << 7) >> 7)) << 7) >> 7),
           DAT_EXTMEM_1ab2 < bVar6)) {
          return DAT_EXTMEM_1ab2 - bVar6;
        }
        return 0;
      }
LAB_CODE_6d43:
      return bVar6 | 1;
    }
  }
  return bVar6;
}

