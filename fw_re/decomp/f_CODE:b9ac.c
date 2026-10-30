
void sub_b9ac(undefined1 param_1,char param_2,char param_3)

{
  char cVar1;
  undefined1 uVar2;
  short sVar3;
  
  sub_3073(0x1aa7);
  sVar3 = 0x1aa7;
  cVar1 = sub_2ff4(0x1aa7);
  if ((cVar1 != '\0' || param_2 != '\0') || param_3 != '\0') {
    cVar1 = sub_2ff4(sVar3 + 1);
    if ((cVar1 != '\0' || param_2 != '\0') || param_3 != '\0') {
      uVar2 = sub_31df(0x1aa7);
      sub_3074(param_1,0x20b0,uVar2);
      param_1 = sub_31df(0x1aaa);
      sub_3074(uVar2,0x20ac,param_1);
      goto LAB_CODE_b9fc;
    }
  }
  DAT_EXTMEM_20b0 = 0xff;
  DAT_EXTMEM_20b1 = 0xf2;
  DAT_EXTMEM_20b2 = 0x16;
  DAT_EXTMEM_20ac = 0xff;
  DAT_EXTMEM_20ad = 0xf2;
  DAT_EXTMEM_20ae = 0x1b;
LAB_CODE_b9fc:
  uVar2 = sub_31df(0x20ac);
  sub_3074(param_1,0x1ab0,uVar2);
  sub_2fb4(0x20b0);
  FUN_CODE_e38a();
  return;
}

