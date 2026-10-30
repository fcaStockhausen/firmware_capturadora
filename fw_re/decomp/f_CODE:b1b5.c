
void sub_b1b5(void)

{
  char cVar1;
  undefined1 uVar2;
  
  cVar1 = BANK0_R7;
  sub_125f(0x1ae7);
  nop();
  nop();
  nop();
  nop();
  if (cVar1 == '\x01') {
    if (_0_3 == '\0') {
      sub_db0b(0x1ae4);
      sub_e61a();
    }
    else {
      sub_db0b(0x1ae4);
      sub_d87b();
    }
    uVar2 = 0;
  }
  else if (cVar1 == '\x02') {
    sub_db03();
    if (_0_3 == '\0') {
      uVar2 = sub_e7dc();
    }
    else {
      uVar2 = sub_d4e1();
    }
  }
  else if (cVar1 == '\x03') {
    sub_db03();
    if (_0_3 == '\0') {
      uVar2 = sub_e7f7();
    }
    else {
      uVar2 = sub_d51d();
    }
  }
  else {
    if (cVar1 != '\0') {
      sub_db06(0x1ae7);
      return;
    }
    sub_db03();
    if (_0_3 == '\0') {
      uVar2 = sub_e7c1();
    }
    else {
      uVar2 = sub_d8b1();
    }
  }
                    /* WARNING: Subroutine does not return */
  sub_1253(uVar2,0x1ae7);
}

