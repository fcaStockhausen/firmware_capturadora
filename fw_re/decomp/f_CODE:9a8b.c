
void sub_9a8b(char param_1,byte param_2,char param_3)

{
  char cVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  
  bVar2 = sub_84fd(0x101d);
  do {
    bVar4 = param_2 >> 1;
    bVar3 = param_2 << 7;
    bVar5 = bVar2 << 7;
    param_1 = param_1 + -1;
    param_2 = bVar4;
    bVar2 = bVar2 >> 1 | bVar3;
  } while (param_1 != '\0');
  sub_84e3(0x1022);
  if (-1 < (char)bVar5) {
    sub_8541();
    DAT_EXTMEM_1020 = 0;
    DAT_EXTMEM_1021 = 0;
    while( true ) {
      sub_8570(0x1022);
      bVar2 = bVar4 - (((DAT_EXTMEM_1021 < (byte)(param_3 - ((char)bVar5 >> 7))) << 7) >> 7);
      bVar5 = (DAT_EXTMEM_1020 < bVar2) << 7;
      if (DAT_EXTMEM_1020 >= bVar2) break;
      sub_854b();
      do {
        cVar1 = TF2;
      } while (cVar1 == '\0');
      T2CON = 0xc0;
      bVar3 = sub_8558();
      bVar2 = bVar4;
      do {
        bVar4 = bVar2 << 1 | bVar3 >> 7;
        bVar5 = bVar2 & 0x80;
        param_1 = param_1 + -1;
        bVar2 = bVar4;
        bVar3 = bVar3 << 1;
      } while (param_1 != '\0');
      sub_84b3(0x101d);
      DAT_EXTMEM_1021 = DAT_EXTMEM_1021 + 1;
      if (DAT_EXTMEM_1021 == 0) {
        DAT_EXTMEM_1020 = DAT_EXTMEM_1020 + 1;
      }
    }
    bVar3 = RCAP2L;
    RCAP2L = bVar3 & 0x3f;
    sub_8544(DAT_EXTMEM_1020 - bVar2);
  }
  DAT_EXTMEM_1022 = 0;
  DAT_EXTMEM_1023 = 0;
  while( true ) {
    sub_8570(0x1024);
    bVar2 = bVar4 - (((DAT_EXTMEM_1023 < (byte)(param_3 - ((char)bVar5 >> 7))) << 7) >> 7);
    if (bVar2 <= DAT_EXTMEM_1022) break;
    sub_ecba(DAT_EXTMEM_1022 - bVar2);
    bVar3 = sub_8558(BANK0_R7);
    bVar2 = bVar4;
    do {
      bVar4 = bVar2 << 1 | bVar3 >> 7;
      bVar5 = bVar2 & 0x80;
      param_1 = param_1 + -1;
      bVar2 = bVar4;
      bVar3 = bVar3 << 1;
    } while (param_1 != '\0');
    sub_8562(0x101d);
    sub_8577(0x1022);
    DAT_EXTMEM_1023 = DAT_EXTMEM_1023 + 1;
    if (DAT_EXTMEM_1023 == 0) {
      DAT_EXTMEM_1022 = DAT_EXTMEM_1022 + 1;
    }
  }
  return;
}

