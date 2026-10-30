
void sub_e486(void)

{
  sub_ec91();
  sub_ed82(200);
  sub_ed82(200);
  BANK2_R0 = 0;
  DAT_EXTMEM_f21e = 0x58;
  EA = 0;
  DAT_EXTMEM_12a4 = 0;
  sub_e036();
  EA = 1;
  return;
}

