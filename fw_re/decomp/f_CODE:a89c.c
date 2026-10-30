
void sub_a89c(byte param_1,byte param_2,char param_3)

{
  undefined1 uVar1;
  undefined1 uVar2;
  
  sub_bb3c();
  sub_bb7a(0x1aaf);
  sub_b225();
  if (param_3 != '\0') {
    return;
  }
  uVar1 = sub_bb3f(0x1aaf);
  sub_1138(uVar1);
  uVar1 = 0;
  sub_1112(0xc,0,param_1 & 3,param_2 & 0xf0,0);
  uVar2 = sub_bb3c();
                    /* WARNING: Subroutine does not return */
  sub_0e10(uVar1,0xf0,uVar2);
}

