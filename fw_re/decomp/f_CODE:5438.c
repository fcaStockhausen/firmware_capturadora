
undefined1
sub_5438(undefined1 *param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,
        undefined1 param_5,undefined1 param_6)

{
  byte bVar1;
  
  *param_1 = param_5;
  param_1[1] = param_6;
  param_1[2] = param_4;
  param_1[3] = param_3;
  param_1[4] = param_2;
  bVar1 = EA;
  param_1[5] = bVar1 & 1;
  EA = 0;
  CCAPM3 = 0;
  return 0;
}

