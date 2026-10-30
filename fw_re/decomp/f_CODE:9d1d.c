
void sub_9d1d(undefined1 param_1,char param_2,char param_3,char param_4)

{
  undefined1 uVar1;
  undefined1 uVar2;
  byte bVar3;
  char cVar4;
  undefined1 uVar5;
  undefined1 *puVar6;
  
  DAT_EXTMEM_1af2 = '\0';
  DAT_EXTMEM_1af1 = 2;
  DAT_EXTMEM_1aea = param_4;
  do {
    if (DAT_EXTMEM_1aea + 1U <= DAT_EXTMEM_1af1) {
      return;
    }
    sub_e251(DAT_EXTMEM_1af1 - (DAT_EXTMEM_1aea + 1U),1,0x60);
    cVar4 = sub_4117(0x1aeb);
    if ((cVar4 == '\0' && param_2 == '\0') && param_3 == '\0') {
      puVar6 = &DAT_EXTMEM_1af2;
      sub_4205();
      *puVar6 = 0x1a;
      sub_417f(0xf3);
      sub_ad16();
    }
    else {
      sub_3fc4(DAT_EXTMEM_1af2,0x1aeb);
      sub_4181();
      sub_ad16();
      bVar3 = 0;
      do {
        bVar3 = bVar3 + 1;
        cVar4 = (bVar3 < 0x80) << 7;
      } while (bVar3 != 0x80);
      sub_3fbb(0x1aeb);
      sub_4101();
      sub_e597();
      if (-1 < cVar4) {
        return;
      }
      if (_1_0 != '\0') {
        sub_3fbb(0x1aeb);
        sub_4101();
        uVar2 = BANK0_R2;
        uVar1 = BANK0_R1;
        uVar5 = sub_4079(0x1aee);
        sub_3fd7(param_1,0x1b76,uVar5);
        BANK0_R1 = uVar1;
        BANK0_R2 = uVar2;
        sub_66b4();
        param_1 = uVar5;
        if (-1 < cVar4) {
          return;
        }
      }
    }
    DAT_EXTMEM_1af2 = DAT_EXTMEM_1af2 + -0x80;
    DAT_EXTMEM_1af1 = DAT_EXTMEM_1af1 + 1;
  } while( true );
}

