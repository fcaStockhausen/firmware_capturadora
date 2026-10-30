
void sub_326b(byte *param_1)

{
  byte bVar1;
  
  bVar1 = *param_1;
  *param_1 = bVar1 >> 1;
  param_1[1] = param_1[1] >> 1 | bVar1 << 7;
  return;
}

