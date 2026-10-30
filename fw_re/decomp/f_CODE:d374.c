
void FUN_CODE_d374(void)

{
  undefined1 uVar1;
  char cVar2;
  byte bVar3;
  char cVar4;
  
  cVar2 = sub_d6e6(0x1af4);
  if (cVar2 != '\0') {
    cVar2 = (DAT_EXTMEM_1af5 != '\0') << 7;
    bVar3 = DAT_EXTMEM_1af5 - 1;
    cVar4 = sub_d6d6(DAT_EXTMEM_1af4,0x1af6);
    if (cVar2 < '\0') {
      uVar1 = 3;
    }
    else if (bVar3 < 4) {
      cVar4 = '\0';
      uVar1 = 0;
    }
    else {
      cVar4 = bVar3 - 8;
      uVar1 = 0x44;
      if (bVar3 < 8) {
        uVar1 = 0x24;
      }
    }
    sub_e279(cVar4,uVar1,0xff,0xf6,9);
  }
  return;
}

