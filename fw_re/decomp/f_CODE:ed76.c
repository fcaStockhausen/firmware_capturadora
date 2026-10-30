
char sub_ed76(char param_1,char param_2)

{
  if (param_1 < '\0') {
    param_1 = -(param_1 - (((param_2 != '\0') << 7) >> 7));
  }
  return param_1;
}

