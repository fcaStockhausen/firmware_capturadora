
void sub_e8e0(void)

{
  P1_0 = 1;
  P1_1 = 1;
  sub_e987(DAT_INTMEM_2f);
  P0_0 = 0;
  P1_0 = 0;
  sub_e987(DAT_INTMEM_2f);
  P0_1 = 0;
  P1_1 = 0;
  return;
}

