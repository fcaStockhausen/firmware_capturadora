
void sub_ebff(void)

{
  if (_0_1 != '\0') {
    DAT_EXTMEM_f015 = DAT_EXTMEM_f015 & 0xef;
    return;
  }
  DAT_EXTMEM_f015 = DAT_EXTMEM_f015 | 0x10;
  return;
}

