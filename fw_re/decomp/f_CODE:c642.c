
void sub_c642(char param_1)

{
  undefined1 uVar1;
  
  if (param_1 == '\x03') {
    sub_4008();
    sub_40b0();
    uVar1 = 0x40;
  }
  else if (param_1 == '\b') {
    sub_4008();
    sub_40b0();
    uVar1 = 0x10;
  }
  else if (param_1 == '\f') {
    sub_4008();
    sub_40b0();
    uVar1 = 8;
  }
  else if (param_1 == '\x0e') {
    sub_4008();
    sub_40b0();
    uVar1 = 1;
  }
  else if (param_1 == '\n') {
    sub_4008();
    sub_40b0();
    uVar1 = 2;
  }
  else {
    sub_4008();
    sub_40b0();
    uVar1 = 4;
  }
  sub_e279(uVar1,0x7f);
  return;
}

