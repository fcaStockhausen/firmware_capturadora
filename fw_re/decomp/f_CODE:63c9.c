
void sub_63c9(char param_1)

{
  undefined1 uVar1;
  char cVar2;
  byte bVar3;
  
  bVar3 = _1_6 << 7;
  _0_3 = _1_6 & 1;
  sub_ec2c();
  _0_4 = bVar3 >> 7;
  sub_ee36();
  _0_5 = -((char)bVar3 >> 7);
  if (DAT_EXTMEM_268b == '\x01') {
    if (_0_4 == 1) {
      if (DAT_EXTMEM_2002 != 'F') {
        DAT_EXTMEM_268b = '\0';
      }
    }
    else if ((DAT_EXTMEM_2002 == '\0') << 7 < '\0') {
      DAT_EXTMEM_268b = '\0';
      DAT_EXTMEM_2004 = '\x01';
    }
    else {
      DAT_EXTMEM_2002 = DAT_EXTMEM_2002 + -1;
      if (DAT_EXTMEM_2002 == '\0') {
        sub_e925();
        _0_6 = 1;
        sub_ea6c();
        _0_6 = 1;
        sub_ea80();
        sub_3177();
        sub_2fea();
        sub_c6eb(0xf0,0x22,1,DAT_EXTMEM_236e);
      }
    }
    goto LAB_CODE_64f0;
  }
  if (DAT_EXTMEM_268b == '\x02') {
    DAT_EXTMEM_2003 = DAT_EXTMEM_2003 + -1;
    if ((DAT_EXTMEM_2003 == '\0') || (_0_4 != 1)) {
      if (((_0_3 == 1) || (_0_4 != 0)) && (_0_5 != 0)) {
        _0_6 = 1;
      }
      else {
        _0_6 = 0;
      }
      sub_e440();
      sub_6521();
      DAT_EXTMEM_2004 = '\0';
    }
    goto LAB_CODE_64f0;
  }
  cVar2 = (0xfd < DAT_EXTMEM_268b - 2U) << 7;
  if ((DAT_EXTMEM_268b - 2U != 0xfe) || (_0_4 != 1)) goto LAB_CODE_64f0;
  sub_ec0e(0);
  sub_31ba();
  sub_5bd5();
  if (cVar2 < '\0') {
    sub_2fe6(0xe5,5,0x20,0x1a);
    DAT_EXTMEM_1af4 = 0;
    sub_31c6(3);
    sub_3438();
    sub_31c8(0x4a,0x24,1);
    param_1 = '\x02';
    uVar1 = 0;
LAB_CODE_643c:
    sub_0d92(uVar1);
  }
  else {
    sub_ed82(100);
    sub_31ba();
    sub_5bd5();
    if (-1 < cVar2) {
      sub_3177();
      param_1 = '\0';
      uVar1 = 0xf;
      goto LAB_CODE_643c;
    }
  }
  sub_c6eb(0x4a,0x24,1,DAT_EXTMEM_24c8);
  cVar2 = sub_341a();
  if (((cVar2 == BANK0_R7) && (cVar2 = sub_3424(), cVar2 == BANK0_R6)) && (DAT_EXTMEM_2004 == '\0'))
  {
    sub_6521();
  }
  else {
    sub_3347();
    _0_6 = 0;
    sub_e440();
    DAT_EXTMEM_2003 = '(';
    DAT_EXTMEM_268b = '\x02';
  }
LAB_CODE_64f0:
  bVar3 = _1_2;
  if (_0_5 != 0) {
    bVar3 = _1_2 & 1 ^ 1;
  }
  if ((char)(bVar3 << 7) < '\0') {
    _1_2 = _0_5 & 1;
    cVar2 = sub_341a();
    if (((cVar2 != BANK0_R7) || (cVar2 = sub_3424(), cVar2 != param_1)) && (_1_2 != 0)) {
      sub_3347();
    }
    if (((_0_3 == 1) || (_0_4 != 0)) && (_0_5 != 0)) {
      _0_6 = 1;
    }
    else {
      _0_6 = 0;
    }
    sub_e440();
  }
  return;
}

