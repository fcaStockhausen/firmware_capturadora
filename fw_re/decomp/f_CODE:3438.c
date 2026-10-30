
void sub_3438(void)

{
  undefined1 uVar1;
  undefined1 uVar2;
  char cVar3;
  char cVar4;
  char in_PSW;
  
  sub_3073(0x1ae2);
  uVar1 = 0x1a;
  uVar2 = 1;
  sub_0d92(0xfe,0x45,0xf3,0xff,0x1a,1,0,0x12);
  DAT_EXTMEM_1b10 = 0;
  if (DAT_EXTMEM_1ae5 == '\0') {
    if ((DAT_EXTMEM_1af5 & 1) == 1) {
      sub_2fb4(0x1ae2);
      sub_2ffc();
      while (sub_30a7(), in_PSW < '\0') {
        sub_2ff1();
        sub_3284();
        uVar2 = BANK0_R2;
        uVar1 = BANK0_R1;
        sub_31d7();
        sub_2fb6();
        sub_30b6();
        BANK0_R1 = uVar1;
        BANK0_R2 = uVar2;
        cVar3 = sub_30e6();
        if (cVar3 == '\0') {
          sub_320f();
        }
      }
      sub_2fb4(0x1ae2);
                    /* WARNING: Subroutine does not return */
      sub_0e10(0x40,0x83);
    }
    return;
  }
  if ((DAT_EXTMEM_1af5 >> 6 & 1) == 0) {
    if (DAT_EXTMEM_1af3 != '\0') {
      DAT_EXTMEM_1af8 = 0;
      DAT_EXTMEM_1af9 = 0x36;
      DAT_EXTMEM_1afa = 4;
      DAT_EXTMEM_1afd = 0x12;
      sub_300b();
      cVar4 = ((DAT_EXTMEM_1af7 < DAT_EXTMEM_1afa) << 7) >> 7;
      cVar3 = (DAT_EXTMEM_1af6 < (byte)-cVar4) << 7;
      cVar4 = DAT_EXTMEM_1af6 + cVar4;
      if (cVar3 < '\0') {
        sub_2fb4(cVar4,0x1ae2);
        sub_313f(0x1af8);
        sub_315f(0x1afb);
        if (-1 < cVar3) {
          sub_2fb4(0x1ae2);
          sub_3119(0x1af8);
                    /* WARNING: Subroutine does not return */
          sub_0dd1();
        }
        DAT_EXTMEM_1afc = DAT_EXTMEM_1afc >> 1 | DAT_EXTMEM_1afb << 7;
        DAT_EXTMEM_1afb = DAT_EXTMEM_1afb >> 1;
        sub_2fb4(0x1ae2);
        sub_3216(0x1af8);
                    /* WARNING: Subroutine does not return */
        sub_0e10(DAT_EXTMEM_1afb,CONCAT11(uVar1,uVar2) + 1);
      }
      sub_2fb4(cVar4,0x1ae2);
      sub_3004();
      while (sub_30a7(), cVar3 < '\0') {
        sub_2ff1();
        sub_3284();
        uVar2 = BANK0_R2;
        uVar1 = BANK0_R1;
        sub_31d7();
        sub_2fb6();
        sub_30b6();
        BANK0_R1 = uVar1;
        BANK0_R2 = uVar2;
        cVar4 = sub_30e6();
        if (cVar4 == '\0') {
          sub_320f();
        }
      }
    }
    sub_2fb4(0x1ae2);
                    /* WARNING: Subroutine does not return */
    sub_0dd1(0x80);
  }
  sub_2fb4(0x1ae2);
  sub_2ffe(0);
  while (sub_30a7(), in_PSW < '\0') {
    sub_2ff1();
    sub_3284();
    uVar2 = BANK0_R2;
    uVar1 = BANK0_R1;
    sub_31d7();
    sub_2fb6();
    sub_30b6();
    BANK0_R1 = uVar1;
    BANK0_R2 = uVar2;
    cVar3 = sub_30e6();
    if (cVar3 == '\0') {
      sub_320f();
    }
  }
  return;
}

