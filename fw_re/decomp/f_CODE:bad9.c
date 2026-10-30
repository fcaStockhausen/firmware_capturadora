
void sub_bad9(void)

{
  undefined1 uVar1;
  
  uVar1 = 0xc;
  sub_ce7b(0xc4);
  DAT_EXTMEM_1a71 = uVar1;
                    /* WARNING: Subroutine does not return */
  sub_1253(0x1c39,0x80,0,0,uVar1);
}

