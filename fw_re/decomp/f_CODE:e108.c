
void FUN_CODE_e108(void)

{
  undefined1 uVar1;
  undefined1 uVar2;
  
  if (BANK1_R2 == '\x02') {
    DAT_EXTMEM_12f5 = 0;
    uVar2 = sub_a420();
    uVar1 = 2;
  }
  else {
    if (BANK1_R2 != '\x01') {
      _2_4 = 1;
      return;
    }
    uVar2 = sub_a421(0,0x12f5);
    uVar1 = 1;
  }
  sub_e318(uVar2,uVar1);
  return;
}

