
/* WARNING: Instruction at (CODE,0x04ea) overlaps instruction at (CODE,0x04e9)
    */

byte FUN_CODE_032c(byte param_1,byte *param_2,byte param_3,byte *param_4,char *param_5,char param_6,
                  byte param_7,byte param_8,byte param_9,char param_10,char param_11)

{
  bool bVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  byte *pbVar5;
  char cVar6;
  byte bVar7;
  byte bVar8;
  byte bVar9;
  byte *pbVar10;
  byte *pbVar11;
  undefined1 *puVar12;
  undefined1 *puVar13;
  byte in_PSW;
  byte bVar14;
  
  puVar13 = (undefined1 *)0x0;
  nop();
  bVar14 = (char)param_4 - ((char)in_PSW >> 7);
  bVar7 = (param_1 ^ param_9) - bVar14;
  bVar9 = param_6 - ((char)(in_PSW & 0x7f | ((param_1 ^ param_9) < bVar14) << 7) >> 7);
  bVar8 = bVar7 + bVar9;
  bVar14 = in_PSW & 0x5d | CARRY1(bVar7,bVar9) << 7;
  nop();
  if (CARRY1(bVar7,bVar9)) {
    *param_4 = *param_4 + 1;
    nop();
    cVar6 = P2_1;
    if (cVar6 == '\x01') {
      *param_5 = *param_5 + '\x01';
      cVar6 = param_11 + '\x01';
      nop();
      bVar8 = bVar8 + param_10;
      bVar14 = in_PSW & 0x5d | (0xf8 < bVar8) << 7;
      bVar9 = bVar8 + 7 >> 1;
      bVar7 = bVar9 | (bVar8 + 7) * -0x80;
      nop();
      if (0xf8 < bVar8) {
        nop();
        bVar7 = bVar7 >> 1 | bVar9 << 7;
        nop();
        nop();
        *param_4 = bVar7;
      }
      param_5 = param_5 + '\x01';
      nop();
      nop();
      bVar9 = bVar7 >> 4 | bVar7 << 4;
      goto LAB_CODE_035a;
    }
    nop();
    nop();
    pbVar10 = param_4 + bVar8;
    bVar14 = in_PSW & 0x5d | CARRY1(bVar8,(byte)param_4) << 7;
    nop();
    nop();
  }
  else {
    nop();
    DAT_INTMEM_40 = DAT_INTMEM_40 + '\x01';
    param_9 = param_9 + 1;
    bVar9 = (bVar8 >> 1 | bVar8 * -0x80) >> 1 | (bVar8 >> 1) << 7;
    nop();
    BANK2_R6 = BANK2_R6 + -1;
    BANK0_R0 = BANK0_R0 + '\x01';
    cVar6 = param_11;
LAB_CODE_035a:
    nop();
    bVar7 = *param_2;
    param_11 = cVar6 + -1;
    nop();
    nop();
    BANK1_R2 = BANK1_R2 + '\x01';
    nop();
    if (!CARRY1(bVar9,param_7 - ((char)bVar14 >> 7))) {
      bVar7 = bVar7 >> 1 | bVar7 << 7;
      nop();
      BANK2_R6 = BANK2_R6 + -1;
      BANK0_R0 = BANK0_R0 + '\x01';
      cVar2 = P2_1;
      if (cVar2 == '\x01') {
        *param_5 = *param_5 + '\x01';
      }
      else {
        nop();
        param_11 = cVar6;
      }
    }
    nop();
    bVar14 = bVar14 & 0x5d | (0xf8 < bVar7 + param_10) << 7;
    nop();
    nop();
    BANK0_R0 = BANK0_R0 + '\x01';
    pbVar10 = (byte *)(bVar7 + param_10 + 9);
    nop();
    nop();
  }
  pbVar5 = (byte *)(param_6 + '\x01');
  BANK1_R2 = BANK1_R2 + '\x01';
  nop();
  BANK0_R2 = param_7;
  if ((char)bVar14 < '\0') {
LAB_CODE_03a5:
    nop();
    bVar9 = bVar14 & 0x5d;
    BANK0_R0 = BANK0_R0 + '\x01';
    nop();
    cVar6 = FIFLG;
    FIFLG = cVar6 + '\x01';
    pbVar11 = (byte *)((byte)(pbVar10 + param_10 + '\a') >> 1 |
                      (char)(pbVar10 + param_10 + '\a') * -0x80);
    nop();
    nop();
    bVar14 = bVar9 | (param_4 < &BANK1_R3) << 7;
    nop();
    if (param_4 < &BANK1_R3) {
      nop();
      pbVar10 = (byte *)(param_6 + '\x01');
      param_4 = param_4 + '\x01';
      nop();
      nop();
      bVar14 = bVar9 | (param_8 < 0x34) << 7;
      goto LAB_CODE_03e6;
    }
LAB_CODE_03fd:
    nop();
    if (-1 < (char)bVar14) {
      param_11 = param_11 + '\x01';
      goto LAB_CODE_0401;
    }
    *param_4 = BANK1_R6;
    cVar2 = BANK2_R6;
    cVar6 = BANK0_R0;
    nop();
    pbVar10 = pbVar5 + '\x01';
    nop();
    BANK1_R2 = BANK1_R2 + '\x01';
    nop();
    puVar12 = puVar13;
    if ((char)bVar14 < '\0') {
LAB_CODE_045d:
      nop();
    }
    else {
      bVar9 = (byte)pbVar11 >> 1;
      pbVar11 = (byte *)(bVar9 | (char)pbVar11 << 7);
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
            bVar9 = (byte)pbVar11 >> 1 | bVar9 << 7;
            nop();
            BANK2_R6 = cVar2 + -2;
            BANK0_R0 = cVar6 + '\x02';
            cVar6 = P2_1;
            if (cVar6 == '\x01') {
              *param_5 = *param_5 + '\x01';
            }
            else {
              nop();
              if ((char)bVar14 < '\0') {
                nop();
                nop();
                bVar14 = (char)param_4 - ((char)bVar14 >> 7);
                bVar14 = thunk_FUN_CODE_032c((bVar9 + bVar14) -
                                             (param_7 - ((CARRY1(bVar9,bVar14) << 7) >> 7)),BANK0_R0
                                             ,param_9,param_11);
                *param_4 = *param_4 + 1;
                nop();
                nop();
                nop();
                nop();
                return bVar14;
              }
              param_11 = param_11 + '\x01';
            }
          }
          nop();
          nop();
          nop();
          nop();
          bVar14 = thunk_FUN_CODE_a4eb(param_10,pbVar5 + '\x02',param_7 + 1,param_11);
          return bVar14;
        }
        param_11 = param_11 + '\x01';
        goto LAB_CODE_045d;
      }
      *param_5 = *param_5 + '\x01';
    }
    while( true ) {
      pbVar5 = pbVar11 + param_10;
      pbVar11 = pbVar5 + '\a';
      param_5 = param_5 + '\x01';
      nop();
      puVar13 = puVar12 + -1;
      if ((byte *)0xf8 < pbVar5) break;
      nop();
      puVar12 = puVar12 + -1;
      bVar14 = bVar14 & 0x5d;
    }
    bVar9 = ~(byte)pbVar11 >> 1 | ~(byte)pbVar11 << 7;
    nop();
    nop();
    bVar14 = bVar14 & 0x5d | (param_7 < 0x17) << 7;
