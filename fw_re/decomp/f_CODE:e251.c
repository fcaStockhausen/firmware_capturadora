
void sub_e251(char param_1,char param_2)

{
  char cVar1;
  
  _1_1 = 0;
  DAT_EXTMEM_1b73 = param_2;
  DAT_EXTMEM_1b74 = param_1;
  sub_e8e0();
  cVar1 = DAT_EXTMEM_1b73;
  sub_af72();
  if (cVar1 != '\0') {
    cVar1 = DAT_EXTMEM_1b74;
    sub_af72();
    if (cVar1 != '\0') {
      _1_1 = 1;
    }
  }
  return;
}

