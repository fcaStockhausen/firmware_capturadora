
undefined1 sub_d1f6(char param_1)

{
  DAT_EXTMEM_1c56 = param_1;
  sub_8bad(0x57,0x7e,0xf4,0x1c);
  if (DAT_EXTMEM_1c56 == '\x03') {
    DAT_EXTMEM_1c57 = 0x15;
  }
  else if (DAT_EXTMEM_1c56 == '\x02') {
    DAT_EXTMEM_1c57 = 0x35;
  }
  sub_ee94();
  sub_8bcc();
  sub_9477();
  sub_8bcc();
  sub_9a8b();
  sub_ee97();
  return DAT_EXTMEM_1c57;
}

