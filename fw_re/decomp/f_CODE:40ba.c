
char sub_40ba(char param_1)

{
  char in_PSW;
  
  return param_1 + (-5 - (in_PSW >> 7));
}

