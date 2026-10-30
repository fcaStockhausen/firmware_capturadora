
void sub_ee91(char param_1)

{
  byte bVar1;
  short sVar2;
  
  DAT_EXTMEM_1aa7 = param_1;
  if (0xf < param_1 - 1U) {
    DAT_EXTMEM_f065 = DAT_EXTMEM_f065 | 8;
    return;
  }
  sVar2 = 0x7d2d;
  bVar1 = sub_3204();
                    /* WARNING: Could not recover jumptable at 0x7d2c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)(sVar2 + (ushort)bVar1))();
  return;
}

