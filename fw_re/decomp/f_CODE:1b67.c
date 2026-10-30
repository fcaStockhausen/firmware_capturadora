
void sub_1b67(char param_1,char param_2,char param_3,char param_4)

{
  bool bVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  byte bVar5;
  char cVar6;
  byte bVar7;
  byte bVar8;
  undefined1 uVar9;
  char in_PSW;
  short sVar10;
  
  sub_125f(0x1aa7);
  nop();
  nop();
  nop();
  nop();
  DAT_EXTMEM_1ac9 = 0;
  _0_1 = '\0';
  _0_2 = '\0';
  DAT_EXTMEM_1ae1 = '\0';
  sub_63c9();
  sub_3363();
  if (in_PSW < '\0') {
    sub_e925();
    DAT_EXTMEM_20ab = 0;
    return;
  }
  sub_324f();
  sub_e7dc();
  if (((param_1 != '\0' || param_2 != '\0') || param_3 != '\0') || param_4 != '\0') {
    return;
  }
  bVar8 = DAT_EXTMEM_2405;
  cVar2 = DAT_EXTMEM_2406;
  sub_b739();
  DAT_EXTMEM_1aca = bVar8;
  DAT_EXTMEM_1acb = cVar2;
  if ((((bVar8 & 1) != 0) && (DAT_EXTMEM_264a = DAT_EXTMEM_264a + 1, _1_4 != '\x01')) &&
     (bVar1 = DAT_EXTMEM_2404 < 5, !bVar1)) {
    DAT_EXTMEM_2404 = 0;
    bVar8 = 2 - ((bVar1 << 7) >> 7);
    if (bVar8 <= DAT_EXTMEM_264a) {
      sub_c836(DAT_EXTMEM_264a - bVar8);
      sub_ed82(5);
      DAT_EXTMEM_264a = 0;
      return;
    }
  }
  if (cVar2 < '\0') {
    return;
  }
  if (_1_4 != '\x01') {
    DAT_EXTMEM_20ab = 0;
  }
  cVar6 = 'E';
  cVar4 = ' ';
  sub_d87b();
  cVar2 = '\0';
  cVar3 = '\0';
  sub_342e();
  sub_32f6();
  if (((cVar2 != '\0' || cVar3 != '\0') || cVar4 != '\0') || cVar6 != '\0') {
    if (((_1_4 != '\0') && (_1_7 != '\x01')) &&
       (((DAT_EXTMEM_1aca & 1) != 0 && (DAT_EXTMEM_20ab == 0)))) {
      DAT_EXTMEM_20ab = 1;
    }
    if (DAT_EXTMEM_20ab == 0) {
      _0_2 = '\x01';
    }
  }
  bVar1 = DAT_EXTMEM_20ab == 0;
  cVar2 = DAT_EXTMEM_20ab - 1;
  if (!bVar1) {
    DAT_EXTMEM_20ab = DAT_EXTMEM_20ab + 1;
    bVar8 = 7 - ((bVar1 << 7) >> 7);
    cVar3 = (DAT_EXTMEM_20ab < bVar8) << 7;
    cVar2 = DAT_EXTMEM_20ab - bVar8;
    if (DAT_EXTMEM_20ab >= bVar8) {
      DAT_EXTMEM_20ab = 0;
      cVar2 = sub_ee7d(0xcc,0x1a,1);
      if (cVar3 < '\0') {
        DAT_EXTMEM_1ae5 = 1;
        DAT_EXTMEM_1ae6 = 0x1a;
        DAT_EXTMEM_1ae7 = 0xcc;
        cVar2 = sub_77dd(0x94,0x20,1);
        if (cVar3 < '\0') {
          _0_2 = '\x01';
        }
      }
      else {
        _0_2 = '\x01';
      }
    }
  }
  if (_0_2 != '\0') {
    sub_e925(cVar2);
    sub_ee1f();
    sub_ed98(1);
    _0_3 = 0;
    sub_eb78();
    sub_125f(0x1ae3);
    _0_3 = 1;
    sub_b1b5(0);
    _1_7 = '\x01';
    DAT_EXTMEM_2404 = 0;
    if (_1_4 != '\0') {
      _1_4 = '\0';
    }
  }
  if (_1_4 == '\0') {
    cVar2 = (DAT_EXTMEM_2404 < 0x1e) << 7;
    if (DAT_EXTMEM_2404 < 0x1e) {
      DAT_EXTMEM_2404 = DAT_EXTMEM_2404 + 1;
      return;
    }
    sub_ee7d(DAT_EXTMEM_2404 - 0x1e,0x94,0x20,1);
    _0_1 = -(cVar2 >> 7);
    if (_0_1 == '\x01') {
      _1_4 = 1;
      _1_7 = 1;
      DAT_EXTMEM_20af = sub_33d7();
      _0_3 = 0;
      DAT_EXTMEM_2404 = DAT_EXTMEM_20af;
      sub_eb78();
      uVar9 = sub_125f(0x1ae3);
      sub_204d();
      DAT_EXTMEM_1aae = sub_2025();
      DAT_EXTMEM_1aad = uVar9;
      sub_303f();
      bVar8 = sub_33df();
      if ((bVar8 & 4) == 0) {
        sub_e9ee(0);
      }
      bVar8 = sub_33df();
      if ((bVar8 & 8) == 0) {
        sub_eb0a(0);
      }
      if ((DAT_EXTMEM_1aa9 & 0x80) == 0) {
        sub_ed22(0x1aaa,0,0,0);
      }
      sub_3398();
      sub_d559();
      sub_2007();
      sub_125f();
      nop();
      FUN_CODE_ee00();
      return;
    }
    DAT_EXTMEM_2404 = 0;
  }
  if (_1_4 != '\x01') {
    bVar8 = 0;
    DAT_EXTMEM_20af = 0;
    goto LAB_CODE_1e18;
  }
  cVar2 = (DAT_EXTMEM_20af < 0xf) << 7;
  bVar8 = DAT_EXTMEM_20af - 0xf;
  if (DAT_EXTMEM_20af < 0xf) {
    bVar8 = DAT_EXTMEM_20af + 1;
    DAT_EXTMEM_20af = bVar8;
  }
  bVar7 = 0;
  bVar5 = 0;
  cVar4 = '\0';
  cVar3 = '\x02';
  sub_e7dc(bVar8);
  if (((cVar3 == '\0' && cVar4 == '\0') && bVar5 == 0) && bVar7 == 0) {
    sub_ec59();
    cVar3 = '\0';
    if (bVar7 != 0) goto LAB_CODE_1da8;
  }
  else {
LAB_CODE_1da8:
    sub_ee17();
    cVar3 = ((bVar7 < 0x81) << 7) >> 7;
    bVar1 = bVar5 < (byte)-cVar3;
    cVar2 = bVar1 << 7;
    cVar3 = bVar5 + cVar3;
    if (!bVar1) {
      if (_1_7 != '\x01') {
        sub_206e();
      }
      cVar2 = ((DAT_EXTMEM_22d8 < 0x28) << 7) >> 7;
      bVar8 = DAT_EXTMEM_22d7 + cVar2;
      if (DAT_EXTMEM_22d7 < (byte)-cVar2) {
        DAT_EXTMEM_22d8 = DAT_EXTMEM_22d8 + 1;
        if (DAT_EXTMEM_22d8 == 0) {
          DAT_EXTMEM_22d7 = DAT_EXTMEM_22d7 + 1;
        }
        bVar8 = DAT_EXTMEM_22d7;
        if (DAT_EXTMEM_22d7 == 0) {
          bVar8 = DAT_EXTMEM_22d8 ^ 0x28;
        }
        if (bVar8 == 0) {
          bVar8 = sub_e9ac(0,0,0,0x80);
        }
      }
      goto LAB_CODE_1e18;
    }
  }
  sub_33d7(cVar3);
  bVar8 = sub_ec1d();
  if (cVar2 < '\0') {
    if (_1_7 != '\x01') {
      bVar8 = sub_206e();
    }
  }
  else {
    bVar8 = DAT_EXTMEM_20af - 0xf;
    if ((0xe < DAT_EXTMEM_20af) && (_1_7 != '\0')) {
      _1_7 = '\0';
      sub_ed98(0);
      bVar8 = sub_ee27();
    }
  }
LAB_CODE_1e18:
  if (_1_4 == '\x01') {
    uVar9 = sub_125f(bVar8,0x1ae3);
    sub_204d(uVar9);
    uVar9 = 0;
    if ((DAT_EXTMEM_1aa7 & 0xb) != 0) {
      DAT_EXTMEM_1aae = sub_2025(0x1aaa,DAT_EXTMEM_1aa7 & 0xb,0,0);
      DAT_EXTMEM_1aad = uVar9;
      if ((DAT_EXTMEM_23fd != DAT_EXTMEM_1ab8) && (DAT_EXTMEM_1ab8 == '\x01')) {
        cVar2 = 'h';
        sub_d953(0xe3);
        sub_1112(8);
        DAT_EXTMEM_1ae1 = cVar2;
        if ((cVar2 != '\0') && (cVar2 != '\x01')) {
          DAT_EXTMEM_1ab8 = cVar2;
        }
      }
      cVar2 = DAT_EXTMEM_23f4;
      if ((((DAT_EXTMEM_1aaf != BANK0_R7) || (cVar2 = DAT_EXTMEM_23f7, DAT_EXTMEM_1ab2 != BANK0_R7))
          || (cVar2 = DAT_EXTMEM_23fa, DAT_EXTMEM_1ab5 != BANK0_R7)) ||
         (cVar2 = DAT_EXTMEM_23f9, DAT_EXTMEM_1ab4 != DAT_EXTMEM_23f9)) {
        sub_303f();
        sub_eb42();
        DAT_EXTMEM_1ac3 = cVar2;
        sub_ed98(1);
        sub_3398();
        sub_e897();
        sub_2007();
        sub_125f();
        nop();
        FUN_CODE_ee00();
        return;
      }
    }
    sVar10 = 0x1aaa;
    if ((DAT_EXTMEM_1aa8 & 0xc0) != 0) {
      _0_3 = 1;
      sub_205b();
                    /* WARNING: Subroutine does not return */
      sub_1253(0x1abf);
    }
    sub_ee81(0,0,0);
    sub_342e(0,0,0);
    if (((*(byte *)(sVar10 + 3) & 4) != 0) && ((DAT_EXTMEM_1aaa & 0x18) != 0)) {
      _0_3 = 0;
      sub_205b(0,0,0);
    }
  }
  return;
}

