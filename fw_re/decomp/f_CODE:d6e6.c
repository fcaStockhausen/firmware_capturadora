
byte sub_d6e6(undefined1 *param_1,byte param_2,byte param_3,undefined1 param_4,undefined1 param_5)

{
  *param_1 = param_4;
  param_1[1] = param_5;
  param_1[2] = param_2;
  param_1[3] = param_3;
  return param_3 | param_2;
}

