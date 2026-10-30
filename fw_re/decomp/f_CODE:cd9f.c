
void sub_cd9f(void)

{
  char in_PSW;
  
  if (((DAT_EXTMEM_1c49 & 1) != 0) && (sub_e5fa(), in_PSW < '\0')) {
    DAT_EXTMEM_1c48 = 1;
    return;
  }
  if (((DAT_EXTMEM_1c49 >> 1 & 1) != 0) && (sub_8abb(), in_PSW < '\0')) {
    DAT_EXTMEM_1c48 = 2;
    return;
  }
  if ((DAT_EXTMEM_1c49 >> 2 & 1) != 0) {
    sub_ce33();
    sub_edf4();
    sub_e971(0x3c);
    sub_ee59();
    if (in_PSW < '\0') {
      DAT_EXTMEM_1c48 = 4;
      return;
    }
  }
  return;
}

