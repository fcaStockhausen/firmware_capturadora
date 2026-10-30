
void sub_8541(void)

{
  byte bVar1;
  
  bVar1 = RCAP2L;
  RCAP2L = bVar1 | 0xc0;
  bVar1 = EPCONFIG;
  EPCONFIG = bVar1 & 0xbf;
  bVar1 = EPCONFIG;
  EPCONFIG = bVar1 | 0xd0;
  return;
}

