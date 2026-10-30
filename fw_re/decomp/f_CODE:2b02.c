
/* WARNING: Instruction at (CODE,0x2b03) overlaps instruction at (CODE,0x2b02)
    */

byte sub_2b02(byte *param_1,byte param_2,byte param_3,byte param_4,byte param_5,byte param_6,
             byte param_7,byte param_8,byte param_9)

{
  byte bVar1;
  
  while( true ) {
    nop();
    nop();
    nop();
    if (_0_0 == '\x01') break;
    nop();
  }
  if (_5_3 == '\0') {
    return 0;
  }
  _5_3 = 0;
  if (_7_5 == '\0') {
    return 0;
  }
  _7_5 = 0;
  if (_9_7 != '\0') {
    _9_7 = 0;
    if (_c_1 != '\0') {
      _c_1 = 0;
      if (_4_7 != '\0') {
        _4_7 = '\0';
      }
      func_0x2825();
                    /* WARNING: Subroutine does not return */
      sub_1253(param_6,param_9 | 7);
    }
    *param_1 = param_6;
    param_1[1] = param_7;
    param_1[2] = param_8;
    param_1[3] = param_9;
    return param_9;
  }
  bVar1 = param_8 - 1;
  if (param_8 - 1 == 0) {
    *param_1 = 0;
    bVar1 = param_8;
  }
                    /* WARNING: Subroutine does not return */
  sub_1253(0,param_6 | param_2,param_7 | param_3,bVar1 | param_4,param_9 | param_5);
}

