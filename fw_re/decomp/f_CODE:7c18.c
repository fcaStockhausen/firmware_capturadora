
void sub_7c18(void)

{
  char cVar1;
  undefined1 uVar2;
  undefined1 *puVar3;
  
  sub_3073(0x1aa7);
  DAT_INTMEM_40 = 3;
  DAT_INTMEM_48 = 0;
  DAT_INTMEM_49 = 0;
  DAT_EXTMEM_f008 = DAT_EXTMEM_f008 & 0xfb;
  sub_3258();
  sub_7489();
  sub_ddb0();
  sub_a601(2);
  sub_33b7();
  sub_585f();
  sub_da22(2);
  puVar3 = &DAT_EXTMEM_f017;
  uVar2 = sub_33ea(0x22);
  *puVar3 = uVar2;
  puVar3[1] = 0x88;
  puVar3[2] = 0x88;
  puVar3[3] = 0x82;
  DAT_EXTMEM_f015 = DAT_EXTMEM_f015 | 0x16;
  DAT_EXTMEM_2405 = 0;
  DAT_EXTMEM_2406 = 0;
  _1_4 = 0;
  DAT_EXTMEM_2404 = 0;
  _1_7 = 1;
  DAT_EXTMEM_20ab = sub_33d8();
  sub_3311(DAT_INTMEM_2e);
  sub_e76d();
  sub_e82d();
  sub_3311(0,DAT_INTMEM_2e);
  sub_cde9();
  _0_1 = 0;
  sub_dcf8();
  _0_1 = 1;
  sub_ec67();
  DAT_EXTMEM_f003 = DAT_EXTMEM_f003 | 0x40;
  DAT_EXTMEM_f00b = DAT_EXTMEM_f00b | 0x40;
  DAT_EXTMEM_f014 = 0x23;
  cVar1 = '\0';
  sub_aba2(2);
  _0_1 = 1;
  sub_dfe2();
  sub_cd9f();
  DAT_INTMEM_49 = DAT_INTMEM_49 | cVar1 != '\0';
  sub_ad91();
  sub_c28c();
  sub_2fb4(0x1aa7);
  uVar2 = sub_0db8();
  sub_eda3(uVar2);
  sub_ed98(1);
  sub_2fb4(0x1aa7);
                    /* WARNING: Subroutine does not return */
  sub_0dd1(1);
}

