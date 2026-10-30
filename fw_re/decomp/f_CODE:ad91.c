
void sub_ad91(void)

{
  undefined1 *puVar1;
  
  DAT_EXTMEM_f583 = 0x10;
  DAT_EXTMEM_f58c = 0x25;
  sub_ee2f(1,0xf0,0x56);
  DAT_EXTMEM_f597 = 0xc0;
  DAT_EXTMEM_f598 = 3;
  DAT_EXTMEM_f599 = 0xc0;
  DAT_EXTMEM_f59a = 3;
  DAT_EXTMEM_f591 = 0;
  DAT_EXTMEM_f592 = 0;
  DAT_EXTMEM_f593 = 0;
  puVar1 = &DAT_EXTMEM_f584;
  sub_a01a();
  *puVar1 = 0xf;
  DAT_EXTMEM_f594 = 0;
  DAT_EXTMEM_f595 = 0;
  DAT_EXTMEM_f596 = 0x10;
  puVar1 = &DAT_EXTMEM_f587;
  sub_a01a();
  *puVar1 = 0x1f;
  DAT_EXTMEM_f5a5 = 0;
  DAT_EXTMEM_f5a6 = 0;
  DAT_EXTMEM_f5a7 = 0x18;
  puVar1 = &DAT_EXTMEM_f5a8;
  sub_a01a();
  *puVar1 = 0x1f;
  sub_ee2f(0x20,0xf5,0x81);
  sub_ee2f(1,0xf5,0x81);
  sub_ee2f(0x80,0xf5,0x8b);
  return;
}

