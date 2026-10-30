
void sub_d87b(byte param_1,byte param_2)

{
  char cVar1;
  
  sub_3a68(0x1aeb);
  sub_d953();
  DAT_EXTMEM_1aee = param_2 & 0x6f;
  param_1 = param_1 & 0xfe;
  DAT_EXTMEM_1aed = param_1;
  cVar1 = sub_3963(0x1aeb);
  if (cVar1 != '\0' || param_1 != 0) {
    sub_37f9(0,0);
    sub_c925(0xef,0xd0);
  }
  sub_395d(0x1aeb);
  return;
}

