
/* WARNING: Instruction at (CODE,0xf001) overlaps instruction at (CODE,0xf000)
    */

undefined1
sub_f000(byte param_1,byte param_2,byte *param_3,undefined1 *param_4,byte param_5,char param_6,
        byte param_7,undefined1 param_8,char param_9)

{
  byte *pbVar1;
  char cVar2;
  char cVar3;
  byte bVar4;
  byte bVar5;
  byte in_PSW;
  
code_c0xf000:
  TH1 = param_7;
  do {
    TH1 = param_7;
    TH1 = param_7;
    TH1 = param_7;
    TH1 = param_7;
    TH1 = param_7;
    TH1 = param_7;
    TH1 = param_7;
    TH1 = param_7;
    TH1 = param_7;
    TH1 = param_7;
    TH1 = param_7;
    TH1 = param_7;
    TH1 = param_7;
    TH1 = param_7;
    TH1 = param_7;
    TH1 = param_7;
    pbVar1 = param_3;
code_c0xf022:
    do {
      TH1 = param_7;
      TH1 = param_7;
      TH1 = param_7;
      TH1 = param_7;
      TH1 = param_7;
      TH1 = param_7;
      param_3 = pbVar1;
      if (_2_6 == '\x01') goto code_c0xf049;
      while( true ) {
        cVar2 = param_6 + -1;
        param_3 = pbVar1 + -1;
        bVar4 = param_1 - 1;
        if (_3_4 == '\x01') {
          TL1 = *param_4;
          P1_4 = in_PSW >> 7;
          goto code_c0xefe2;
        }
        param_6 = param_6 + -2;
        in_PSW = (0xdd < bVar4) << 7;
        bVar5 = param_1 + 0x21;
        if (_4_6 == '\x01') {
          param_1 = *param_3;
          *param_3 = bVar5;
          pbVar1 = param_3;
          goto code_c0xf022;
        }
        if (0xdd < bVar4) break;
        in_PSW = CARRY1(bVar5,param_5) << 7;
        bVar5 = bVar5 + param_5;
        if (_b_6 == '\0') goto code_c0xf0ab;
        bVar4 = *param_3;
        *param_3 = bVar5 + ('^' - ((char)in_PSW >> 7));
        in_PSW = 0;
        param_1 = bVar4;
        if (param_2 != 0) {
          param_1 = bVar4 / param_2;
          param_2 = bVar4 % param_2;
        }
        if (param_1 == 0) {
          bVar4 = *param_3;
          *param_3 = 0;
          bVar5 = *param_3;
          *param_3 = bVar4;
          bVar4 = *param_3;
          *param_3 = bVar5;
          bVar5 = *param_3;
          *param_3 = bVar4;
          bVar4 = *param_3;
          *param_3 = bVar5;
          bVar5 = *param_3;
          *param_3 = bVar4;
          bVar4 = *param_3;
          *param_3 = bVar5;
          bVar5 = *param_3;
          *param_3 = bVar4;
          bVar4 = *param_3;
          *param_3 = bVar5;
          bVar5 = *param_3;
          *param_3 = bVar4;
          bVar4 = *param_3;
          *param_3 = bVar5;
          bVar5 = *param_3;
          *param_3 = bVar4;
          bVar4 = *param_3;
          *param_3 = bVar5;
          bVar5 = *param_3;
          *param_3 = bVar4;
          goto code_c0xf08b;
        }
        TH1 = param_7;
        TH1 = param_7;
        TH1 = param_7;
        TH1 = param_7;
        TH1 = param_7;
        TH1 = param_7;
        TH1 = param_7;
        TH1 = param_7;
        TH1 = param_7;
        TH1 = param_7;
        TH1 = param_7;
        TH1 = param_7;
        TH1 = param_7;
        TH1 = param_7;
        TH1 = param_7;
        TH1 = param_7;
        TH1 = param_7;
        TH1 = param_7;
        TH1 = param_7;
        TH1 = param_7;
        TH1 = param_7;
        TH1 = param_7;
        bINTMEM20 = param_7;
        *param_3 = *param_3 - 1;
        pbVar1 = pbVar1 + -2;
      }
      pbVar1 = param_3;
      param_1 = bVar5;
    } while (_5_4 == '\0');
    if (_c_2 != '\0') break;
code_c0xf08b:
    bVar4 = *param_3;
    *param_3 = bVar5;
    bVar5 = *param_3;
    *param_3 = bVar4;
    bVar4 = *param_3;
    *param_3 = bVar5;
    bVar5 = *param_3;
    *param_3 = bVar4;
    bVar4 = *param_3;
    *param_3 = bVar5;
    bVar5 = *param_3;
    *param_3 = bVar4;
    bVar4 = *param_3;
    *param_3 = bVar5;
    bVar5 = *param_3;
    *param_3 = bVar4;
    bVar4 = *param_3;
    *param_3 = bVar5;
    bVar5 = *param_3;
    *param_3 = bVar4;
    bVar4 = *param_3;
    *param_3 = bVar5;
    bVar5 = *param_3;
    *param_3 = bVar4;
    bVar4 = *param_3;
    *param_3 = bVar5;
    bVar5 = *param_3;
    *param_3 = bVar4;
    bVar4 = *param_3;
    *param_3 = bVar5;
    bVar5 = *param_3;
    *param_3 = bVar4;
    bVar4 = *param_3;
    *param_3 = bVar5;
    bVar5 = *param_3;
    *param_3 = bVar4;
    bVar4 = *param_3;
    *param_3 = bVar5;
    bVar5 = *param_3;
    *param_3 = bVar4;
    bVar4 = *param_3;
    *param_3 = bVar5;
    bVar5 = *param_3;
    *param_3 = bVar4;
    bVar4 = *param_3;
    *param_3 = bVar5;
    bVar5 = *param_3;
    *param_3 = bVar4;
    bVar4 = *param_3;
    *param_3 = bVar5;
    bVar5 = *param_3;
    *param_3 = bVar4;
    bVar4 = *param_3;
    *param_3 = bVar5;
    bVar5 = *param_3;
    *param_3 = bVar4;
    bVar4 = *param_3;
    *param_3 = bVar5;
    bVar5 = *param_3;
    *param_3 = bVar4;
    bVar4 = *param_3;
    *param_3 = bVar5;
    bVar5 = *param_3;
    *param_3 = bVar4;
code_c0xf0ab:
    bVar4 = *param_3;
    *param_3 = bVar5;
    bVar5 = *param_3;
    *param_3 = bVar4;
    param_1 = *param_3;
    *param_3 = bVar5;
    nop();
    nop();
    nop();
    nop();
    param_9 = param_9 + -1;
    nop();
    param_7 = 0;
    nop();
    param_1 = param_1 + 1;
  } while( true );
  bVar5 = bVar5 | param_5;
  param_5 = param_5 + 1;
  in_PSW = CARRY1(bVar5,param_5) << 7;
  param_1 = bVar5 + param_5;
  if (!CARRY1(bVar5,param_5)) {
    cVar2 = sub_d018(cVar2);
    if (cVar2 == 'l') {
      DAT_EXTMEM_1fc2 = 7;
    }
    else if ((cCODE001e == 'A') && (param_9 == 'u')) {
      DAT_EXTMEM_1fc2 = 8;
    }
    else {
      cVar2 = sub_d00a();
      if (cVar2 == 'S') {
        DAT_EXTMEM_1fc2 = 9;
      }
      else if (param_9 == 'O') {
        DAT_EXTMEM_1fc2 = 10;
      }
      else {
        cVar2 = sub_d00a();
        if (cVar2 == 'N') {
          DAT_EXTMEM_1fc2 = 0xb;
        }
        else {
          DAT_EXTMEM_1fc2 = 99;
          if (param_9 == 'D') {
            DAT_EXTMEM_1fc2 = 0xc;
          }
        }
      }
    }
    if (cCODE001e == '?') {
      DAT_EXTMEM_1fc3 = 'c';
    }
    else {
      bVar4 = sub_d000();
      if (((bVar4 ^ 0x80) < 0xb0) << 7 < '\0') {
        cVar2 = '\0';
      }
      else {
        cVar2 = (bVar4 - 0x30) * '\n';
      }
      cVar3 = sub_d000();
      DAT_EXTMEM_1fc3 = cVar3 + -0x30 + cVar2;
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
      cVar2 = ((DAT_INTMEM_2d < 4) << 7) >> 7;
      if ((byte)-cVar2 <= DAT_INTMEM_2c) {
        sub_1b67(DAT_INTMEM_2c + cVar2);
        if ((_1_4 != '\x01') && ((DAT_EXTMEM_f015 >> 4 & 1) != 1)) {
          sub_ee27();
        }
        DAT_INTMEM_2c = 0;
        DAT_INTMEM_2d = 0;
      }
      cVar2 = ((DAT_INTMEM_27 < 10) << 7) >> 7;
      if ((byte)-cVar2 <= DAT_INTMEM_26) {
        sub_bfba(DAT_INTMEM_26 + cVar2);
        DAT_INTMEM_26 = 0;
        DAT_INTMEM_27 = 0;
      }
      sub_b525();
    } while( true );
  }
code_c0xf049:
  param_1 = param_1 ^ *param_3;
  param_5 = 0x78;
  in_PSW = (in_PSW >> 7 | _c_6) << 7;
  if (param_1 == 0) {
    bVar4 = 0;
code_c0xefe2:
    _b_0 = in_PSW >> 7;
    bVar5 = ES;
    DAT_SFR_aa = param_8;
    UNK_SFR_92 = param_9;
    BANK0_R1 = param_7;
    return *(undefined1 *)
            ((ushort)((bVar4 ^ param_7) - (param_9 - ((char)((in_PSW >> 7 | bVar5 ^ 1) << 7) >> 7)))
            + 0xefeb);
  }
  goto code_c0xf000;
}

