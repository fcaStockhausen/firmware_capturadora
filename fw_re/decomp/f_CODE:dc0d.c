
void sub_dc0d(void)

{
  char cVar1;
  char cVar2;
  
  sub_3fd6(0x1aea);
  cVar1 = sub_0db8();
  if (cVar1 == '\0') {
    sub_3fbb(0x1aea);
    cVar1 = sub_4159();
    if (cVar1 == '\0') {
      cVar1 = '\x01';
      do {
        sub_3fbb(0x1aea);
        cVar2 = sub_4092();
        if (cVar2 != -1) {
          return;
        }
        cVar1 = cVar1 + '\x01';
      } while (cVar1 != '\a');
      return;
    }
  }
  return;
}

