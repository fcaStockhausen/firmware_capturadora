
void sub_da55(void)

{
  undefined1 uVar1;
  char cVar2;
  
  if (BANK1_R2 == '\x02') {
    uVar1 = sub_ccc8(0,0x12f5,0);
  }
  else {
    if (BANK1_R2 == '\x01') {
      cVar2 = BANK1_R2;
      sub_ed5e();
      sub_ccc8(cVar2,0x12f5);
    }
    else {
      sub_ccf1();
    }
    uVar1 = 0;
  }
  sub_e318(uVar1);
  return;
}

