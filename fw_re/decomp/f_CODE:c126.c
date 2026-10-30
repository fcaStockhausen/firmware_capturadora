
void sub_c126(char param_1,undefined1 param_2,byte param_3,undefined1 param_4)

{
  char cVar1;
  undefined1 uVar2;
  byte bVar3;
  char cVar4;
  undefined1 *puVar5;
  
  DAT_EXTMEM_1a8c = param_4;
  sub_125f(0x1a99);
  nop();
  nop();
  nop();
  cVar4 = P1;
  P1 = cVar4 + '\x01';
  uVar2 = DAT_SFR_aa;
  uVar2 = DAT_SFR_aa;
  BANK2_R2 = param_2;
  sub_25eb(param_1 + -1);
  cVar1 = sub_2940();
  cVar4 = '\0';
  if (cVar1 != '\0') {
    uVar2 = sub_2833();
    bVar3 = sub_278f(uVar2);
    cVar4 = bVar3 - 5;
    if (4 < bVar3) {
      uVar2 = sub_25c4(0x1a99);
                    /* WARNING: Subroutine does not return */
      sub_1253(param_2,0x1a99,param_3 | 8,uVar2);
    }
  }
  sub_263b(cVar4,0x8d,0x1a);
  puVar5 = &DAT_EXTMEM_1a99;
  sub_25c4();
  sub_2725();
  *puVar5 = 0x1a;
  puVar5[1] = 0x8d;
  sub_4aef(DAT_EXTMEM_1a8c);
  return;
}

