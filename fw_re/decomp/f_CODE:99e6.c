
void sub_99e6(undefined1 param_1,byte param_2)

{
  undefined1 uVar1;
  byte bVar2;
  char cVar3;
  undefined1 uVar4;
  
  sub_eb42();
  DAT_EXTMEM_1aa8 = param_2;
  sub_eda3(0);
  sub_ed98(1);
  sub_3258();
  sub_7489();
  sub_ddb0();
  sub_a601(2);
  sub_33b7();
  sub_585f();
  uVar1 = 2;
  sub_da22(2);
  DAT_EXTMEM_f003 = DAT_EXTMEM_f003 | 0xfc;
  bVar2 = sub_306a(0xf004);
  sub_31b3(bVar2 | 0xfc);
  _0_1 = 1;
  sub_dfe2();
  sub_3264(0x23,0xf014);
  sub_edeb();
  DAT_EXTMEM_f050 = DAT_EXTMEM_f050 & 0xfe;
  cVar3 = DAT_INTMEM_30;
  if (DAT_INTMEM_30 == '\x01') {
    bVar2 = EA;
    DAT_EXTMEM_1aa7 = bVar2 & 1;
    EA = 0;
    sub_7e18();
    cVar3 = DAT_EXTMEM_1aa7 - 1;
    EA = DAT_EXTMEM_1aa7 != 0;
  }
  sub_30f0(cVar3);
  uVar4 = sub_3035(0x22ee,100);
  sub_0e44(uVar4,param_1,uVar1,3,0xe8);
  sub_ed82();
  sub_337f();
  sub_ed82();
  sub_ed98(DAT_EXTMEM_1aa8 & 0x80);
  sub_eda3(DAT_EXTMEM_1aa8);
  DAT_INTMEM_2a = 0;
  DAT_INTMEM_2b = 0;
  return;
}

