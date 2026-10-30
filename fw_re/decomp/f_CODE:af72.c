
void sub_af72(char param_1)

{
  char cVar1;
  byte bVar2;
  char cVar3;
  
  DAT_INTMEM_3a = 0;
  DAT_INTMEM_39 = 0;
  DAT_EXTMEM_1b7c = param_1;
  do {
    if (DAT_EXTMEM_1b7c < '\0') {
      P1_0 = 1;
    }
    else {
      P0_0 = 0;
      P1_0 = 0;
    }
    sub_afda();
    sub_ba6f();
    sub_e987();
    bVar2 = DAT_INTMEM_39;
    DAT_EXTMEM_1b7c = DAT_EXTMEM_1b7c * '\x02';
    DAT_INTMEM_39 = DAT_INTMEM_39 + 1;
  } while ((DAT_INTMEM_39 < 8) << 7 < '\0');
  P1_0 = 1;
  sub_afda(bVar2 - 7);
  cVar3 = '\0';
  DAT_INTMEM_3b = 0;
  DAT_INTMEM_3c = 0;
  while ((cVar1 = P0_0, cVar1 != '\0' &&
         (cVar1 = ((DAT_INTMEM_3c < 2) << 7) >> 7, cVar3 = DAT_INTMEM_3b + cVar1,
         DAT_INTMEM_3b < (byte)-cVar1))) {
    DAT_INTMEM_3c = DAT_INTMEM_3c + 1;
    if (DAT_INTMEM_3c == 0) {
      DAT_INTMEM_3b = DAT_INTMEM_3b + 1;
    }
    cVar3 = sub_e971(1);
  }
  cVar1 = P0_0;
  if (cVar1 != '\x01') {
    DAT_INTMEM_3a = 1;
  }
  sub_ba6f(cVar3);
  sub_e987();
  return;
}

