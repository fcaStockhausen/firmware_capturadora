
void sub_e597(void)

{
  char cVar1;
  undefined1 uVar2;
  
  sub_3fd6(0x1b73);
  cVar1 = '\0';
  do {
    uVar2 = 0x1b;
    sub_3fbb(0x1b73);
    sub_4094(CONCAT11(uVar2,cVar1));
    cVar1 = cVar1 + '\x01';
  } while (cVar1 != -0x80);
  return;
}

