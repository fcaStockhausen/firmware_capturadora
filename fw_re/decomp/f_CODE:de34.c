
void sub_de34(char param_1,byte param_2,char param_3)

{
  char in_PSW;
  
  sub_9c59();
  if (in_PSW < '\0') {
    sub_9c3d(0x1bb4);
    sub_9bec();
    DAT_EXTMEM_f6c0 = param_3 + -0x80;
  }
  else if (param_2 < 0x65) {
    sub_9bd5(param_2 + 0x9b,0x1bb4);
    DAT_EXTMEM_f6c0 = param_1 + param_3;
  }
  DAT_EXTMEM_1c06 = param_2;
  return;
}

