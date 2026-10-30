
void sub_6541(byte param_1)

{
  char cVar1;
  byte bVar2;
  char cVar3;
  char in_PSW;
  undefined1 uVar4;
  undefined2 uVar5;
  
  if (_2_5 != '\0') {
    uVar5 = 0x265;
    sub_6daf(DAT_CODE_0266,0x265);
    while( true ) {
      uVar4 = (undefined1)((ushort)uVar5 >> 8);
      sub_6dde();
      if (-1 < in_PSW) break;
      in_PSW = (0x9c < param_1) << 7;
      uVar5 = CONCAT11(uVar4,param_1 + 99);
      cVar1 = sub_6dc5(2,uVar5);
      if (cVar1 == '\0') {
        sub_6e39();
      }
    }
    DAT_EXTMEM_1065 = 0;
    DAT_EXTMEM_1066 = 0;
    DAT_EXTMEM_1067 = 0;
    DAT_EXTMEM_106b = 1;
    DAT_EXTMEM_106c = 0;
    DAT_EXTMEM_1053 = 0;
    DAT_EXTMEM_1054 = 0;
    DAT_EXTMEM_1055 = 0;
    DAT_EXTMEM_1059 = 1;
    DAT_EXTMEM_105a = 0;
    DAT_EXTMEM_119a = 0xff;
    return;
  }
  sub_6da4();
  bVar2 = sub_6e7f();
  if (bVar2 == 5) {
    sub_6db4(DAT_CODE_0750,DAT_CODE_0751);
    while( true ) {
      bVar2 = DAT_EXTMEM_1312 - (((DAT_EXTMEM_1a77 < DAT_EXTMEM_1313) << 7) >> 7);
      cVar1 = (DAT_EXTMEM_1a76 < bVar2) << 7;
      if (DAT_EXTMEM_1a76 >= bVar2) break;
      cVar1 = (DAT_EXTMEM_1a76 - (((0xb1 < DAT_EXTMEM_1a77) << 7) >> 7)) + '\a';
      cVar1 = sub_6dd3(CONCAT11(cVar1,DAT_EXTMEM_1a77 + 0x42),
                       *(undefined1 *)CONCAT11(cVar1,DAT_EXTMEM_1a77 + 0x4e));
      if (cVar1 == '\0') {
        sub_6e39();
      }
    }
    sub_6dbd(DAT_EXTMEM_1a76 - bVar2);
    while (sub_6e86(), cVar1 < '\0') {
      sub_6e95(0xf44a);
      cVar3 = sub_6dd6();
      if (cVar3 == '\0') {
        sub_6e39();
      }
    }
    if (DAT_EXTMEM_119d != '\0') {
      DAT_INTMEM_30 = 1;
      DAT_INTMEM_31 = 1;
      DAT_INTMEM_32 = 0;
      DAT_EXTMEM_1331 = 0;
      DAT_EXTMEM_1332 = 4;
      return;
    }
    if (DAT_EXTMEM_11a1 < 2) {
      DAT_INTMEM_30 = 1;
      DAT_INTMEM_31 = 1;
      DAT_INTMEM_32 = 0;
      return;
    }
  }
  else {
    if (bVar2 != 3) {
      uVar5 = 0x72e;
      sub_6db0(0x72e,DAT_CODE_072f);
      while( true ) {
        uVar4 = (undefined1)((ushort)uVar5 >> 8);
        sub_6dde();
        if (-1 < in_PSW) break;
        in_PSW = (0xd3 < bVar2) << 7;
        uVar5 = CONCAT11(uVar4,bVar2 + 0x2c);
        cVar1 = sub_6dc5(7,uVar5);
        if (cVar1 == '\0') {
          sub_6e39();
        }
      }
      DAT_INTMEM_30 = 1;
      DAT_INTMEM_31 = 1;
      DAT_INTMEM_32 = 0;
      DAT_EXTMEM_1343 = 2;
      return;
    }
    uVar5 = 0x280;
    sub_6daf(DAT_CODE_0281,0x280);
    while( true ) {
      uVar4 = (undefined1)((ushort)uVar5 >> 8);
      sub_6dde();
      if (-1 < in_PSW) break;
      in_PSW = (0x81 < bVar2) << 7;
      uVar5 = CONCAT11(uVar4,bVar2 + 0x7e);
      cVar1 = sub_6dc5(2,uVar5);
      if (cVar1 == '\0') {
        sub_6e39();
      }
    }
    sub_6dbd();
    while (sub_6e86(), in_PSW < '\0') {
      sub_6e95(0xf464);
      cVar1 = sub_6dd6();
      if (cVar1 == '\0') {
        sub_6e39();
      }
    }
    if (DAT_EXTMEM_119d != '\0') {
      DAT_INTMEM_30 = 1;
      DAT_INTMEM_31 = 1;
      DAT_INTMEM_32 = 0;
      DAT_EXTMEM_1331 = 0;
      DAT_EXTMEM_1332 = 0xc;
      return;
    }
    if ((DAT_EXTMEM_11a1 < 2) << 7 < '\0') {
      DAT_INTMEM_30 = 1;
      DAT_INTMEM_31 = 1;
      DAT_INTMEM_32 = 0;
      return;
    }
  }
  DAT_EXTMEM_1332 = DAT_EXTMEM_11a1 * DAT_INTMEM_4b * '\x04';
  DAT_EXTMEM_1331 = 0;
  DAT_INTMEM_31 = 1;
  DAT_INTMEM_30 = 1;
  DAT_INTMEM_32 = 0;
  return;
}

