
void sub_eb30(char param_1)

{
  if (param_1 != '\0') {
    sub_319d(DAT_EXTMEM_f065 | 0x10);
    return;
  }
  DAT_EXTMEM_f065 = DAT_EXTMEM_f065 & 0xef;
  return;
}

