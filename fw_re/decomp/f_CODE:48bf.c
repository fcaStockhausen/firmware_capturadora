
void sub_48bf(char param_1,byte param_2)

{
  undefined1 uVar1;
  byte bVar2;
  byte bVar3;
  undefined1 uVar4;
  char cVar5;
  undefined1 *puVar6;
  
  if ((DAT_EXTMEM_f004 & 1) != 0) {
    sub_3052();
    sub_3264();
  }
  if (DAT_INTMEM_30 == '\x01') {
    uVar4 = 0x12;
    sub_2fb4(0x12a9);
    cVar5 = sub_33fb();
    if (cVar5 == '\x05') {
      cVar5 = sub_307c(CONCAT11(uVar4,DAT_INTMEM_31 * param_1 + '\\'));
      cVar5 = cVar5 + '^';
    }
    else {
      cVar5 = sub_307c(CONCAT11(uVar4,DAT_INTMEM_31 * param_1 + -0x48));
      cVar5 = cVar5 + -0x46;
    }
    sub_32a9(cVar5);
    DAT_EXTMEM_1bb4 = DAT_EXTMEM_1bbc;
    DAT_EXTMEM_1bbe = DAT_EXTMEM_1bc3;
    DAT_EXTMEM_1bb8 = DAT_EXTMEM_1bc0;
    puVar6 = &DAT_EXTMEM_1bbd;
  }
  else {
    uVar4 = 0x12;
    sub_2fb4(0x12a9);
    cVar5 = sub_33fb();
    if (cVar5 == '\x05') {
      cVar5 = sub_307c(CONCAT11(uVar4,DAT_INTMEM_31 * param_1 + ','));
      cVar5 = cVar5 + '.';
    }
    else {
      cVar5 = sub_307c(CONCAT11(uVar4,DAT_INTMEM_31 * param_1 + -0x74));
      cVar5 = cVar5 + -0x72;
    }
    sub_32a9(cVar5);
    DAT_EXTMEM_1bb4 = DAT_EXTMEM_1bb6;
    DAT_EXTMEM_1bbe = DAT_EXTMEM_1bbf;
    DAT_EXTMEM_1bb8 = DAT_EXTMEM_1bb9;
    puVar6 = &DAT_EXTMEM_1bb7;
  }
  DAT_EXTMEM_1bb5 = *puVar6;
  sub_de34(DAT_EXTMEM_1c06);
  sub_d2f7(DAT_EXTMEM_1c0c);
  sub_d766(DAT_EXTMEM_1c0a);
  sub_de5f(DAT_EXTMEM_1c08);
  sub_9735(0xd9,0x22,1);
  for (DAT_EXTMEM_1aa7 = 0xf0; bVar2 = param_2, 2 < DAT_EXTMEM_1aa7;
      DAT_EXTMEM_1aa7 = DAT_EXTMEM_1aa7 - 1) {
    sub_32d9(DAT_EXTMEM_1aa7 - 3,DAT_EXTMEM_1aa7,BANK0_R1);
    bVar3 = DAT_INTMEM_32;
    sub_d0aa(0,0,0,BANK0_R7);
    uVar1 = BANK0_R7;
    uVar4 = BANK0_R6;
    sub_322d();
    BANK0_R6 = uVar4;
    BANK0_R7 = uVar1;
    sub_d0aa();
    param_2 = DAT_EXTMEM_22de +
              ((DAT_EXTMEM_22e6 << 1 | CARRY1(DAT_EXTMEM_22e7,DAT_EXTMEM_22e7)) -
              ((CARRY1(DAT_EXTMEM_22df,DAT_EXTMEM_22e7 * '\x02') << 7) >> 7));
    DAT_EXTMEM_22da = bVar2;
    DAT_EXTMEM_22db = bVar3;
    if (param_2 - (((bVar3 < DAT_EXTMEM_22df + DAT_EXTMEM_22e7 * '\x02' + 1) << 7) >> 7) <= bVar2)
    break;
    if (DAT_EXTMEM_1aa7 == 3) goto LAB_CODE_4a1b;
  }
LAB_CODE_4a77:
  DAT_EXTMEM_22e5 = (undefined1)((ushort)DAT_INTMEM_32 * 100);
  DAT_EXTMEM_22e4 = (undefined1)((ushort)DAT_INTMEM_32 * 100 >> 8);
  sub_bd87(DAT_EXTMEM_1aa7);
  sub_420f(0xd9,0x22,1);
  sub_569e();
  sub_31f3();
  sub_e33f();
  if ((DAT_EXTMEM_f004 & 1) != 0) {
    sub_31a6();
  }
  if (DAT_INTMEM_30 == '\x01') {
    DAT_EXTMEM_f04c = DAT_EXTMEM_f04c | 2;
    if ((DAT_EXTMEM_f004 & 1) != 0) {
      bVar2 = EA;
      DAT_EXTMEM_1aa8 = bVar2 & 1;
      EA = 0;
      sub_7e18();
      EA = DAT_EXTMEM_1aa8 != 0;
    }
    uVar4 = 0;
  }
  else {
    DAT_EXTMEM_f04c = DAT_EXTMEM_f04c & 0xfd;
    uVar4 = 1;
  }
  sub_ed8d(uVar4);
  if ((DAT_EXTMEM_f004 & 1) != 0) {
    sub_30f0();
  }
  return;
LAB_CODE_4a1b:
  if ((DAT_INTMEM_32 == 0) << 7 < '\0') goto LAB_CODE_4a77;
  sub_32d9(DAT_EXTMEM_1aa7);
  bVar2 = DAT_INTMEM_32;
  sub_d0aa(0,0,0,BANK0_R7);
  uVar1 = BANK0_R7;
  uVar4 = BANK0_R6;
  sub_322d();
  BANK0_R6 = uVar4;
  BANK0_R7 = uVar1;
  sub_d0aa();
  DAT_EXTMEM_22da = param_2;
  DAT_EXTMEM_22db = bVar2;
  if ((byte)((DAT_EXTMEM_22de +
             (DAT_EXTMEM_22e6 - ((CARRY1(DAT_EXTMEM_22df,DAT_EXTMEM_22e7) << 7) >> 7))) -
            (((bVar2 < DAT_EXTMEM_22df + DAT_EXTMEM_22e7 + 1) << 7) >> 7)) <= param_2)
  goto LAB_CODE_4a77;
  DAT_INTMEM_32 = DAT_INTMEM_32 - 1;
  goto LAB_CODE_4a1b;
}

