
void sub_31a6(void)

{
  DAT_EXTMEM_f050 = DAT_EXTMEM_f050 & 0xfe;
  DAT_EXTMEM_f00b = DAT_EXTMEM_f00b | 0x80;
  bEXTMEMf00c = bEXTMEMf00c | 1;
  return;
}

