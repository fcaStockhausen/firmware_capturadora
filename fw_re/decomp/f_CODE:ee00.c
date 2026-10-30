
/* WARNING: Instruction at (CODE,0xee01) overlaps instruction at (CODE,0xee00)
    */

void FUN_CODE_ee00(char param_1,undefined1 param_2,char param_3,char param_4)

{
  char cVar1;
  
  cVar1 = param_1;
  if (_f_6 == '\x01') {
    cVar1 = param_3 + param_4;
    param_2 = 1;
    param_4 = ' ';
    param_3 = -10;
    BANK0_R2 = param_1;
  }
  sub_ee2f(cVar1,param_2,param_3,param_4);
  return;
}

