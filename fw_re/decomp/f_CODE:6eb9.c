
void sub_6eb9(char param_1,char param_2,byte param_3,char param_4)

{
  bool bVar1;
  byte bVar2;
  char cVar3;
  byte bVar4;
  byte bVar5;
  char cVar6;
  char in_PSW;
  char cVar7;
  
  sub_324f();
  sub_d4e1();
  if (((param_1 != '\0' || param_2 != '\0') || param_3 != 0) || param_4 != '\0') {
    sub_ee1f();
    bVar4 = 1;
    sub_ed98();
    _1_4 = 0;
    _1_7 = 1;
    DAT_EXTMEM_2404 = 0;
    sub_6fcf(0x20ab);
    DAT_EXTMEM_1aa9 = param_3;
    sub_6fcf(bVar4,0x1aaa);
    DAT_EXTMEM_1aa7 = param_3;
    DAT_EXTMEM_1aa8 = bVar4;
    bVar5 = sub_3274(0x1aa9);
    bVar5 = 1 - (((bVar5 < 0xf4U - (in_PSW >> 7)) << 7) >> 7);
    cVar7 = (param_3 < bVar5) << 7;
    if ((param_3 >= bVar5) || (sub_3355(param_3 - bVar5), -1 < cVar7)) {
      bVar5 = param_3 - (((DAT_EXTMEM_1aa8 < bVar4 + 1) << 7) >> 7);
      cVar7 = (DAT_EXTMEM_1aa7 < bVar5) << 7;
      bVar2 = DAT_EXTMEM_1aa7;
      if (cVar7 < '\0') {
        sub_3274(DAT_EXTMEM_1aa7 - bVar5,0x1aa7);
        bVar4 = bVar4 - (cVar7 >> 7);
        bVar1 = DAT_EXTMEM_1aaa < bVar4;
        cVar6 = DAT_EXTMEM_1aaa - bVar4;
        bVar4 = DAT_EXTMEM_1aa9;
      }
      else {
        bVar5 = DAT_EXTMEM_1aa8;
        sub_32fb();
        bVar4 = bVar4 - (cVar7 >> 7);
        bVar1 = bVar5 < bVar4;
        cVar6 = bVar5 - bVar4;
        bVar4 = bVar2;
      }
      bVar4 = bVar4 - (param_3 - ((bVar1 << 7) >> 7));
      cVar3 = '2';
      bVar5 = BANK0_R7;
      sub_33c2(0x1aa7);
      bVar5 = param_3 - (((bVar5 < cVar6 + 1U) << 7) >> 7);
      cVar7 = (bVar4 < bVar5) << 7;
      if (bVar4 >= bVar5) {
        sub_324f(bVar4 - bVar5);
        sub_e7dc();
        if (((bVar2 == 0 && cVar3 == '\0') && param_3 == 0) && cVar6 == '\0') {
          DAT_EXTMEM_1aa7 = 0;
          DAT_EXTMEM_1aa8 = 2;
          sub_3251(2);
          sub_e9ac();
        }
        else {
          DAT_EXTMEM_1aa7 = 0;
          DAT_EXTMEM_1aa8 = 1;
        }
      }
    }
    sub_3355();
    if (cVar7 < '\0') {
      sub_6fde();
      sub_3363();
      if (-1 < cVar7) {
        sub_d4e1(2,0,0,0);
        sub_3251(4);
        sub_e9ac();
        sub_d022();
      }
    }
    else {
      sub_6fde();
      sub_e9ac(0,0,1,0);
      bVar4 = DAT_EXTMEM_1aa7;
      bVar5 = DAT_EXTMEM_1aa8;
      sub_93c6();
      DAT_EXTMEM_1aab = bVar4;
      DAT_EXTMEM_1aac = bVar5;
      if (-1 < (char)bVar5) {
        _0_1 = 1;
        sub_e184();
      }
    }
    DAT_EXTMEM_2405 = DAT_EXTMEM_1aa7;
    DAT_EXTMEM_2406 = DAT_EXTMEM_1aa8;
  }
  return;
}

