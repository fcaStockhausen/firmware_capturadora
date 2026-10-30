
void sub_e036(void)

{
  char cVar1;
  
  sub_eabc();
  sub_dddc();
  sub_d6f4();
  DAT_EXTMEM_f082 = 0;
  cVar1 = DAT_EXTMEM_11a2;
  if (DAT_EXTMEM_11a2 == '\0') {
    cVar1 = DAT_EXTMEM_11a3;
  }
  if (cVar1 != '\0') {
    DAT_EXTMEM_f21b = 0x3f;
  }
  DAT_EXTMEM_f215 = 1;
  DAT_EXTMEM_f12a = 0;
  return;
}