LAB_CODE_0470:
    cVar4 = BANK2_R6;
    cVar2 = BANK1_R2;
    cVar6 = BANK0_R0;
    nop();
    pbVar5 = pbVar10 + '\x01';
    nop();
    BANK1_R2 = BANK1_R2 + '\x01';
    nop();
    if (-1 < (char)bVar14) {
      bVar7 = bVar9 >> 1 | bVar9 << 7;
      nop();
      BANK2_R6 = BANK2_R6 + -1;
      BANK0_R0 = BANK0_R0 + '\x01';
      cVar3 = P2_1;
      if (cVar3 == '\x01') {
        *param_5 = *param_5 + '\x01';
      }
      else {
        nop();
        if ((char)bVar14 < '\0') {
          if (bVar7 != 0) {
            nop();
            pbVar5 = pbVar10 + '\x02';
            nop();
            BANK1_R2 = cVar2 + '\x02';
          }
          nop();
          if (-1 < (char)bVar14) {
            bVar7 = bVar7 >> 1 | (bVar9 >> 1) << 7;
            nop();
            BANK2_R6 = cVar4 + -2;
            BANK0_R0 = cVar6 + '\x02';
            cVar6 = P2_1;
            if (cVar6 == '\x01') {
              param_9 = param_9 + 1;
            }
            else {
              nop();
              if ((char)bVar14 < '\0') {
                if (param_3 != 0) {
                  bVar7 = bVar7 / param_3;
                }
                nop();
                return bVar7;
              }
              param_11 = param_11 + '\x01';
            }
          }
          nop();
          *BANK1_R4 = *BANK1_R4 + '\x01';
          bVar7 = bVar7 + 0xd;
          cVar6 = (char)((ushort)bVar7 * (ushort)param_3 >> 8);
          puVar13['\x01'] = param_7;
          puVar13['\x02'] = cVar6;
          puVar13['\x03'] = (char)((ushort)param_2 >> 8);
          puVar13['\x04'] = (char)param_2;
          puVar13['\x05'] =
               bVar14 & 0x59 | ((char)bVar7 < '\0') << 5 | (bVar7 == 0) << 1 | (cVar6 != '\0') << 2;
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
          sub_bad9(pbVar5,param_9,param_11);
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
        param_11 = param_11 + '\x01';
      }
    }
    nop();
    pbVar10 = pbVar10 + '\x02';
  }
  else {
    pbVar10 = (byte *)((byte)pbVar10 >> 1 | (char)pbVar10 << 7);
    nop();
    BANK2_R6 = BANK2_R6 + -1;
    BANK0_R0 = BANK0_R0 + '\x01';
    cVar6 = P2_1;
    if (cVar6 == '\x01') {
      *param_5 = *param_5 + '\x01';
      goto LAB_CODE_03a5;
    }
    nop();
    pbVar11 = pbVar5;
    if (-1 < (char)bVar14) {
      param_11 = param_11 + '\x01';
      goto LAB_CODE_03a5;
    }
LAB_CODE_03e6:
    pbVar5 = pbVar11 + '\x01';
    nop();
    BANK1_R2 = BANK1_R2 + '\x01';
    nop();
    pbVar11 = pbVar10;
    if (-1 < (char)bVar14) {
      pbVar11 = (byte *)((byte)pbVar10 >> 1 | (char)pbVar10 << 7);
      nop();
      BANK2_R6 = BANK2_R6 + -1;
      BANK0_R0 = BANK0_R0 + '\x01';
      cVar6 = P2_1;
      if (cVar6 != '\x01') goto LAB_CODE_03fd;
      *param_5 = *param_5 + '\x01';
    }
LAB_CODE_0401:
    nop();
    pbVar11 = pbVar11 + param_10;
    bVar1 = (byte *)0xf8 < pbVar11;
    bVar14 = bVar14 & 0x5d | bVar1 << 7;
    *param_5 = *param_5 + '\x01';
    nop();
    nop();
    nop();
    bVar9 = (byte)(pbVar11 + '\b') >> 1 | (char)pbVar11 * -0x80;
    nop();
    nop();
    nop();
    pbVar10 = pbVar5 + '\x01';
    nop();
    BANK1_R2 = BANK1_R2 + '\x01';
    nop();
    if (!bVar1) {
      bVar9 = bVar9 >> 1 | ((byte)(pbVar11 + '\b') >> 1) << 7;
      nop();
      BANK2_R6 = BANK2_R6 + -1;
      BANK0_R0 = BANK0_R0 + '\x01';
      cVar6 = P2_1;
      if (cVar6 == '\x01') {
        *param_5 = *param_5 + '\x01';
      }
      else {
        nop();
        if (bVar1) goto LAB_CODE_0470;
        param_11 = param_11 + '\x01';
      }
    }
    nop();
    nop();
    if (_0_3 != '\x01') {
      nop();
      bVar14 = P2_0;
      bVar14 = 0xf8 < bVar9 + param_10 | (bVar14 ^ 1) & 1;
      if ((char)((bVar14 | _5_1 ^ 1) << 7) < '\0') {
        return bVar9 + param_10 + 7;
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
      bVar9 = (byte)(param_4 + '\x01') >> 1;
      nop();
      *param_5 = *param_5 + '\x01';
      bVar14 = bVar14 | (_5_1 ^ 1) & 1;
      if (((char)((bVar14 | _0_6 ^ 1) << 7) < '\0') ||
         ((char)(((bVar14 | (_0_6 ^ 1) & 1) & ~_0_5) << 7) < '\0')) {
        nop();
        BANK0_R0 = BANK0_R0 + '\x01';
      }
      nop();
      BANK0_R0 = BANK0_R0 + '\x01';
      nop();
      nop();
      return *(byte *)CONCAT11((bVar9 | (char)(param_4 + '\x01') * -0x80) >> 1 | bVar9 * -0x80,
                               (char)param_2);
    }
  }
  nop();
  BANK0_R2 = *puVar13;
  bVar14 = thunk_FUN_CODE_a4eb(*param_2,pbVar10,param_11);
  return bVar14;
}

