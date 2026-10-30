
void sub_d468(char param_1)

{
  byte bVar1;
  
  DAT_EXTMEM_1c58 = param_1;
  sub_8bb1(0x59,0x90,0xf4,0xff,0x1c,1);
  DAT_EXTMEM_1c59 = 199;
  if (DAT_EXTMEM_1c58 != '\0') {
    DAT_EXTMEM_1c59 = 0x60;
  }
  sub_ee94();
  sub_8be0(0x59,0x1c);
  sub_9477();
  sub_ee97();
  do {
    bVar1 = 1;
    sub_d1f6();
  } while ((bVar1 & 1) == 1);
  return;
}

