
void sub_d174(void)

{
  DAT_EXTMEM_1ae2 = DAT_EXTMEM_d140;
  DAT_EXTMEM_1ae3 = DAT_EXTMEM_f00e;
  if (((DAT_EXTMEM_d140 & 7) != 0) && ((DAT_EXTMEM_f00e & 1) != 1)) {
    DAT_EXTMEM_d140 = DAT_EXTMEM_d140 & 0xf8;
    DAT_EXTMEM_f00e = DAT_EXTMEM_f00e | 1;
    sub_ed82(10);
    DAT_EXTMEM_d140 = DAT_EXTMEM_1ae2;
    DAT_EXTMEM_f00e = DAT_EXTMEM_1ae3;
  }
  DAT_EXTMEM_1ae2 = DAT_EXTMEM_d140;
  DAT_EXTMEM_1ae3 = DAT_EXTMEM_f00e;
  return;
}

