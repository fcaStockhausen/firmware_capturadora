
void sub_3d31(undefined1 param_1,undefined1 param_2,undefined1 param_3)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  
  DAT_EXTMEM_1ae8 = 0;
  DAT_EXTMEM_1ae9 = 0;
  DAT_EXTMEM_1aea = 0xa4;
  DAT_EXTMEM_1ae2 = param_3;
  DAT_EXTMEM_1ae3 = param_2;
  DAT_EXTMEM_1ae4 = param_1;
  sub_12da();
  uVar2 = BANK0_R3;
  uVar5 = BANK0_R2;
  uVar4 = sub_d404();
  uVar3 = BANK0_R3;
  uVar1 = BANK0_R2;
  BANK0_R2 = uVar5;
  BANK0_R3 = uVar2;
  sub_0d92(uVar4,uVar1,uVar3,0,0x15);
  uVar5 = sub_d407(0x1ae2);
                    /* WARNING: Subroutine does not return */
  sub_0dd1(4,uVar5);
}

