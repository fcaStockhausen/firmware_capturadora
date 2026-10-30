
/* WARNING: Instruction at (CODE,0x04ea) overlaps instruction at (CODE,0x04e9)
    */

byte sub_0338(byte param_1,byte *param_2,byte param_3,char *param_4,char *param_5,char param_6,
             byte param_7,byte param_8,char param_9,char param_10,char param_11)

{
  bool bVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  char cVar5;
  byte bVar6;
  char cVar7;
  char cVar8;
  char cVar9;
  byte bVar10;
  byte bVar11;
  undefined1 *puVar12;
  undefined1 *puVar13;
  byte in_PSW;
  byte bVar14;
  
  cVar2 = BANK2_R6;
  cVar7 = BANK0_R0;
  puVar13 = (undefined1 *)0x0;
  nop();
  BANK2_R6 = BANK2_R6 + -1;
  BANK0_R0 = BANK0_R0 + '\x01';
  nop();
  bVar10 = *param_2;
  cVar9 = param_11 + -1;
  nop();
  bVar6 = param_6 + 1;
  nop();
  BANK1_R2 = BANK1_R2 + '\x01';
  nop();
  if (!CARRY1(param_1 >> 1 | param_1 << 7,param_7 - ((char)in_PSW >> 7))) {
    bVar10 = bVar10 >> 1 | bVar10 << 7;
    nop();
    BANK2_R6 = cVar2 + -2;
    BANK0_R0 = cVar7 + '\x02';
    cVar7 = P2_1;
    if (cVar7 == '\x01') {
      *param_5 = *param_5 + '\x01';
    }
    else {
      nop();
      cVar9 = param_11;
    }
  }
  cVar7 = BANK0_R0;
  nop();
  bVar1 = 0xf8 < bVar10 + param_10;
  bVar14 = in_PSW & 0x5d | bVar1 << 7;
  nop();
  nop();
  BANK0_R0 = BANK0_R0 + '\x01';
  bVar10 = bVar10 + param_10 + 9;
  nop();
  nop();
  BANK1_R2 = BANK1_R2 + '\x01';
  nop();
  BANK0_R2 = param_7;
  if (bVar1) {
LAB_CODE_03a5:
    nop();
    bVar10 = bVar10 + param_10 + 7;
    BANK0_R0 = BANK0_R0 + '\x01';
    nop();
    cVar7 = FIFLG;
    FIFLG = cVar7 + '\x01';
    bVar11 = bVar10 >> 1 | bVar10 * -0x80;
    nop();
    nop();
    bVar14 = in_PSW & 0x5d | (param_4 < &BANK1_R3) << 7;
    nop();
    if (param_4 < &BANK1_R3) {
      nop();
      param_4 = param_4 + '\x01';
      nop();
      nop();
      bVar14 = in_PSW & 0x5d | (param_8 < 0x34) << 7;
      bVar10 = bVar6;
      goto LAB_CODE_03e6;
    }
LAB_CODE_03fd:
    nop();
    if (-1 < (char)bVar14) {
      cVar9 = cVar9 + '\x01';
      goto LAB_CODE_0401;
    }
    *param_4 = BANK1_R6;
    cVar5 = BANK2_R6;
    cVar2 = BANK0_R0;
    nop();
    cVar7 = bVar6 + 1;
    nop();
    BANK1_R2 = BANK1_R2 + '\x01';
    nop();
    puVar12 = puVar13;
    if ((char)bVar14 < '\0') {
LAB_CODE_045d:
      nop();
    }
    else {
      bVar10 = bVar11 >> 1;
      bVar11 = bVar10 | bVar11 << 7;
      nop();
      BANK2_R6 = BANK2_R6 + -1;
      BANK0_R0 = BANK0_R0 + '\x01';
      cVar4 = P2_1;
      if (cVar4 != '\x01') {
        nop();
        if ((char)bVar14 < '\0') {
          nop();
          nop();
          BANK1_R2 = param_8 + 1;
          nop();
          if (-1 < (char)bVar14) {
            bVar10 = bVar11 >> 1 | bVar10 << 7;
            nop();
            BANK2_R6 = cVar5 + -2;
            BANK0_R0 = cVar2 + '\x02';
            cVar7 = P2_1;
            if (cVar7 == '\x01') {
              *param_5 = *param_5 + '\x01';
            }
            else {
              nop();
              if ((char)bVar14 < '\0') {
                nop();
                nop();
                bVar6 = (char)param_4 - ((char)bVar14 >> 7);
                bVar10 = thunk_FUN_CODE_032c((bVar10 + bVar6) -
                                             (param_7 - ((CARRY1(bVar10,bVar6) << 7) >> 7)),BANK0_R0
                                             ,cVar9);
                *param_4 = *param_4 + '\x01';
                nop();
                nop();
                nop();
                nop();
                return bVar10;
              }
              cVar9 = cVar9 + '\x01';
            }
          }
          nop();
          nop();
          nop();
          nop();
          bVar10 = thunk_FUN_CODE_a4eb(param_10,bVar6 + 2,param_7 + 1,cVar9);
          return bVar10;
        }
        cVar9 = cVar9 + '\x01';
        goto LAB_CODE_045d;
      }
      *param_5 = *param_5 + '\x01';
    }
    while( true ) {
      bVar10 = bVar11 + param_10;
      bVar11 = bVar10 + 7;
      param_5 = param_5 + '\x01';
      nop();
      puVar13 = puVar12 + -1;
      if (0xf8 < bVar10) break;
      nop();
      puVar12 = puVar12 + -1;
      bVar14 = bVar14 & 0x5d;
    }
    bVar11 = ~bVar11 >> 1 | ~bVar11 << 7;
    nop();
    nop();
    bVar10 = bVar14 & 0x5d | (param_7 < 0x17) << 7;
LAB_CODE_0470:
    cVar4 = BANK2_R6;
    cVar5 = BANK1_R2;
    cVar2 = BANK0_R0;
    nop();
    cVar8 = cVar7 + '\x01';
    nop();
    BANK1_R2 = BANK1_R2 + '\x01';
    nop();
    if (-1 < (char)bVar10) {
      bVar6 = bVar11 >> 1 | bVar11 << 7;
      nop();
      BANK2_R6 = BANK2_R6 + -1;
      BANK0_R0 = BANK0_R0 + '\x01';
      cVar3 = P2_1;
      if (cVar3 == '\x01') {
        *param_5 = *param_5 + '\x01';
      }
      else {
        nop();
        if ((char)bVar10 < '\0') {
          if (bVar6 != 0) {
            nop();
            cVar8 = cVar7 + '\x02';
            nop();
            BANK1_R2 = cVar5 + '\x02';
          }
          nop();
          if (-1 < (char)bVar10) {
            bVar6 = bVar6 >> 1 | (bVar11 >> 1) << 7;
            nop();
            BANK2_R6 = cVar4 + -2;
            BANK0_R0 = cVar2 + '\x02';
            cVar7 = P2_1;
            if (cVar7 == '\x01') {
              param_9 = param_9 + '\x01';
            }
            else {
              nop();
              if ((char)bVar10 < '\0') {
                if (param_3 != 0) {
                  bVar6 = bVar6 / param_3;
                }
                nop();
                return bVar6;
              }
              cVar9 = cVar9 + '\x01';
            }
          }
          nop();
          *BANK1_R4 = *BANK1_R4 + '\x01';
          bVar6 = bVar6 + 0xd;
          cVar7 = (char)((ushort)bVar6 * (ushort)param_3 >> 8);
          puVar13['\x01'] = param_7;
          puVar13['\x02'] = cVar7;
          puVar13['\x03'] = (char)((ushort)param_2 >> 8);
          puVar13['\x04'] = (char)param_2;
          puVar13['\x05'] =
               bVar10 & 0x59 | ((char)bVar6 < '\0') << 5 | (bVar6 == 0) << 1 | (cVar7 != '\0') << 2;
          puVar13['\x06'] = BANK0_R0;
          puVar13['\a'] = BANK0_R1;
          puVar13['\b'] = BANK0_R2;
          puVar13['\t'] = BANK0_R3;
          puVar13['\n'] = BANK0_R4;
          puVar13['\v'] = BANK0_R5;
          puVar13['\f'] = BANK0_R6;
          puVar13['\r'] = BANK0_R7;
          puVar13['\x0e'] = 0xb5;
          puVar13['\x0f'] = 0xd5;
          sub_bad9(cVar8,param_9,cVar9);
          BANK0_R7 = puVar13['\r'];
          BANK0_R6 = puVar13['\f'];
          BANK0_R5 = puVar13['\v'];
          BANK0_R4 = puVar13['\n'];
          BANK0_R3 = puVar13['\t'];
          BANK0_R2 = puVar13['\b'];
          BANK0_R1 = puVar13['\a'];
          BANK0_R0 = puVar13['\x06'];
          return puVar13['\x01'];
        }
        cVar9 = cVar9 + '\x01';
      }
    }
    nop();
    cVar7 = cVar7 + '\x02';
  }
  else {
    bVar10 = bVar10 >> 1 | bVar10 * -0x80;
    nop();
    BANK2_R6 = BANK2_R6 + -1;
    BANK0_R0 = cVar7 + '\x02';
    cVar7 = P2_1;
    if (cVar7 == '\x01') {
      *param_5 = *param_5 + '\x01';
      goto LAB_CODE_03a5;
    }
    nop();
    bVar11 = bVar6;
    if (!bVar1) {
      cVar9 = cVar9 + '\x01';
      goto LAB_CODE_03a5;
    }
LAB_CODE_03e6:
    bVar6 = bVar11 + 1;
    nop();
    BANK1_R2 = BANK1_R2 + '\x01';
    nop();
    bVar11 = bVar10;
    if (-1 < (char)bVar14) {
      bVar11 = bVar10 >> 1 | bVar10 << 7;
      nop();
      BANK2_R6 = BANK2_R6 + -1;
      BANK0_R0 = BANK0_R0 + '\x01';
      cVar7 = P2_1;
      if (cVar7 != '\x01') goto LAB_CODE_03fd;
      *param_5 = *param_5 + '\x01';
    }
LAB_CODE_0401:
    nop();
    bVar11 = bVar11 + param_10;
    bVar1 = 0xf8 < bVar11;
    bVar10 = bVar14 & 0x5d | bVar1 << 7;
    *param_5 = *param_5 + '\x01';
    nop();
    nop();
    nop();
    bVar14 = bVar11 + 8 >> 1;
    bVar11 = bVar14 | bVar11 * -0x80;
    nop();
    nop();
    nop();
    cVar7 = bVar6 + 1;
    nop();
    BANK1_R2 = BANK1_R2 + '\x01';
    nop();
    if (!bVar1) {
      bVar11 = bVar11 >> 1 | bVar14 << 7;
      nop();
      BANK2_R6 = BANK2_R6 + -1;
      BANK0_R0 = BANK0_R0 + '\x01';
      cVar2 = P2_1;
      if (cVar2 == '\x01') {
        *param_5 = *param_5 + '\x01';
      }
      else {
        nop();
        if (bVar1) goto LAB_CODE_0470;
        cVar9 = cVar9 + '\x01';
      }
    }
    nop();
    nop();
    if (_0_3 != '\x01') {
      nop();
      bVar10 = P2_0;
      bVar10 = 0xf8 < bVar11 + param_10 | (bVar10 ^ 1) & 1;
      if ((char)((bVar10 | _5_1 ^ 1) << 7) < '\0') {
        return bVar11 + param_10 + 7;
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
      nop();
      nop();
      nop();
      nop();
      nop();
      nop();
      bVar6 = (byte)(param_4 + '\x01') >> 1;
      nop();
      *param_5 = *param_5 + '\x01';
      bVar10 = bVar10 | (_5_1 ^ 1) & 1;
      if (((char)((bVar10 | _0_6 ^ 1) << 7) < '\0') ||
         ((char)(((bVar10 | (_0_6 ^ 1) & 1) & ~_0_5) << 7) < '\0')) {
        nop();
        BANK0_R0 = BANK0_R0 + '\x01';
      }
      nop();
      BANK0_R0 = BANK0_R0 + '\x01';
      nop();
      nop();
      return *(byte *)CONCAT11((bVar6 | (char)(param_4 + '\x01') * -0x80) >> 1 | bVar6 * -0x80,
                               (char)param_2);
    }
  }
  nop();
  BANK0_R2 = *puVar13;
  bVar10 = thunk_FUN_CODE_a4eb(*param_2,cVar7,cVar9);
  return bVar10;
}

