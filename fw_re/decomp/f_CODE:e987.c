
void sub_e987(char param_1,char param_2)

{
  char cVar1;
  
  sub_e16c();
  do {
    nop();
    nop();
    cVar1 = param_2 + -1;
    if (param_2 == '\0') {
      param_1 = param_1 + -1;
    }
    param_2 = cVar1;
  } while (cVar1 != '\0' || param_1 != '\0');
  return;
}

