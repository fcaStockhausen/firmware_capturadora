
void sub_c440(char param_1)

{
  byte bVar1;
  
  DAT_INTMEM_3a = 0;
  P1_0 = 1;
  DAT_INTMEM_39 = 0;
  DAT_EXTMEM_1b7c = param_1;
  do {
    DAT_INTMEM_3a = DAT_INTMEM_3a * '\x02';
    P1_1 = 1;
    sub_e987(DAT_INTMEM_2f);
    bVar1 = P0_0;
    DAT_INTMEM_3a = DAT_INTMEM_3a | bVar1 & 1;
    sub_ba6f();
    sub_e987();
    DAT_INTMEM_39 = DAT_INTMEM_39 + 1;
  } while ((DAT_INTMEM_39 < 8) << 7 < '\0');
  if (DAT_EXTMEM_1b7c == '\0') {
    P0_0 = 0;
    P1_0 = 0;
  }
  else {
    P1_0 = 1;
  }
  sub_e987(DAT_INTMEM_2f);
  P1_1 = 1;
  sub_e987(DAT_INTMEM_2f);
  P0_1 = 0;
  P1_1 = 0;
  P1_0 = 1;
  sub_e987(DAT_INTMEM_2f);
  return;
}

