
undefined1 sub_544b(char param_1,short param_2)

{
  byte in_PSW;
  
  *(byte *)(param_2 + 1) = param_1 << 1 | in_PSW >> 7;
  EA = 0;
  CCAPM3 = 0;
  return 0;
}

