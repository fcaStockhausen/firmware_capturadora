
void sub_eb78(char param_1)

{
  char cVar1;
  char in_PSW;
  
  sub_125f(0x1af9);
  nop();
  nop();
  nop();
  cVar1 = func_0x5312();
  nop();
                    /* WARNING: Subroutine does not return */
  sub_0dd1(0xf1,cVar1 - (param_1 - (in_PSW >> 7)));
}

