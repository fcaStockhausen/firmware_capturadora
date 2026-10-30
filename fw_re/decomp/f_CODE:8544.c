
void sub_8544(void)

{
  byte bVar1;
  
  bVar1 = EPCONFIG;
  EPCONFIG = bVar1 & 0xbf;
  bVar1 = EPCONFIG;
  EPCONFIG = bVar1 | 0xd0;
  return;
}

