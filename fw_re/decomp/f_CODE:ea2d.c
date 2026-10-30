
char sub_ea2d(char param_1)

{
  if ((param_1 != '\x02') && (param_1 != '\x01')) {
    param_1 = '\0';
  }
  return param_1;
}

