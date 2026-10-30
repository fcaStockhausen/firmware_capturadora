
void sub_76c6(undefined1 param_1,undefined1 param_2,undefined1 param_3)

{
  undefined1 uVar1;
  char in_PSW;
  
  _0_1 = 0;
  DAT_EXTMEM_d0ab = 3;
  DAT_EXTMEM_d0ac = 0;
  DAT_EXTMEM_d0aa = 1;
  DAT_EXTMEM_d09b = 0xff;
  DAT_EXTMEM_d0a8 = 0x30;
  DAT_EXTMEM_d0a9 = 0x20;
  DAT_EXTMEM_1ab3 = param_3;
  DAT_EXTMEM_1ab4 = param_2;
  DAT_EXTMEM_1ab5 = param_1;
  sub_e279(0xb0,0xf0,0xd0,0xa7);
  _0_2 = 0;
  sub_ec83();
  sub_ee2f(0x20,0xf0,4);
  sub_ee2f(2,0xd0,0x90);
  sub_0016(1,0xd0,0x90);
  uVar1 = sub_eaab(0x1ab3);
  DAT_EXTMEM_1ab6 = sub_0db8(uVar1);
  sub_b666(0xb6,0x1a,1);
  if (in_PSW < '\0') {
    _0_1 = 1;
    sub_e279(DAT_EXTMEM_1ac4,3,0xd0,0x93);
    sub_e279(DAT_EXTMEM_1ac5 << 4,0x70,0xd0,0x93);
    DAT_EXTMEM_d091 = DAT_EXTMEM_1ac7;
    DAT_EXTMEM_d092 = DAT_EXTMEM_1ac6;
  }
  uVar1 = sub_eaab(0x1ab3);
                    /* WARNING: Subroutine does not return */
  sub_0dd1(2,uVar1);
}

