
void sub_c496(char param_1,char param_2)

{
  byte bVar1;
  char cVar2;
  undefined1 uVar3;
  
  DAT_EXTMEM_1a76 = 1;
  while( true ) {
    if (9 < DAT_EXTMEM_1a76) {
      return;
    }
    bVar1 = DAT_EXTMEM_1a76;
    sub_25b0(DAT_EXTMEM_1a76 - 10,DAT_EXTMEM_1a76);
    sub_28b3();
    sub_2694(bVar1);
    cVar2 = sub_2632(0x1a77);
    if ((cVar2 != '\0' || param_1 != '\0') || param_2 != '\0') break;
    DAT_EXTMEM_1a76 = DAT_EXTMEM_1a76 + 1;
  }
  uVar3 = sub_25b3(0x1a77);
                    /* WARNING: Subroutine does not return */
  sub_0dd1(8,uVar3);
}

