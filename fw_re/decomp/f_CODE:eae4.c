
void sub_eae4(void)

{
  byte bVar1;
  
  sub_d7d6(0x18);
  bVar1 = IEN1;
  IEN1 = bVar1 | 2;
  TXD = 1;
  P2_6 = 1;
  WR = 0;
  P2_7 = 1;
  RD = 0;
  return;
}

