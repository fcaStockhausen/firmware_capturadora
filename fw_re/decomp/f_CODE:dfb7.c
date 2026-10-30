
void FUN_CODE_dfb7(void)

{
  undefined1 uVar1;
  undefined1 uVar2;
  
  if (BANK1_R2 == '\x02') {
    sub_a446();
    uVar1 = sub_a420(0);
    uVar2 = 2;
  }
  else {
    if (BANK1_R2 != '\x01') {
      _2_4 = 1;
      return;
    }
    uVar2 = sub_a446();
    uVar1 = 0;
  }
  sub_e318(uVar1,uVar2);
  return;
}

