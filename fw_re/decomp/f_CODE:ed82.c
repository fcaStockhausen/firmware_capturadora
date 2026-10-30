
void sub_ed82(void)

{
  char cVar1;
  
  cVar1 = BANK0_R7;
  do {
    sub_e96a();
    sub_e96a();
    cVar1 = cVar1 + -1;
  } while (cVar1 != '\0');
  return;
}

