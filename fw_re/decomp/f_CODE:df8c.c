
void sub_df8c(undefined1 param_1)

{
  sub_54b9();
  PSW1 = DAT_EXTMEM_1abe;
  sub_5305(DAT_EXTMEM_1abe,8);
  SOFL = param_1;
  sub_5393(&LAB_CODE_1abb);
  sub_1112(0x10);
  DAT_SFR_d3 = param_1;
  sub_5305(0x18);
  HPINDEX = param_1;
  sub_5487();
  return;
}

