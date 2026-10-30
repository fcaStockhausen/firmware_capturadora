
void sub_6dc5(char param_1,undefined1 param_2,char param_3,byte param_4)

{
  char in_PSW;
  
  *(undefined1 *)CONCAT11((param_3 - (((0xbd < param_4) << 7) >> 7)) + '\x13',param_4 + 0x42) =
       *(undefined1 *)CONCAT11(param_1 + (param_3 - (in_PSW >> 7)),param_2);
  DAT_EXTMEM_1a77 = DAT_EXTMEM_1a77 + '\x01';
  return;
}

