
void sub_d6f4(char param_1,char param_2)

{
  undefined1 uVar1;
  byte bVar2;
  
  sub_c393();
  uVar1 = sub_bb3c();
  sub_0f94(0xde,0,uVar1);
  sub_e863();
  bVar2 = sub_bb3c();
  sub_eb8a(bVar2 - 0x2b,param_1 - (((0x2a < bVar2) << 7) >> 7));
  sub_a89c();
  if (param_2 != '\0') {
    return;
  }
  sub_df0b();
  sub_d91d();
  if (param_2 != '\0') {
    return;
  }
  sub_ac9a();
  sub_e1d6();
  return;
}

