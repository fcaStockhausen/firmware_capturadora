
void sub_c887(byte param_1,byte param_2)

{
  DAT_EXTMEM_1ae5 = param_1;
  DAT_EXTMEM_1ae6 = param_2;
  sub_0016(8,0xfd,4);
  if (DAT_EXTMEM_1ae5 < 0x40U - (((DAT_EXTMEM_1ae6 < 0x75) << 7) >> 7)) {
    DAT_EXTMEM_1ae7 = 1;
  }
  else {
    DAT_EXTMEM_1ae7 = 2;
  }
  sub_d277(0,6,0x17);
  sub_d277(1,0x8c,0xe);
  sub_d277(0x80,0x39,9);
  sub_d277(0,3,0x19);
  return;
}

