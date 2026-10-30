
void sub_c4ec(char param_1,char param_2,char param_3,char param_4,char param_5,char param_6)

{
  char cVar1;
  
  DAT_EXTMEM_1a77 = param_5;
  sub_9f53();
  sub_b80b();
  DAT_EXTMEM_1a78 = param_6;
  cVar1 = sub_9f61();
  if ((cVar1 != '\0') || (param_1 != '\0')) {
    return;
  }
  sub_9f53();
  sub_e4a9();
  if ((param_3 == '\0' && param_2 == '\0') && param_4 == '\0') {
    return;
  }
  if (DAT_EXTMEM_1a77 == '\0') {
                    /* WARNING: Subroutine does not return */
    sub_0dd1(8);
  }
  cVar1 = DAT_EXTMEM_1a78;
  sub_aa23(DAT_EXTMEM_1a77);
  if (cVar1 != '\0') {
    return;
  }
  return;
}

