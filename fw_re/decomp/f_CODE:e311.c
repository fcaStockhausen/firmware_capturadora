
char sub_e311(char *param_1)

{
  char cVar1;
  
  cVar1 = *param_1;
  *param_1 = cVar1 + '\x01';
  return cVar1;
}

