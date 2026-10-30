
void sub_c973(void)

{
  ushort uVar1;
  char cVar2;
  
  DAT_EXTMEM_f0b2 = 0xf;
  DAT_EXTMEM_f0b3 = 0;
  DAT_EXTMEM_f0b4 = 0xff;
  DAT_EXTMEM_f0b5 = 0x1f;
  uVar1 = 0x6f9;
  cVar2 = '\x03';
  do {
    uVar1 = uVar1 >> 1;
    cVar2 = cVar2 + -1;
  } while (cVar2 != '\0');
  DAT_EXTMEM_f0b6 = (char)uVar1;
  DAT_EXTMEM_f0b1 = (DAT_EXTMEM_f0b1 | 0xf3) & 0xfd;
  DAT_EXTMEM_f0b0 = DAT_EXTMEM_f0b0 | 1;
  DAT_EXTMEM_f0b8 = 0x1f;
  return;
}

