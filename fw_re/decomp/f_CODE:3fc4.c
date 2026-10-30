
void sub_3fc4(byte param_1,short param_2,char param_3,undefined1 param_4)

{
  DAT_EXTMEM_1b77 = param_4;
  cEXTMEM1b78 = param_3 - ((CARRY1(*(byte *)(param_2 + 2),param_1) << 7) >> 7);
  cEXTMEM1b79 = *(byte *)(param_2 + 2) + param_1;
  return;
}

