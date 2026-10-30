
void sub_38c6(undefined1 param_1,undefined1 param_2)

{
  char in_PSW;
  
  *(undefined1 *)CONCAT11(-0x1e - (in_PSW >> 7),param_1) = param_2;
  DAT_EXTMEM_1a84 = DAT_EXTMEM_1a84 + '\x01';
  return;
}

