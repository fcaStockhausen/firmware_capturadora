
char * sub_0088(byte param_1,undefined1 param_2,byte param_3,char *param_4)

{
  char cVar1;
  undefined1 *puVar2;
  byte bVar3;
  char *pcVar4;
  byte *pbVar5;
  byte bVar6;
  byte bVar7;
  byte *pbVar8;
  byte *pbVar9;
  
  nop();
  bVar3 = (param_1 | param_3) & 0x4f;
  if (_a_5 == '\x01') {
    if (!CARRY1(bVar3,(byte)param_4)) {
      nop();
      nop();
      nop();
      nop();
      nop();
      nop();
      nop();
      nop();
      nop();
      nop();
      nop();
      nop();
      nop();
      nop();
      nop();
      nop();
      nop();
      nop();
      nop();
      *param_4 = *param_4 + '\x01';
      if (((char)((_0_6 ^ 1) << 7) < '\0') || ((char)(((_0_6 ^ 1) & 1 & ~_0_5) << 7) < '\0')) {
        nop();
        BANK0_R0 = BANK0_R0 + '\x01';
      }
      nop();
      BANK0_R0 = BANK0_R0 + '\x01';
      nop();
      nop();
      return *(char **)CONCAT11((param_3 >> 1 | param_3 << 7) >> 1 | (param_3 >> 1) * -0x80,param_2)
      ;
    }
    return param_4 + bVar3;
  }
  BANK1_R2 = BANK1_R2 | bVar3;
  if (_4_0 == '\x01') {
    param_4 = param_4 + '\x01';
    *param_4 = *param_4 + '\x01';
    *param_4 = *param_4 + '\x01';
    puVar2 = &DAT_INTMEM_7f;
    do {
      *puVar2 = 0;
      puVar2 = puVar2 + -1;
    } while (puVar2 != (undefined1 *)0x0);
    SP = 0x4b;
    pbVar8 = &DAT_CODE_2aa3;
    while( true ) {
      bVar3 = 1;
      bVar6 = *pbVar8;
      if (bVar6 == 0) break;
      bVar7 = bVar6 & 0x3f;
      pbVar9 = pbVar8 + 1;
      if (bVar7 >> 5 != 0) {
        bVar3 = bVar6 & 0x1f;
        bVar7 = pbVar8[1];
        pbVar9 = pbVar8 + 2;
        if (bVar7 != 0) {
          bVar3 = bVar3 + 1;
        }
      }
      pbVar8 = pbVar9;
      cVar1 = CARRY1(bVar6 & 0xc0,bVar6 & 0xc0) << 7;
      if ((bVar6 & 0x40) == 0) {
        pbVar5 = (byte *)*pbVar8;
        pbVar8 = pbVar8 + 1;
        do {
          bVar3 = *pbVar8;
          pbVar8 = pbVar8 + 1;
          if (cVar1 < '\0') {
            *(byte *)ZEXT12(pbVar5) = bVar3;
          }
          else {
            *pbVar5 = bVar3;
          }
          pbVar5 = pbVar5 + '\x01';
          bVar7 = bVar7 - 1;
        } while (bVar7 != 0);
      }
      else if (cVar1 < '\0') {
        do {
          bVar3 = *pbVar8;
          pbVar8 = pbVar8 + 1;
          pbVar5 = (byte *)((bVar3 & 0x7f) >> 3 | 0x20);
          bVar6 = *(byte *)((ushort)((bVar3 & 7) + 0xc) + 0xa51e);
          if ((char)bVar3 < '\0') {
            bVar6 = bVar6 | *pbVar5;
          }
          else {
            bVar6 = ~bVar6 & *pbVar5;
          }
          *pbVar5 = bVar6;
          bVar7 = bVar7 - 1;
        } while (bVar7 != 0);
      }
      else {
        pbVar9 = *(byte **)pbVar8;
        pbVar8 = pbVar8 + 2;
        do {
          do {
            bVar6 = *pbVar8;
            pbVar8 = pbVar8 + 1;
            *pbVar9 = bVar6;
            pbVar9 = pbVar9 + 1;
            bVar7 = bVar7 - 1;
          } while (bVar7 != 0);
          bVar3 = bVar3 - 1;
        } while (bVar3 != 0);
      }
    }
    pcVar4 = (char *)FUN_CODE_4f20();
    return pcVar4;
  }
  nop();
  nop();
  nop();
  if (_0_0 != '\0') {
    _0_0 = '\0';
  }
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  pcVar4 = (char *)thunk_FUN_CODE_0086();
  return pcVar4;
}

