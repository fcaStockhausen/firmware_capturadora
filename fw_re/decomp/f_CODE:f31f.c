
/* WARNING: Instruction at (CODE,0xf012) overlaps instruction at (CODE,0xf011)
    */

undefined1
sub_f31f(byte param_1,byte param_2,undefined1 *param_3,undefined1 *param_4,undefined1 *param_5,
        char param_6,byte param_7,byte param_8,char param_9)

{
  byte *pbVar1;
  undefined1 *puVar2;
  char cVar3;
  char cVar4;
  undefined1 *puVar5;
  undefined1 *puVar6;
  byte bVar7;
  undefined1 *puVar8;
  byte bVar9;
  undefined1 uVar10;
  char in_PSW;
  byte bVar11;
  
  bVar11 = 0xc0 - (in_PSW >> 7);
  puVar8 = (undefined1 *)(param_1 - bVar11);
  if (param_1 < bVar11) {
    param_3 = (undefined1 *)((byte)puVar8 & 0x73);
    bVar11 = (param_1 < bVar11 | _2_3) << 7;
    param_6 = param_6 + '\x01';
    *(undefined1 **)ZEXT12(param_3) = param_3;
    bVar9 = EPCON;
    EPCON = bVar9 & 0x77;
    param_7 = param_7 - 1;
    pbVar1 = (byte *)0xcf;
    puVar2 = param_3;
    if (param_5 != (undefined1 *)0x0) {
      nop();
      param_4 = param_5;
      puVar8 = param_5;
      goto LAB_CODE_f35f;
    }
  }
  else {
    nop();
    nop();
    puVar2 = param_5;
LAB_CODE_f35f:
    param_5 = param_4;
    pbVar1 = puVar8 + (char)param_5;
    nop();
    puVar2 = puVar2 + '\x01';
    nop();
    bVar9 = (char)param_5 - ((CARRY1((byte)puVar8,(byte)param_5) << 7) >> 7);
    bVar11 = (pbVar1 + bVar9 < pbVar1 + -((CARRY1((byte)pbVar1,bVar9) << 7) >> 7)) << 7;
    nop();
    param_7 = param_7 + 1;
    if (_0_0 != '\0') {
      _0_0 = '\0';
    }
    nop();
    bVar9 = (char)(pbVar1 + bVar9) - (char)(pbVar1 + -((CARRY1((byte)pbVar1,bVar9) << 7) >> 7)) |
            param_8;
    if (_0_0 != '\x01') {
      nop();
      nop();
      nop();
      uVar10 = FUN_CODE_f3a8(bVar9 + 1);
      return uVar10;
    }
    if (_0_1 != '\0') {
      pbVar1 = pbVar1 + '\x01';
      nop();
      nop();
      nop();
      if ((bVar9 < (byte)(param_6 - ((char)bVar11 >> 7))) << 7 < '\0') {
        nop();
        nop();
      }
      else {
        param_6 = param_6 + '\x01';
        _0_0 = '\0';
      }
      nop();
      bVar11 = 0;
    }
    if (-1 < (char)bVar11) goto LAB_CODE_f394;
    param_8 = param_8 + 1;
  }
  pbVar1 = pbVar1 + '\x01';
LAB_CODE_f394:
  nop();
  nop();
  nop();
  puVar8 = param_5;
  if (param_5 == (undefined1 *)0x0) {
    nop();
  }
  else {
    param_9 = param_9 + '\x01';
    if (_0_0 != '\0') {
      _0_0 = '\0';
    }
  }
LAB_CODE_f010_1:
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
  *pbVar1 = *pbVar1 - 1;
  pbVar1 = pbVar1 + -1;
  do {
    cVar3 = param_6 + -1;
    pbVar1 = pbVar1 + -1;
    puVar5 = puVar8 + -1;
    if (_3_4 == '\x01') {
      TL1 = *param_3;
      P1_4 = bVar11 >> 7;
code_c0xefe2:
      _b_0 = bVar11 >> 7;
      bVar9 = ES;
      DAT_SFR_aa = param_8;
      UNK_SFR_92 = param_9;
      BANK0_R1 = param_7;
      return *(undefined1 *)
              ((ushort)(((byte)puVar5 ^ param_7) -
                       (param_9 - ((char)((bVar11 >> 7 | bVar9 ^ 1) << 7) >> 7))) + 0xefeb);
    }
    param_6 = param_6 + -2;
    bVar11 = ((undefined1 *)0xdd < puVar5) << 7;
    puVar6 = puVar8 + '!';
    if (_4_6 == '\x01') {
      puVar8 = (undefined1 *)*pbVar1;
      *pbVar1 = (byte)puVar6;
      goto code_c0xf022;
    }
    if ((undefined1 *)0xdd >= puVar5) break;
    puVar8 = puVar6;
    if (_5_4 == '\0') goto code_c0xf022;
    if (_c_2 == '\0') goto code_c0xf08b;
    bVar7 = (byte)puVar6 | (byte)param_5;
    bVar9 = (char)param_5 - ((char)bVar11 >> 7);
    bVar11 = CARRY1(bVar7,bVar9) << 7;
    puVar8 = (undefined1 *)(bVar7 + bVar9);
    if (!CARRY1(bVar7,bVar9)) {
      cVar3 = sub_d018(puVar2,cVar3,param_8);
      if (cVar3 == 'l') {
        DAT_EXTMEM_1fc2 = 7;
      }
      else if ((cCODE001e == 'A') && (param_9 == 'u')) {
        DAT_EXTMEM_1fc2 = 8;
      }
      else {
        cVar3 = sub_d00a();
        if (cVar3 == 'S') {
          DAT_EXTMEM_1fc2 = 9;
        }
        else if (param_9 == 'O') {
          DAT_EXTMEM_1fc2 = 10;
        }
        else {
          cVar3 = sub_d00a();
          if (cVar3 == 'N') {
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
        bVar11 = sub_d000();
        if (((bVar11 ^ 0x80) < 0xb0) << 7 < '\0') {
          cVar3 = '\0';
        }
        else {
          cVar3 = (bVar11 - 0x30) * '\n';
        }
        cVar4 = sub_d000();
        DAT_EXTMEM_1fc3 = cVar4 + -0x30 + cVar3;
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
        cVar3 = ((DAT_INTMEM_2d < 4) << 7) >> 7;
        if ((byte)-cVar3 <= DAT_INTMEM_2c) {
          sub_1b67(DAT_INTMEM_2c + cVar3);
          if ((_1_4 != '\x01') && ((DAT_EXTMEM_f015 >> 4 & 1) != 1)) {
            sub_ee27();
          }
          DAT_INTMEM_2c = 0;
          DAT_INTMEM_2d = 0;
        }
        cVar3 = ((DAT_INTMEM_27 < 10) << 7) >> 7;
        if ((byte)-cVar3 <= DAT_INTMEM_26) {
          sub_bfba(DAT_INTMEM_26 + cVar3);
          DAT_INTMEM_26 = 0;
          DAT_INTMEM_27 = 0;
        }
        sub_b525();
      } while( true );
    }
    do {
      puVar8 = (undefined1 *)((byte)puVar8 ^ *pbVar1);
      param_5 = (undefined1 *)0x78;
      bVar11 = (bVar11 >> 7 | _c_6) << 7;
      if (puVar8 == (undefined1 *)0x0) {
        puVar5 = (undefined1 *)0x0;
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
  bVar11 = CARRY1((byte)puVar6,(byte)param_5) << 7;
  puVar6 = puVar6 + (char)param_5;
  if (_b_6 == '\0') goto code_c0xf0ab;
  puVar5 = (undefined1 *)*pbVar1;
  *pbVar1 = (byte)(puVar6 + ('^' - ((char)bVar11 >> 7)));
  bVar11 = 0;
  puVar8 = puVar5;
  if (param_2 != 0) {
    puVar8 = (undefined1 *)((byte)puVar5 / param_2);
    param_2 = (byte)puVar5 % param_2;
  }
  if (puVar8 == (undefined1 *)0x0) {
    bVar9 = *pbVar1;
    *pbVar1 = 0;
    bVar7 = *pbVar1;
    *pbVar1 = bVar9;
    bVar9 = *pbVar1;
    *pbVar1 = bVar7;
    bVar7 = *pbVar1;
    *pbVar1 = bVar9;
    bVar9 = *pbVar1;
    *pbVar1 = bVar7;
    bVar7 = *pbVar1;
    *pbVar1 = bVar9;
    bVar9 = *pbVar1;
    *pbVar1 = bVar7;
    bVar7 = *pbVar1;
    *pbVar1 = bVar9;
    bVar9 = *pbVar1;
    *pbVar1 = bVar7;
    bVar7 = *pbVar1;
    *pbVar1 = bVar9;
    bVar9 = *pbVar1;
    *pbVar1 = bVar7;
    bVar7 = *pbVar1;
    *pbVar1 = bVar9;
    bVar9 = *pbVar1;
    *pbVar1 = bVar7;
    puVar6 = (undefined1 *)*pbVar1;
    *pbVar1 = bVar9;
code_c0xf08b:
    bVar9 = *pbVar1;
    *pbVar1 = (byte)puVar6;
    bVar7 = *pbVar1;
    *pbVar1 = bVar9;
    bVar9 = *pbVar1;
    *pbVar1 = bVar7;
    bVar7 = *pbVar1;
    *pbVar1 = bVar9;
    bVar9 = *pbVar1;
    *pbVar1 = bVar7;
    bVar7 = *pbVar1;
    *pbVar1 = bVar9;
    bVar9 = *pbVar1;
    *pbVar1 = bVar7;
    bVar7 = *pbVar1;
    *pbVar1 = bVar9;
    bVar9 = *pbVar1;
    *pbVar1 = bVar7;
    bVar7 = *pbVar1;
    *pbVar1 = bVar9;
    bVar9 = *pbVar1;
    *pbVar1 = bVar7;
    bVar7 = *pbVar1;
    *pbVar1 = bVar9;
    bVar9 = *pbVar1;
    *pbVar1 = bVar7;
    bVar7 = *pbVar1;
    *pbVar1 = bVar9;
    bVar9 = *pbVar1;
    *pbVar1 = bVar7;
    bVar7 = *pbVar1;
    *pbVar1 = bVar9;
    bVar9 = *pbVar1;
    *pbVar1 = bVar7;
    bVar7 = *pbVar1;
    *pbVar1 = bVar9;
    bVar9 = *pbVar1;
    *pbVar1 = bVar7;
    bVar7 = *pbVar1;
    *pbVar1 = bVar9;
    bVar9 = *pbVar1;
    *pbVar1 = bVar7;
    bVar7 = *pbVar1;
    *pbVar1 = bVar9;
    bVar9 = *pbVar1;
    *pbVar1 = bVar7;
    bVar7 = *pbVar1;
    *pbVar1 = bVar9;
    bVar9 = *pbVar1;
    *pbVar1 = bVar7;
    bVar7 = *pbVar1;
    *pbVar1 = bVar9;
    bVar9 = *pbVar1;
    *pbVar1 = bVar7;
    bVar7 = *pbVar1;
    *pbVar1 = bVar9;
    bVar9 = *pbVar1;
    *pbVar1 = bVar7;
    bVar7 = *pbVar1;
    *pbVar1 = bVar9;
    bVar9 = *pbVar1;
    *pbVar1 = bVar7;
    puVar6 = (undefined1 *)*pbVar1;
    *pbVar1 = bVar9;
code_c0xf0ab:
    bVar9 = *pbVar1;
    *pbVar1 = (byte)puVar6;
    bVar7 = *pbVar1;
    *pbVar1 = bVar9;
    bVar9 = *pbVar1;
    *pbVar1 = bVar7;
    nop();
    nop();
    nop();
    nop();
    param_9 = param_9 + -1;
    nop();
    param_7 = 0;
    nop();
    puVar8 = (undefined1 *)(bVar9 + 1);
    goto code_c0xf002;
  }
  TH1 = param_7;
  TH1 = param_7;
  TH1 = param_7;
  TH1 = param_7;
  TH1 = param_7;
  TH1 = param_7;
  TH1 = param_7;
  TH1 = param_7;
  goto LAB_CODE_f010_1;
}

