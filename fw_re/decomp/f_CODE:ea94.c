
void sub_ea94(void)

{
  char cVar1;
  
  cVar1 = BANK0_R7;
  sub_4008(BANK0_R7);
  sub_41a6();
  sub_e279(cVar1 << 6,0xc0);
  return;
}

