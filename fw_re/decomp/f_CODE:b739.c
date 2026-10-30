
byte sub_b739(undefined1 param_1,undefined1 param_2)

{
  byte bVar1;
  byte in_PSW;
  
  bVar1 = 0xe4;
  DAT_EXTMEM_1ae2 = param_1;
  DAT_EXTMEM_1ae3 = param_2;
  sub_d953(0xe2);
  DAT_EXTMEM_1ae4 = bVar1 & 0xf;
  in_PSW = in_PSW & 0xdd;
  sub_ae84(0,1);
  if (-1 < (char)in_PSW) {
    return DAT_EXTMEM_1ae4;
  }
  if (DAT_EXTMEM_1ae4 == 1) {
    bVar1 = 0;
  }
  else {
    bVar1 = DAT_EXTMEM_1ae4 + 1;
  }
  _0_3 = 0;
  DAT_EXTMEM_1ae4 = bVar1;
  sub_3a00(0x1ae2);
  sub_95d7();
  DAT_EXTMEM_1ae4 = bVar1;
  sub_37f9(0,0,0,bVar1 & 0xf);
  sub_c925(0xe2,0xe4);
  return 3;
}

