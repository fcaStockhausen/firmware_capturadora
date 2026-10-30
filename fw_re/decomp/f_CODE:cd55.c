
void sub_cd55(undefined1 param_1,undefined1 param_2)

{
  char in_PSW;
  
  sub_a2e3(0x1b1b);
  sub_a32a(DAT_EXTMEM_1b1e,0x1b22,DAT_EXTMEM_1b1d);
  if (in_PSW < '\0') {
                    /* WARNING: Subroutine does not return */
    sub_0dd1(CONCAT11(param_1,param_2),DAT_EXTMEM_1b21,DAT_EXTMEM_1b20,DAT_EXTMEM_1b1f);
  }
  return;
}

