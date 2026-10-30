
void FUN_CODE_afe7(char param_1)

{
  byte bVar1;
  short sVar2;
  
  if (8 < param_1 - 1U) {
    return;
  }
  sVar2 = -0x500b;
  bVar1 = sub_3204();
                    /* WARNING: Could not recover jumptable at 0xaff4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)(sVar2 + (ushort)bVar1))();
  return;
}

