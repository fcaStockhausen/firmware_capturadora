
void sub_ce7b(void)

{
  undefined1 uVar1;
  byte bVar2;
  undefined1 uVar3;
  
  bVar2 = EA;
  DAT_EXTMEM_118c = bVar2 & 1;
  sub_54be();
  uVar1 = PSW1;
  sub_53e2(0,0,0,uVar1);
  uVar1 = BANK0_R0;
  sub_5463();
  BANK0_R0 = uVar1;
  sub_53d6();
  uVar3 = BANK0_R0;
  uVar1 = DAT_SFR_d3;
  sub_5467(0x10,uVar1);
  BANK0_R0 = uVar3;
  sub_53d6();
  uVar1 = BANK0_R0;
  sub_54a1();
  BANK0_R0 = uVar1;
  sub_5429(sub_1188);
  EA = DAT_EXTMEM_118c != 0;
  sub_5393(DAT_EXTMEM_118c - 1,sub_1188);
  return;
}

