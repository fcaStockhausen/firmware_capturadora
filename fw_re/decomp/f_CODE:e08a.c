
void sub_e08a(void)

{
  undefined1 uVar1;
  char cVar2;
  
  if ((BANK1_R2 != '\x02') && (BANK1_R2 != '\x01')) {
    _2_4 = 1;
    return;
  }
  cVar2 = sub_d42b();
  if (cVar2 == '\x05') {
    uVar1 = 0x4a;
  }
  else {
    uVar1 = 100;
  }
  sub_e318(uVar1,0xf4,0xff,0,0x1a);
  return;
}

