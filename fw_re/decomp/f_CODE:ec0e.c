
void sub_ec0e(char param_1)

{
  if (param_1 == '\x01') {
    DAT_INTMEM_2f = 3;
  }
  else if (param_1 == '\0') {
    DAT_INTMEM_2f = 0xf;
    return;
  }
  return;
}

