
void sub_dddc(char param_1,char param_2)

{
  char cVar1;
  
  DAT_EXTMEM_f209 = 2;
  DAT_EXTMEM_f221 = 3;
  cVar1 = sub_6da7(0x11a8);
  if ((param_1 != '\0' || cVar1 != '\0') || param_2 != '\0') {
    sub_145f();
  }
  DAT_EXTMEM_f20e = 8;
  DAT_EXTMEM_f00b = DAT_EXTMEM_f00b & 0xfe | 1;
  return;
}

