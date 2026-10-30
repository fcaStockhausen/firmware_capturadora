
void FUN_CODE_e511(char param_1,byte param_2)

{
  byte bVar1;
  char in_PSW;
  
  sub_125f(0x1a7e);
  nop();
  nop();
  bVar1 = sub_125f(&LAB_CODE_1a82,0);
  nop();
  nop();
  nop();
  if (-1 < in_PSW) {
    sub_54ce(bVar1 ^ param_2,0xf07f,param_1 + '\x01');
    sub_8910(9);
    return;
  }
  if (bVar1 == 0x81) {
    FUN_CODE_e108();
    return;
  }
  if (bVar1 == 0x82) {
    FUN_CODE_dcc9();
    return;
  }
  if (bVar1 != 0x83) {
    if (bVar1 == 0x80) {
      FUN_CODE_d646();
      return;
    }
    _2_4 = 1;
    return;
  }
  FUN_CODE_dfb7();
  return;
}

