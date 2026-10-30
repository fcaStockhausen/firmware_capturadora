
void sub_5bd5(undefined1 param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  char in_PSW;
  
  sub_3fd6(0x1ae2);
  DAT_EXTMEM_1ae8 = 0;
  DAT_EXTMEM_1ae9 = 0;
  _0_6 = 1;
  _0_7 = 0;
  sub_3fbb(0x1ae5);
  sub_0dfe(0);
  sub_3fbb(0x1ae5);
  sub_4055();
  uVar1 = sub_12aa();
  sub_40d1(uVar1);
  sub_12aa();
  nop();
  nop();
  nop();
  nop();
  sub_40fa();
  sub_3fbb(0x1ae2,0,2,0);
  sub_1492();
  sub_eea9();
  if (-1 < in_PSW) {
    uVar1 = sub_4079(0x1ae2);
    sub_3fd7(param_1,0x1b77,uVar1);
    sub_5d73(8);
    sub_3fbb();
    sub_dc0d();
    if (in_PSW < '\0') {
      uVar2 = sub_4079(0x1ae2);
      sub_3fd7(uVar1,0x1b77,uVar2);
      sub_5d73(0x80);
      sub_3fbb();
      sub_e597();
      if (in_PSW < '\0') {
        sub_3fbb(0x1ae5);
        sub_4151();
        sub_3fbb(0x1ae2);
                    /* WARNING: Subroutine does not return */
        sub_0dd1(0x7e);
      }
    }
  }
  _0_6 = 0;
  sub_3fbb(0x1ae5);
  sub_0dfe(1);
  sub_3fbb(0x1ae5);
  sub_4055();
  uVar1 = sub_12aa();
  sub_40d1(uVar1);
  sub_12aa();
  nop();
  nop();
  nop();
  nop();
  sub_40fa();
  return;
}

