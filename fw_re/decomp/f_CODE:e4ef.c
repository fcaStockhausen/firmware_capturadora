
void sub_e4ef(byte param_1,byte param_2,undefined1 param_3,undefined1 param_4)

{
  DAT_EXTMEM_1a86 = param_3;
  DAT_EXTMEM_1a87 = param_4;
  sub_ee3d();
  FUN_CODE_ee44(param_1 & param_2 | ~param_2 & BANK0_R7,BANK0_R4,DAT_EXTMEM_1a86,DAT_EXTMEM_1a87);
  return;
}

