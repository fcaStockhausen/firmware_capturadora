
void sub_66b4(void)

{
  char cVar1;
  byte bVar2;
  
  sub_3fd6(0x1b73);
  _1_1 = 0;
  DAT_EXTMEM_1b7c = 0;
  sub_3fd6(0x1b7d);
  cVar1 = sub_0db8();
  if (cVar1 != '\x02') {
    return;
  }
  sub_3fbb(0x1b7d);
  cVar1 = sub_415f();
  if (cVar1 != '\x03') {
    return;
  }
  bVar2 = sub_41ff();
  bVar2 = bVar2 & 0x30;
  sub_3fbb(0x1b76,bVar2);
                    /* WARNING: Subroutine does not return */
  sub_0e10(bVar2,1);
}

