
/* WARNING: Instruction at (CODE,0xf002) overlaps instruction at (CODE,0xf001)
    */

undefined1
sub_f45a(byte param_1,byte param_2,byte *param_3,undefined1 *param_4,byte param_5,char param_6,
        byte param_7,undefined1 param_8,char param_9)

{
  char cVar1;
  byte bVar2;
  char cVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  char in_PSW;
  
  nop();
  nop();
  nop();
  bVar2 = param_9 - (in_PSW >> 7);
  bVar6 = (param_1 | (byte)param_3) + bVar2;
  nop();
  nop();
  bVar4 = param_6 - ((CARRY1(param_1 | (byte)param_3,bVar2) << 7) >> 7);
  bVar2 = CARRY1(bVar6,bVar4) << 7;
  bVar6 = bVar6 + bVar4;
  nop();
  nop();
  nop();
  nop();
sub_f000_1:
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
  param_3 = param_3 + -1;
  do {
    cVar1 = param_6 + -1;
    param_3 = param_3 + -1;
    bVar4 = bVar6 - 1;
    if (_3_4 == '\x01') {
      TL1 = *param_4;
      P1_4 = bVar2 >> 7;
code_c0xefe2:
      _b_0 = bVar2 >> 7;
      bVar6 = ES;
      DAT_SFR_aa = param_8;
      UNK_SFR_92 = param_9;
      BANK0_R1 = param_7;
      return *(undefined1 *)
              ((ushort)((bVar4 ^ param_7) - (param_9 - ((char)((bVar2 >> 7 | bVar6 ^ 1) << 7) >> 7))
                       ) + 0xefeb);
    }
    param_6 = param_6 + -2;
    bVar2 = (0xdd < bVar4) << 7;
    bVar5 = bVar6 + 0x21;
    if (_4_6 == '\x01') {
      bVar6 = *param_3;
      *param_3 = bVar5;
      goto code_c0xf022;
    }
    if (0xdd >= bVar4) break;
    bVar6 = bVar5;
    if (_5_4 == '\0') goto code_c0xf022;
    if (_c_2 == '\0') goto code_c0xf08b;
    bVar5 = bVar5 | param_5;
    param_5 = param_5 - ((char)bVar2 >> 7);
    bVar2 = CARRY1(bVar5,param_5) << 7;
    bVar6 = bVar5 + param_5;
    if (!CARRY1(bVar5,param_5)) {
      cVar1 = sub_d018(cVar1);
      if (cVar1 == 'l') {
        DAT_EXTMEM_1fc2 = 7;
      }
      else if ((cCODE001e == 'A') && (param_9 == 'u')) {
        DAT_EXTMEM_1fc2 = 8;
      }
      else {
        cVar1 = sub_d00a();
        if (cVar1 == 'S') {
          DAT_EXTMEM_1fc2 = 9;
        }
        else if (param_9 == 'O') {
          DAT_EXTMEM_1fc2 = 10;
        }
        else {
          cVar1 = sub_d00a();
          if (cVar1 == 'N') {
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
        bVar2 = sub_d000();
        if (((bVar2 ^ 0x80) < 0xb0) << 7 < '\0') {
          cVar1 = '\0';
        }
        else {
          cVar1 = (bVar2 - 0x30) * '\n';
        }
        cVar3 = sub_d000();
        DAT_EXTMEM_1fc3 = cVar3 + -0x30 + cVar1;
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
        cVar1 = ((DAT_INTMEM_2d < 4) << 7) >> 7;
        if ((byte)-cVar1 <= DAT_INTMEM_2c) {
          sub_1b67(DAT_INTMEM_2c + cVar1);
          if ((_1_4 != '\x01') && ((DAT_EXTMEM_f015 >> 4 & 1) != 1)) {
            sub_ee27();
          }
          DAT_INTMEM_2c = 0;
          DAT_INTMEM_2d = 0;
        }
        cVar1 = ((DAT_INTMEM_27 < 10) << 7) >> 7;
        if ((byte)-cVar1 <= DAT_INTMEM_26) {
          sub_bfba(DAT_INTMEM_26 + cVar1);
          DAT_INTMEM_26 = 0;
          DAT_INTMEM_27 = 0;
        }
        sub_b525();
      } while( true );
    }
    do {
      bVar6 = bVar6 ^ *param_3;
      param_5 = 0x78;
      bVar2 = (bVar2 >> 7 | _c_6) << 7;
      if (bVar6 == 0) {
        bVar4 = 0;
        goto code_c0xefe2;
      }
      TH1 = param_7;
code_c0xf002:
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
code_c0xf022:
      TH1 = param_7;
      TH1 = param_7;
      TH1 = param_7;
      TH1 = param_7;
      TH1 = param_7;
      TH1 = param_7;
    } while (_2_6 == '\x01');
  } while( true );
  bVar2 = CARRY1(bVar5,param_5) << 7;
  bVar5 = bVar5 + param_5;
  if (_b_6 == '\0') goto code_c0xf0ab;
  bVar4 = *param_3;
  *param_3 = bVar5 + ('^' - ((char)bVar2 >> 7));
  bVar2 = 0;
  bVar6 = bVar4;
  if (param_2 != 0) {
    bVar6 = bVar4 / param_2;
    param_2 = bVar4 % param_2;
  }
  if (bVar6 == 0) {
    bVar6 = *param_3;
    *param_3 = 0;
    bVar4 = *param_3;
    *param_3 = bVar6;
    bVar6 = *param_3;
    *param_3 = bVar4;
    bVar4 = *param_3;
    *param_3 = bVar6;
    bVar6 = *param_3;
    *param_3 = bVar4;
    bVar4 = *param_3;
    *param_3 = bVar6;
    bVar6 = *param_3;
    *param_3 = bVar4;
    bVar4 = *param_3;
    *param_3 = bVar6;
    bVar6 = *param_3;
    *param_3 = bVar4;
    bVar4 = *param_3;
    *param_3 = bVar6;
    bVar6 = *param_3;
    *param_3 = bVar4;
    bVar4 = *param_3;
    *param_3 = bVar6;
    bVar6 = *param_3;
    *param_3 = bVar4;
    bVar5 = *param_3;
    *param_3 = bVar6;
code_c0xf08b:
    bVar6 = *param_3;
    *param_3 = bVar5;
    bVar4 = *param_3;
    *param_3 = bVar6;
    bVar6 = *param_3;
    *param_3 = bVar4;
    bVar4 = *param_3;
    *param_3 = bVar6;
    bVar6 = *param_3;
    *param_3 = bVar4;
    bVar4 = *param_3;
    *param_3 = bVar6;
    bVar6 = *param_3;
    *param_3 = bVar4;
    bVar4 = *param_3;
    *param_3 = bVar6;
    bVar6 = *param_3;
    *param_3 = bVar4;
    bVar4 = *param_3;
    *param_3 = bVar6;
    bVar6 = *param_3;
    *param_3 = bVar4;
    bVar4 = *param_3;
    *param_3 = bVar6;
    bVar6 = *param_3;
    *param_3 = bVar4;
    bVar4 = *param_3;
    *param_3 = bVar6;
    bVar6 = *param_3;
    *param_3 = bVar4;
    bVar4 = *param_3;
    *param_3 = bVar6;
    bVar6 = *param_3;
    *param_3 = bVar4;
    bVar4 = *param_3;
    *param_3 = bVar6;
    bVar6 = *param_3;
    *param_3 = bVar4;
    bVar4 = *param_3;
    *param_3 = bVar6;
    bVar6 = *param_3;
    *param_3 = bVar4;
    bVar4 = *param_3;
    *param_3 = bVar6;
    bVar6 = *param_3;
    *param_3 = bVar4;
    bVar4 = *param_3;
    *param_3 = bVar6;
    bVar6 = *param_3;
    *param_3 = bVar4;
    bVar4 = *param_3;
    *param_3 = bVar6;
    bVar6 = *param_3;
    *param_3 = bVar4;
    bVar4 = *param_3;
    *param_3 = bVar6;
    bVar6 = *param_3;
    *param_3 = bVar4;
    bVar4 = *param_3;
    *param_3 = bVar6;
    bVar6 = *param_3;
    *param_3 = bVar4;
    bVar5 = *param_3;
    *param_3 = bVar6;
code_c0xf0ab:
    bVar6 = *param_3;
    *param_3 = bVar5;
    bVar4 = *param_3;
    *param_3 = bVar6;
    bVar6 = *param_3;
    *param_3 = bVar4;
    nop();
    nop();
    nop();
    nop();
    param_9 = param_9 + -1;
    nop();
    param_7 = 0;
    nop();
    bVar6 = bVar6 + 1;
    goto code_c0xf002;
  }
  goto sub_f000_1;
}

