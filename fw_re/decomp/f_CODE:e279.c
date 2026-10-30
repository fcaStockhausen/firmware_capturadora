
void sub_e279(byte param_1,byte param_2,undefined1 param_3,undefined1 param_4)

{
  DAT_EXTMEM_1afa = param_3;
  DAT_EXTMEM_1afb = param_4;
  *(byte *)CONCAT11(param_3,param_4) =
       param_1 & BANK0_R5 | *(byte *)CONCAT11(param_3,param_4) & ~param_2;
  return;
}

