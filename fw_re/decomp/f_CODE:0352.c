
/* WARNING: Instruction at (CODE,0x04ea) overlaps instruction at (CODE,0x04e9)
    */

byte sub_0352(byte param_1,byte *param_2,byte param_3,byte *param_4,char param_5,char param_6,
             byte param_7,byte param_8,char param_9,char param_10,char param_11)

{
  bool bVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  char cVar5;
  char *pcVar6;
  byte bVar7;
  char cVar8;
  char cVar9;
  char cVar10;
  byte bVar11;
  byte bVar12;
  byte bVar13;
  undefined1 *puVar14;
  undefined1 *puVar15;
  byte in_PSW;
  
  puVar15 = (undefined1 *)0x0;
  bVar11 = param_1 >> 1 | param_1 << 7;
  nop();
  nop();
  *param_4 = bVar11;
  pcVar6 = (char *)(param_5 + '\x01');
  nop();
  nop();
  nop();
  bVar12 = *param_2;
  cVar10 = param_11 + -1;
  nop();
  bVar7 = param_6 + 1;
  nop();
  BANK1_R2 = BANK1_R2 + '\x01';
  nop();
  if (!CARRY1(bVar11 >> 4 | (param_1 >> 1) << 4,param_7 - ((char)in_PSW >> 7))) {
    bVar12 = bVar12 >> 1 | bVar12 << 7;
    nop();
    BANK2_R6 = BANK2_R6 + -1;
    BANK0_R0 = BANK0_R0 + '\x01';
    cVar8 = P2_1;
    if (cVar8 == '\x01') {
      *pcVar6 = *pcVar6 + '\x01';
    }
    else {
      nop();
      cVar10 = param_11;
    }
  }
  cVar8 = BANK0_R0;
  nop();
  bVar1 = 0xf8 < bVar12 + param_10;
  bVar11 = in_PSW & 0x5d | bVar1 << 7;
  nop();
  nop();
  BANK0_R0 = BANK0_R0 + '\x01';
  bVar12 = bVar12 + param_10 + 9;
  nop();
  nop();
  BANK1_R2 = BANK1_R2 + '\x01';
  nop();
  BANK0_R2 = param_7;
  if (bVar1) {
LAB_CODE_03a5:
    nop();
    bVar12 = bVar12 + param_10 + 7;
    BANK0_R0 = BANK0_R0 + '\x01';
    nop();
    cVar8 = FIFLG;
    FIFLG = cVar8 + '\x01';
    bVar13 = bVar12 >> 1 | bVar12 * -0x80;
    nop();
    nop();
    bVar11 = in_PSW & 0x5d | (param_4 < &BANK1_R3) << 7;
    nop();
    if (param_4 < &BANK1_R3) {
      nop();
      param_4 = param_4 + '\x01';
      nop();
      nop();
      bVar11 = in_PSW & 0x5d | (param_8 < 0x34) << 7;
      bVar12 = bVar7;
      goto LAB_CODE_03e6;
    }
LAB_CODE_03fd:
    nop();
    if (-1 < (char)bVar11) {
      cVar10 = cVar10 + '\x01';
      goto LAB_CODE_0401;
    }
    *param_4 = BANK1_R6;
    cVar5 = BANK2_R6;
    cVar2 = BANK0_R0;
    nop();
    cVar8 = bVar7 + 1;
    nop();
    BANK1_R2 = BANK1_R2 + '\x01';
    nop();
    puVar14 = puVar15;
    if ((char)bVar11 < '\0') {
LAB_CODE_045d:
      nop();
    }
    else {
      bVar12 = bVar13 >> 1;
      bVar13 = bVar12 | bVar13 << 7;
      nop();
      BANK2_R6 = BANK2_R6 + -1;
      BANK0_R0 = BANK0_R0 + '\x01';
      cVar4 = P2_1;
      if (cVar4 != '\x01') {
        nop();
        if ((char)bVar11 < '\0') {
          nop();
          nop();
          BANK1_R2 = param_8 + 1;
          nop();
          if (-1 < (char)bVar11) {
            bVar12 = bVar13 >> 1 | bVar12 << 7;
            nop();
            BANK2_R6 = cVar5 + -2;
            BANK0_R0 = cVar2 + '\x02';
            cVar8 = P2_1;
            if (cVar8 == '\x01') {
              *pcVar6 = *pcVar6 + '\x01';
            }
            else {
              nop();
              if ((char)bVar11 < '\0') {
                nop();
                nop();
                bVar7 = (char)param_4 - ((char)bVar11 >> 7);
                bVar12 = thunk_FUN_CODE_032c((bVar12 + bVar7) -
                                             (param_7 - ((CARRY1(bVar12,bVar7) << 7) >> 7)),BANK0_R0
                                             ,cVar10);
                *param_4 = *param_4 + 1;
                nop();
                nop();
                nop();
                nop();
                return bVar12;
              }
              cVar10 = cVar10 + '\x01';
            }
          }
          nop();
          nop();
          nop();
          nop();
          bVar12 = thunk_FUN_CODE_a4eb(param_10,bVar7 + 2,param_7 + 1,cVar10);
          return bVar12;
        }
        cVar10 = cVar10 + '\x01';
        goto LAB_CODE_045d;
      }
      *pcVar6 = *pcVar6 + '\x01';
    }
    while( true ) {
      bVar12 = bVar13 + param_10;
      bVar13 = bVar12 + 7;
      pcVar6 = pcVar6 + '\x01';
      nop();
      puVar15 = puVar14 + -1;
      if (0xf8 < bVar12) break;
      nop();
      puVar14 = puVar14 + -1;
      bVar11 = bVar11 & 0x5d;
    }
    bVar13 = ~bVar13 >> 1 | ~bVar13 << 7;
    nop();
    nop();
    bVar12 = bVar11 & 0x5d | (param_7 < 0x17) << 7;
LAB_CODE_0470:
    cVar4 = BANK2_R6;
    cVar5 = BANK1_R2;
    cVar2 = BANK0_R0;
    nop();
    cVar9 = cVar8 + '\x01';
    nop();
    BANK1_R2 = BANK1_R2 + '\x01';
    nop();
    if (-1 < (char)bVar12) {
      bVar7 = bVar13 >> 1 | bVar13 << 7;
      nop();
      BANK2_R6 = BANK2_R6 + -1;
      BANK0_R0 = BANK0_R0 + '\x01';
      cVar3 = P2_1;
      if (cVar3 == '\x01') {
        *pcVar6 = *pcVar6 + '\x01';
      }
      else {
        nop();
        if ((char)bVar12 < '\0') {
          if (bVar7 != 0) {
            nop();
            cVar9 = cVar8 + '\x02';
            nop();
            BANK1_R2 = cVar5 + '\x02';
          }
          nop();
          if (-1 < (char)bVar12) {
            bVar7 = bVar7 >> 1 | (bVar13 >> 1) << 7;
            nop();
            BANK2_R6 = cVar4 + -2;
            BANK0_R0 = cVar2 + '\x02';
            cVar8 = P2_1;
            if (cVar8 == '\x01') {
              param_9 = param_9 + '\x01';
            }
            else {
              nop();
              if ((char)bVar12 < '\0') {
                if (param_3 != 0) {
                  bVar7 = bVar7 / param_3;
                }
                nop();
                return bVar7;
              }
              cVar10 = cVar10 + '\x01';
            }
          }
          nop();
          *BANK1_R4 = *BANK1_R4 + '\x01';
          bVar7 = bVar7 + 0xd;
          cVar8 = (char)((ushort)bVar7 * (ushort)param_3 >> 8);
          puVar15['\x01'] = param_7;
          puVar15['\x02'] = cVar8;
          puVar15['\x03'] = (char)((ushort)param_2 >> 8);
          puVar15['\x04'] = (char)param_2;
          puVar15['\x05'] =
               bVar12 & 0x59 | ((char)bVar7 < '\0') << 5 | (bVar7 == 0) << 1 | (cVar8 != '\0') << 2;
          puVar15['\x06'] = BANK0_R0;
          puVar15['\a'] = BANK0_R1;
          puVar15['\b'] = BANK0_R2;
          puVar15['\t'] = BANK0_R3;
          puVar15['\n'] = BANK0_R4;
          puVar15['\v'] = BANK0_R5;
          puVar15['\f'] = BANK0_R6;
          puVar15['\r'] = BANK0_R7;
          puVar15['\x0e'] = 0xb5;
          puVar15['\x0f'] = 0xd5;
          sub_bad9(cVar9,param_9,cVar10);
          BANK0_R7 = puVar15['\r'];
          BANK0_R6 = puVar15['\f'];
          BANK0_R5 = puVar15['\v'];
          BANK0_R4 = puVar15['\n'];
          BANK0_R3 = puVar15['\t'];
          BANK0_R2 = puVar15['\b'];
          BANK0_R1 = puVar15['\a'];
          BANK0_R0 = puVar15['\x06'];
          return puVar15['\x01'];
        }
        cVar10 = cVar10 + '\x01';
      }
    }
    nop();
    cVar8 = cVar8 + '\x02';
  }
  else {
    bVar12 = bVar12 >> 1 | bVar12 * -0x80;
    nop();
    BANK2_R6 = BANK2_R6 + -1;
    BANK0_R0 = cVar8 + '\x02';
    cVar8 = P2_1;
    if (cVar8 == '\x01') {
      *pcVar6 = *pcVar6 + '\x01';
      goto LAB_CODE_03a5;
    }
    nop();
    bVar13 = bVar7;
    if (!bVar1) {
      cVar10 = cVar10 + '\x01';
      goto LAB_CODE_03a5;
    }
LAB_CODE_03e6:
    bVar7 = bVar13 + 1;
    nop();
    BANK1_R2 = BANK1_R2 + '\x01';
    nop();
    bVar13 = bVar12;
    if (-1 < (char)bVar11) {
      bVar13 = bVar12 >> 1 | bVar12 << 7;
      nop();
      BANK2_R6 = BANK2_R6 + -1;
      BANK0_R0 = BANK0_R0 + '\x01';
      cVar8 = P2_1;
      if (cVar8 != '\x01') goto LAB_CODE_03fd;
      *pcVar6 = *pcVar6 + '\x01';
    }
LAB_CODE_0401:
    nop();
    bVar13 = bVar13 + param_10;
    bVar1 = 0xf8 < bVar13;
    bVar12 = bVar11 & 0x5d | bVar1 << 7;
    *pcVar6 = *pcVar6 + '\x01';
    nop();
    nop();
    nop();
    bVar11 = bVar13 + 8 >> 1;
    bVar13 = bVar11 | bVar13 * -0x80;
    nop();
    nop();
    nop();
    cVar8 = bVar7 + 1;
    nop();
    BANK1_R2 = BANK1_R2 + '\x01';
    nop();
    if (!bVar1) {
      bVar13 = bVar13 >> 1 | bVar11 << 7;
      nop();
      BANK2_R6 = BANK2_R6 + -1;
      BANK0_R0 = BANK0_R0 + '\x01';
      cVar2 = P2_1;
      if (cVar2 == '\x01') {
        *pcVar6 = *pcVar6 + '\x01';
      }
      else {
        nop();
        if (bVar1) goto LAB_CODE_0470;
        cVar10 = cVar10 + '\x01';
      }
    }
    nop();
    nop();
    if (_0_3 != '\x01') {
      nop();
      bVar12 = P2_0;
      bVar12 = 0xf8 < bVar13 + param_10 | (bVar12 ^ 1) & 1;
      if ((char)((bVar12 | _5_1 ^ 1) << 7) < '\0') {
        return bVar13 + param_10 + 7;
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
      bVar7 = (byte)(param_4 + '\x01') >> 1;
      nop();
      *pcVar6 = *pcVar6 + '\x01';
      bVar12 = bVar12 | (_5_1 ^ 1) & 1;
      if (((char)((bVar12 | _0_6 ^ 1) << 7) < '\0') ||
         ((char)(((bVar12 | (_0_6 ^ 1) & 1) & ~_0_5) << 7) < '\0')) {
        nop();
        BANK0_R0 = BANK0_R0 + '\x01';
      }
      nop();
      BANK0_R0 = BANK0_R0 + '\x01';
      nop();
      nop();
      return *(byte *)CONCAT11((bVar7 | (char)(param_4 + '\x01') * -0x80) >> 1 | bVar7 * -0x80,
                               (char)param_2);
    }
  }
  nop();
  BANK0_R2 = *puVar15;
  bVar12 = thunk_FUN_CODE_a4eb(*param_2,cVar8,cVar10);
  return bVar12;
}

