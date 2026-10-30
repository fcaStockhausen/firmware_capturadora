
void sub_ebf0(void)

{
  if (_0_1 != '\0') {
    DAT_EXTMEM_f015 = DAT_EXTMEM_f015 & 0xfb;
    return;
  }
  DAT_EXTMEM_f015 = DAT_EXTMEM_f015 | 4;
  return;
}

