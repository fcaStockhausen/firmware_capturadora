
undefined1 sub_470d(void)

{
  byte bVar1;
  
  bVar1 = DAT_SFR_8e;
  DAT_SFR_8e = bVar1 | 7;
  return DAT_EXTMEM_1a75;
}

