
undefined1 sub_3052(void)

{
  DAT_EXTMEM_f04d = DAT_EXTMEM_f04d & 0x9f;
  DAT_EXTMEM_f007 = DAT_EXTMEM_f007 & 0xfc;
  DAT_EXTMEM_f04c = DAT_EXTMEM_f04c & 0xfe;
  DAT_EXTMEM_f050 = DAT_EXTMEM_f050 | 1;
  return DAT_EXTMEM_f00b;
}

