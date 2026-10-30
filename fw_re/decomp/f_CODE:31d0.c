
void sub_31d0(char param_1,short param_2)

{
  *(char *)(param_2 + 1) = param_1 + '\x01';
  *(char *)(param_2 + 2) = param_1 + '\x02';
  return;
}

