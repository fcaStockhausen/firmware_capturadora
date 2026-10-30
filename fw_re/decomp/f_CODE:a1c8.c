
void sub_a1c8(undefined1 param_1,char param_2,undefined1 param_3)

{
  char in_PSW;
  
  *(undefined1 *)CONCAT11(param_2 + (-0x2f - (in_PSW >> 7)),param_1) = param_3;
  return;
}

