
void sub_9258(void)

{
  char cVar1;
  undefined1 uVar2;
  
  sub_3fd6(0x1ae2);
  _0_6 = 0;
  sub_e812();
  sub_e279(4,4,0xf0,5);
  sub_3fb8();
  sub_41e9();
  sub_c887();
  sub_3fb8();
  sub_41e9();
  sub_81f1();
  _0_6 = 1;
  sub_e812();
  _0_6 = 1;
  sub_ebe0();
  sub_e00c();
  sub_3fb8();
  cVar1 = sub_0db8();
  _0_6 = cVar1 != '\0';
  sub_e9d8();
  sub_3fb8();
  cVar1 = sub_4159();
  if (cVar1 == '\x01') {
    cVar1 = sub_41f3();
    if (cVar1 != '\0') {
      uVar2 = 0;
      goto LAB_CODE_92b1;
    }
  }
  sub_3fb8();
  uVar2 = sub_4159();
LAB_CODE_92b1:
  sub_ea94(uVar2);
  sub_3fb8();
  uVar2 = sub_41f3();
  sub_dee0(uVar2);
  sub_3fb8();
                    /* WARNING: Subroutine does not return */
  sub_0dd1(0xf);
}

