
char sub_aa23(char param_1,char param_2)

{
  char cVar1;
  byte bVar2;
  undefined1 *puVar3;
  
  DAT_EXTMEM_1a7a = param_2;
  DAT_EXTMEM_1a7b = param_1;
  sub_25b0();
  sub_28b3();
  sub_2628(DAT_EXTMEM_1a7a,0x1a88);
  cVar1 = sub_284b();
  if (cVar1 == '\x01') {
    return '\x01';
  }
  sub_263b(0x7c,0x1a);
  if (DAT_EXTMEM_1a7b == '\0') {
    cVar1 = DAT_EXTMEM_1a7a;
    sub_c126();
    if (cVar1 != '\0') {
      DAT_EXTMEM_1a8b = cVar1;
      return cVar1;
    }
    DAT_EXTMEM_1a8b = cVar1;
    sub_25b3(0x1a88);
    bVar2 = sub_26c2();
    bVar2 = bVar2 & 0xf9;
  }
  else {
    puVar3 = &DAT_EXTMEM_1b91;
    cVar1 = sub_125f();
    nop();
    nop();
    nop();
    sub_272c(cVar1 + '\x01');
    *puVar3 = 0x1a;
    puVar3[1] = 0x7c;
    cVar1 = DAT_EXTMEM_1a7a;
    sub_4aef();
    if (cVar1 != '\0') {
      DAT_EXTMEM_1a8b = cVar1;
      return cVar1;
    }
    DAT_EXTMEM_1a8b = cVar1;
    sub_25b3(0x1a88);
    bVar2 = sub_26c2();
    bVar2 = bVar2 | 2;
  }
  sub_0dfe(bVar2);
  return DAT_EXTMEM_1a8b;
}

