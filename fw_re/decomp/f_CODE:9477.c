
void sub_9477(char param_1,byte param_2,char param_3)

{
  char cVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  
  bVar2 = sub_84fd(0x1c10);
  do {
    bVar3 = param_2 >> 1;
    bVar4 = param_2 << 7;
    bVar5 = bVar2 << 7;
    param_1 = param_1 + -1;
    param_2 = bVar3;
    bVar2 = bVar2 >> 1 | bVar4;
  } while (param_1 != '\0');
  sub_84e3(0x1c15);
  if (-1 < (char)bVar5) {
    sub_8541();
    DAT_EXTMEM_1c13 = 0;
    DAT_EXTMEM_1c14 = 0;
    while( true ) {
      sub_8570(0x1c15);
      bVar2 = bVar3 - (((DAT_EXTMEM_1c14 < (byte)(param_3 - ((char)bVar5 >> 7))) << 7) >> 7);
      bVar5 = (DAT_EXTMEM_1c13 < bVar2) << 7;
      if (DAT_EXTMEM_1c13 >= bVar2) break;
      bVar2 = sub_855b();
      do {
        bVar3 = bVar3 << 1 | bVar2 >> 7;
        param_1 = param_1 + -1;
        bVar2 = bVar2 << 1;
      } while (param_1 != '\0');
      sub_8510(0x1c10);
      do {
        cVar1 = TF2;
      } while (cVar1 == '\0');
      T2CON = 0xc0;
      bVar4 = sub_855b(0x1c13);
      bVar2 = bVar3;
      do {
        bVar3 = bVar2 << 1 | bVar4 >> 7;
        bVar5 = bVar2 & 0x80;
        param_1 = param_1 + -1;
        bVar2 = bVar3;
        bVar4 = bVar4 << 1;
      } while (param_1 != '\0');
      sub_84b3(0x1c10);
      DAT_EXTMEM_1c14 = DAT_EXTMEM_1c14 + 1;
      if (DAT_EXTMEM_1c14 == 0) {
        DAT_EXTMEM_1c13 = DAT_EXTMEM_1c13 + 1;
      }
    }
    bVar3 = RCAP2L;
    RCAP2L = bVar3 & 0x3f;
    sub_8544(DAT_EXTMEM_1c13 - bVar2);
  }
  DAT_EXTMEM_1c15 = '\0';
  DAT_EXTMEM_1c16 = '\0';
  while( true ) {
    bVar2 = DAT_EXTMEM_1c17;
    sub_8584(DAT_EXTMEM_1c18,0x1c15);
    if (-1 < (char)bVar5) break;
    bVar3 = sub_855b(0x1c13);
    do {
      bVar5 = bVar2 & 0x80;
      param_1 = param_1 + -1;
      bVar2 = bVar2 << 1 | bVar3 >> 7;
      bVar3 = bVar3 << 1;
    } while (param_1 != '\0');
    sub_8562(0x1c10);
    sub_858f();
    sub_edc4();
    DAT_EXTMEM_1c16 = DAT_EXTMEM_1c16 + '\x01';
    if (DAT_EXTMEM_1c16 == '\0') {
      DAT_EXTMEM_1c15 = DAT_EXTMEM_1c15 + '\x01';
    }
  }
  return;
}

