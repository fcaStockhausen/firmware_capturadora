
void sub_dbaf(void)

{
  undefined1 uVar1;
  undefined1 uVar2;
  
  uVar1 = 0;
  uVar2 = DAT_INTMEM_2e;
  sub_1465(0x13,0x88);
  sub_104c(0,0,4,0);
  DAT_EXTMEM_f052 = uVar2;
  DAT_EXTMEM_f053 = uVar1;
  DAT_EXTMEM_f054 = 0;
  DAT_EXTMEM_f051 = 1;
  TR0 = 1;
  ET0 = 1;
  return;
}

