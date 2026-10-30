
undefined1 sub_478f(undefined1 param_1,undefined1 param_2,char param_3)

{
  char in_PSW;
  
  BANK3_R6 = param_1;
  BANK3_R5 = param_3 + (BANK3_R5 - (in_PSW >> 7));
  return param_2;
}

