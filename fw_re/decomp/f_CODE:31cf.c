
void sub_31cf(char param_1,char *param_2)

{
  *param_2 = param_1;
  param_2[1] = param_1 + '\x01';
  param_2[2] = param_1 + '\x02';
  return;
}

