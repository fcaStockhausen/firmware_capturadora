
undefined1 sub_a2ff(char param_1,char param_2,undefined1 param_3)

{
  char in_PSW;
  
  return *(undefined1 *)CONCAT11(param_1 + (param_2 - (in_PSW >> 7)),param_3);
}

