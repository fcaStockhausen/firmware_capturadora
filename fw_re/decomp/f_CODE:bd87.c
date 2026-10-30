
void sub_bd87(char param_1)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  char cVar4;
  
  DAT_EXTMEM_f006 = 0xf0;
  bVar3 = 0;
  bVar2 = 0x77;
  DAT_EXTMEM_1aa9 = param_1;
  sub_d0aa(0,0,0,param_1,0,1);
  bVar1 = 0x12 - (((bVar3 < 0xc0) << 7) >> 7);
  cVar4 = bVar2 - bVar1;
  DAT_EXTMEM_2407 = bVar2;
  DAT_EXTMEM_2408 = bVar3;
  if (bVar2 < bVar1) {
    DAT_EXTMEM_2407 = 0x12;
    cVar4 = -0x40;
    DAT_EXTMEM_2408 = 0xc0;
  }
  sub_3258(cVar4);
  cVar4 = '\0';
  sub_316d(0);
  if (cVar4 < '\0') {
    DAT_EXTMEM_2407 = 0x84;
    DAT_EXTMEM_2408 = 0xd0;
  }
  sub_3258();
  sub_7489();
  sub_ddb0();
  DAT_EXTMEM_f006 = DAT_EXTMEM_1aa9 + -1;
  return;
}

