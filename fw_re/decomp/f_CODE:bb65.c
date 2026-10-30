
char sub_bb65(char param_1)

{
  char in_PSW;
  
  return param_1 + (-0x3c - (in_PSW >> 7));
}

