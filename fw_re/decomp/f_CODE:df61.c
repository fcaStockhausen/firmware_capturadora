
void sub_df61(undefined1 param_1)

{
  sub_54b9();
  PSW1 = DAT_EXTMEM_1c3c;
  sub_52f4(DAT_EXTMEM_1c3c,8);
  SOFL = param_1;
  sub_52f4(0x10);
  DAT_SFR_d3 = param_1;
  sub_5393(0x1c39);
  sub_1112(0x18);
  HPINDEX = param_1;
  sub_5487();
  return;
}

