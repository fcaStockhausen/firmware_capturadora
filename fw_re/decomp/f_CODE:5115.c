
void sub_5115(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5,byte param_6)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  byte bVar4;
  char cVar5;
  byte bVar6;
  byte bVar7;
  char cVar8;
  undefined1 uVar9;
  char cVar10;
  
  DAT_EXTMEM_1105 = param_6;
  sub_d131();
  bVar4 = 0x11;
  DAT_EXTMEM_1116 = param_6;
  sub_2700(10,0x11);
  sub_25a7();
  sub_25eb();
  sub_287d();
  uVar3 = BANK0_R7;
  uVar2 = BANK0_R6;
  uVar1 = BANK0_R5;
  uVar9 = BANK0_R4;
  sub_282d(0x1105);
  sub_25eb();
  sub_2795();
  sub_27a4();
  sub_2a3e();
  BANK0_R3 = uVar3;
  BANK0_R2 = uVar2;
  BANK0_R1 = uVar1;
  BANK0_R0 = uVar9;
  sub_2807(sub_1112);
  bVar6 = sub_25b0();
  bVar7 = sub_278f(bVar6);
  if (4 < bVar7) {
    sub_25e4(bVar7 - 5,0x1105);
    DAT_EXTMEM_1117 = sub_273d();
    sub_25f8(sub_1112);
    uVar9 = BANK0_R0;
    sub_2857(DAT_EXTMEM_1117);
    param_1 = 0x16;
    sub_27eb(0x16);
    BANK0_R0 = uVar9;
    sub_2607(sub_1112);
  }
  bVar7 = sub_25c4(sub_1112);
  sub_25f8(0x1106);
  bVar7 = bVar7 | param_2;
  param_5 = param_5 | bVar4;
  sub_25a3(param_3 | param_1,sub_1112,param_4 | bVar6,param_5);
  sub_25eb();
  cVar8 = sub_2795();
  if (cVar8 == '\0') {
    sub_125f(0x110e);
    nop();
    nop();
    cVar8 = sub_d018(param_3 + 1);
    if (cVar8 == 'l') {
      DAT_EXTMEM_1fc2 = 7;
    }
    else if ((cCODE001e == 'A') && (bVar7 == 0x75)) {
      DAT_EXTMEM_1fc2 = 8;
    }
    else {
      cVar8 = sub_d00a();
      if (cVar8 == 'S') {
        DAT_EXTMEM_1fc2 = 9;
      }
      else if (bVar7 == 0x4f) {
        DAT_EXTMEM_1fc2 = 10;
      }
      else {
        cVar8 = sub_d00a();
        if (cVar8 == 'N') {
          DAT_EXTMEM_1fc2 = 0xb;
        }
        else {
          DAT_EXTMEM_1fc2 = 99;
          if (bVar7 == 0x44) {
            DAT_EXTMEM_1fc2 = 0xc;
          }
        }
      }
    }
    if (cCODE001e == '?') {
      DAT_EXTMEM_1fc3 = 'c';
    }
    else {
      bVar6 = sub_d000();
      if (((bVar6 ^ 0x80) < 0xb0) << 7 < '\0') {
        cVar8 = '\0';
      }
      else {
        cVar8 = (bVar6 - 0x30) * '\n';
      }
      cVar5 = sub_d000();
      DAT_EXTMEM_1fc3 = cVar5 + -0x30 + cVar8;
    }
    sub_eae4();
    sub_eb9c();
    DAT_EXTMEM_1aa6 = 0;
    DAT_EXTMEM_1aa5 = 8;
    sub_7c18(0xa5,0x1a,1);
    sub_c33c(0);
    sub_eb30(1);
    sub_ee8e(7);
    sub_ee91(9);
    sub_0006();
    sub_e78a(0x2a,0,0xff);
    sub_eaf7();
    sub_ecad(0x2a,0,0xff);
    sub_ed82(200);
    sub_ed82(100);
    DAT_INTMEM_4b = 0xf;
    sub_4454();
    thunk_FUN_CODE_ee9a();
    do {
      sub_6eb9();
      cVar8 = ((DAT_INTMEM_2d < 4) << 7) >> 7;
      if ((byte)-cVar8 <= DAT_INTMEM_2c) {
        sub_1b67(DAT_INTMEM_2c + cVar8);
        if ((_1_4 != '\x01') && ((DAT_EXTMEM_f015 >> 4 & 1) != 1)) {
          sub_ee27();
        }
        DAT_INTMEM_2c = 0;
        DAT_INTMEM_2d = 0;
      }
      cVar8 = ((DAT_INTMEM_27 < 10) << 7) >> 7;
      if ((byte)-cVar8 <= DAT_INTMEM_26) {
        sub_bfba(DAT_INTMEM_26 + cVar8);
        DAT_INTMEM_26 = 0;
        DAT_INTMEM_27 = 0;
      }
      sub_b525();
    } while( true );
  }
  if ((((DAT_EXTMEM_1105 == 3) || (DAT_EXTMEM_1105 == 2)) || (DAT_EXTMEM_1105 == 4)) ||
     ((DAT_EXTMEM_1105 == 6 || (DAT_EXTMEM_1105 == 9)))) {
    sub_25c4(0x110e);
    sub_27f4(0x110e);
  }
  if ((DAT_EXTMEM_119d == '\0') && (DAT_EXTMEM_1105 == 7)) {
    uVar9 = sub_25c4(0x110e);
                    /* WARNING: Subroutine does not return */
    sub_1253(param_3,0x110e,param_5 | 2,uVar9);
  }
  cVar5 = (DAT_EXTMEM_1105 < 2) << 7;
  cVar10 = DAT_EXTMEM_1105 - 2;
  if ((cVar5 < '\0') || (cVar5 = (cVar8 == '\0') << 7, cVar10 = '\x01', cVar8 == '\x01')) {
    sub_25c4(cVar10,0x110e);
    sub_270e(0x110e);
  }
  sub_25a7();
  sub_25eb();
  sub_2a47();
  if (-1 < cVar5) {
    cVar8 = sub_2795();
    if (cVar8 == '\x02') {
      sub_25c4(0x110e);
      sub_2946(0x110e);
    }
  }
  sub_25f8(0x110e);
  uVar3 = BANK0_R3;
  uVar2 = BANK0_R2;
  uVar1 = BANK0_R1;
  uVar9 = BANK0_R0;
  sub_25a7();
  sub_25eb();
  sub_2940();
  sub_27d9(0x1116);
  BANK0_R0 = uVar9;
  BANK0_R1 = uVar1;
  BANK0_R2 = uVar2;
  BANK0_R3 = uVar3;
  sub_2595();
  sub_25eb();
  cVar8 = sub_2940();
  if (cVar8 != '\0') {
    sub_25f8(sub_1112);
    uVar9 = BANK0_R0;
    sub_27a4(DAT_EXTMEM_1105 >> 1);
    sub_2a51();
    BANK0_R0 = uVar9;
    sub_2619(sub_1112);
  }
  sub_25a7();
  sub_25eb();
                    /* WARNING: Subroutine does not return */
  sub_0dd1(0x15);
}

