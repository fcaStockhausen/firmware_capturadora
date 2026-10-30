
void sub_338b(char param_1,byte param_2)

{
  bool bVar1;
  
  bVar1 = CARRY1(DAT_EXTMEM_1b33,param_2);
  DAT_EXTMEM_1b33 = DAT_EXTMEM_1b33 + param_2;
  DAT_EXTMEM_1b32 = DAT_EXTMEM_1b32 + (param_1 - ((bVar1 << 7) >> 7));
  return;
}

