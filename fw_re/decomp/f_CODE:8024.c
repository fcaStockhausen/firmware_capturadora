
void sub_8024(char param_1,char param_2)

{
  char in_PSW;
  
  FUN_CODE_7fd6(param_1 - (param_2 - (in_PSW >> 7)),0x80a5);
  return;
}

