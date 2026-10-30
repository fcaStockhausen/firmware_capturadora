
void sub_b874(void)

{
  char cVar1;
  undefined1 *puVar2;
  
  DAT_EXTMEM_1c5e = '\0';
  puVar2 = &DAT_EXTMEM_1bfd;
  sub_8ba5();
  cVar1 = sub_b8c6();
  if (cVar1 == -1) {
    *puVar2 = 0x5a;
    sub_e848();
    sub_8ba4(0x1bf0);
    sub_8bee();
    sub_b945();
  }
  sub_e848();
  sub_d468(0);
  sub_8ba1();
  cVar1 = sub_b8c6();
  if (cVar1 != -1) {
    sub_e848();
    sub_d468(1);
    sub_8ba1();
    sub_8bee();
    sub_bcc6();
    if (DAT_EXTMEM_1c5e != -1) {
      return;
    }
  }
  return;
}

