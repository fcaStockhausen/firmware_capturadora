
void sub_d336(byte param_1,byte param_2)

{
  byte *pbVar1;
  byte *pbVar2;
  
  sub_3a21(0x1ae7);
  pbVar1 = &DAT_EXTMEM_1ae6;
  DAT_EXTMEM_1ae6 = param_2;
  sub_a45b();
  sub_3a2d();
  pbVar2 = pbVar1 + 1;
  param_1 = ~*pbVar1 & param_1;
  param_2 = param_2 & ~*pbVar2;
  sub_3a2d();
  sub_395d();
  DAT_EXTMEM_1aeb = pbVar2[1] | param_1;
  DAT_EXTMEM_1aec = pbVar2[2] | param_2;
  sub_a68a(DAT_EXTMEM_1aeb,DAT_EXTMEM_1aec,DAT_EXTMEM_1ae6);
  return;
}

