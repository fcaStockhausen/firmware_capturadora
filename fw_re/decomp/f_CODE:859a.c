
void sub_859a(byte param_1)

{
  char in_PSW;
  undefined1 *puVar1;
  
  sub_125f(0x1ae4);
  nop();
  do {
    nop();
    nop();
    nop();
    _0_4 = 1;
    sub_e365();
    if (_0_3 != '\0') {
      sub_75ac(DAT_EXTMEM_1ae2,DAT_EXTMEM_1ae3);
                    /* WARNING: Subroutine does not return */
      sub_1253(0x1ae4,0,0);
    }
    sub_ed82(1);
    _0_4 = 0;
    sub_e365();
    sub_daec(0x78);
    if (in_PSW < '\0') {
      sub_125f(0x1ae4);
      nop();
      nop();
      DAT_EXTMEM_1124 = 3;
      goto LAB_CODE_8679;
    }
    sub_daec(0xcc);
    if (in_PSW < '\0') {
      sub_125f(0x1ae4);
      nop();
      nop();
      DAT_EXTMEM_1124 = 0;
      goto LAB_CODE_8679;
    }
    sub_daef(0,2,0x6e);
    if (-1 < in_PSW) {
      sub_daef(0,3,0x97);
      if (in_PSW < '\0') {
        sub_125f(0x1ae4);
        nop();
        thunk_FUN_CODE_80ce();
        return;
      }
      sub_daef(0,4,0xdb);
      if (in_PSW < '\0') {
        sub_125f(0x1ae4);
        nop();
        FUN_CODE_8077();
        return;
      }
      sub_daef(0,7,0x2f);
      if (in_PSW < '\0') {
        sub_125f(0x1ae4);
        nop();
                    /* WARNING: Subroutine does not return */
        sub_1253();
      }
      sub_125f(0x1ae4);
      nop();
      FUN_CODE_ee00();
      return;
    }
    puVar1 = &DAT_EXTMEM_1ae4;
    sub_125f();
    nop();
    nop();
    in_PSW = (param_1 < 0x80) << 7;
  } while (param_1 != 0x80);
  sub_8024();
  *puVar1 = 2;
LAB_CODE_8679:
  sub_db06(0x1ae4);
  return;
}

