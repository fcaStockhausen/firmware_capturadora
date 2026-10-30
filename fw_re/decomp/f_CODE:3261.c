
void sub_3261(byte *param_1)

{
  *param_1 = *param_1 & 3;
  param_1[1] = param_1[1] & 0xfe;
  return;
}

