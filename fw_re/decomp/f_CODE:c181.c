
void sub_c181(void)

{
  undefined1 uVar1;
  byte bVar2;
  
  bVar2 = EA;
  DAT_EXTMEM_1abd = bVar2 & 1;
  sub_54be();
  uVar1 = PSW1;
                    /* WARNING: Subroutine does not return */
  sub_1253(0x1ab9,0,0,0,uVar1);
}

