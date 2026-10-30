
void sub_cec3(void)

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
      uVar1 = 4;
    }
    else {
      cVar4 = bVar3 - 2;
      if (bVar3 < 2) {
        uVar1 = 8;
      }
      else {
        cVar4 = bVar3 - 4;
        if (bVar3 < 4) {
          uVar1 = 0x10;
        }
        else {
          cVar4 = bVar3 - 8;
          uVar1 = 0x30;
          if (bVar3 < 8) {
            uVar1 = 0x20;
          }
        }
      }
    }
    sub_e279(cVar4,uVar1,0x3c,0xf6,1);
  }
  return;
}

