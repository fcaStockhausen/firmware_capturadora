
void FUN_CODE_e74f(void)

{
  char cVar1;
  byte bVar2;
  char cVar3;
  char in_PSW;
  
  sub_c0cb(0);
  do {
    cVar1 = sub_6e53();
    bVar2 = sub_6ea4(cVar1 + (-0x10 - (in_PSW >> 7)));
    in_PSW = (bVar2 < 0x30) << 7;
  } while (bVar2 != 0x30);
  bVar2 = 0;
  cVar1 = '\0';
  do {
    cVar3 = sub_6e53(bVar2);
    bVar2 = sub_6ea4(cVar3 + (-0xe - (cVar1 >> 7)));
    cVar1 = (bVar2 < 0x30) << 7;
  } while (bVar2 != 0x30);
  return;
}

