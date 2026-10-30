
void sub_b225(byte param_1)

{
  undefined1 uVar1;
  
  DAT_EXTMEM_1ab6 = 3;
  DAT_EXTMEM_1ab7 = 0xe8;
  DAT_EXTMEM_1ab8 = 1;
  sub_b284();
  uVar1 = sub_bb51();
                    /* WARNING: Subroutine does not return */
  sub_1253(&LAB_CODE_1ab2,param_1 | 0x40,uVar1);
}

