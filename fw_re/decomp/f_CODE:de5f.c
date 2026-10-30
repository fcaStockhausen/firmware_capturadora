
void sub_de5f(char param_1,byte param_2,char param_3)

{
  char in_PSW;
  
  sub_9c59();
  if (in_PSW < '\0') {
    sub_9c3d(0x1bb5);
    sub_9bec();
    DAT_EXTMEM_f6c3 = param_3 + -0x80;
  }
  else if (param_2 < 0x65) {
    sub_9bd5(param_2 + 0x9b,0x1bb5);
    DAT_EXTMEM_f6c3 = param_1 + param_3;
  }
  DAT_EXTMEM_1c08 = param_2;
  return;
}

