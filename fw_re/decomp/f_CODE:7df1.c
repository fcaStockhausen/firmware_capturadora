
void sub_7df1(void)

{
  sub_dabb();
  DAT_EXTMEM_f015 = DAT_EXTMEM_f015 & 0xef;
  DAT_EXTMEM_f005 = DAT_EXTMEM_f005 | 0x10;
  DAT_EXTMEM_f01f = DAT_EXTMEM_f01f & 0x9f;
  DAT_EXTMEM_f0a6 = DAT_EXTMEM_f0a6 & 0xfe;
  return;
}

