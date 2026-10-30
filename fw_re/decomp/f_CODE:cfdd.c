
char sub_cfdd(undefined1 param_1)

{
  byte bVar1;
  char in_PSW;
  
  bVar1 = *(byte *)CONCAT11(-(in_PSW >> 7),param_1);
  return ((char)bVar1 >> 7) + (-1 - (((0x2f < bVar1) << 7) >> 7));
}

