
char FUN_CODE_d0a2(char param_1,char *param_2,undefined1 param_3,char param_4)

{
  undefined1 uVar1;
  
  *param_2 = param_1;
  *param_2 = *param_2 + '\x01';
  if (DAT_EXTMEM_1af0 < 4) {
    DAT_EXTMEM_1af1 = (char)((ushort)DAT_EXTMEM_1af0 * 0x12) + '6';
    DAT_EXTMEM_1af6 = 0;
    uVar1 = sub_4079(0x1aed,(char)((ushort)DAT_EXTMEM_1af0 * 0x12 >> 8),param_4 + -1,DAT_EXTMEM_1af1
                     ,DAT_EXTMEM_1af1);
    sub_3fd7(param_3,0x1af7,uVar1);
    sub_3fbb(0x1aea);
                    /* WARNING: Subroutine does not return */
    sub_6aea();
  }
  return DAT_EXTMEM_1af0 - 4;
}

