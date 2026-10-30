
void sub_e96a(char param_1)

{
  char cVar1;
  char cVar2;
  
  sub_e971(0xfa);
  cVar1 = -6;
  sub_e16c();
  do {
    nop();
    nop();
    cVar2 = cVar1 + -1;
    if (cVar1 == '\0') {
      param_1 = param_1 + -1;
    }
    cVar1 = cVar2;
  } while (cVar2 != '\0' || param_1 != '\0');
  return;
}

