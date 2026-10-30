
void sub_cd0b(undefined1 param_1,char param_2)

{
  undefined1 uVar1;
  char in_PSW;
  
  sub_a2e3(0x1b15);
  sub_a32a(DAT_EXTMEM_1b18,0x1b1c,DAT_EXTMEM_1b17);
  if (in_PSW < '\0') {
    uVar1 = sub_a2ff(DAT_EXTMEM_1b15,DAT_EXTMEM_1b16 + param_2);
                    /* WARNING: Subroutine does not return */
    sub_0e10(uVar1,CONCAT11(param_1,DAT_EXTMEM_1b1d),DAT_EXTMEM_1b1b,DAT_EXTMEM_1b1a,DAT_EXTMEM_1b19
            );
  }
  return;
}

