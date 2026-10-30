
void sub_8837(char param_1,byte param_2,char param_3,undefined1 param_4)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  char cVar4;
  undefined1 uVar5;
  byte bVar6;
  undefined1 *puVar7;
  
  DAT_EXTMEM_1a7a = param_4;
  DAT_EXTMEM_1a7b = param_3;
  DAT_EXTMEM_1a7c = param_2;
  sub_25b0();
  sub_28b3();
  sub_2628(DAT_EXTMEM_1a7a,0x1a89);
  cVar4 = sub_279b();
  if ((cVar4 != '\0') && ((param_2 & 0x10) == 0)) {
    sub_125f(0x1a8c,0);
    nop();
    nop();
    nop();
    uVar5 = sub_25c4(0x1a8c,param_1 + '\x01');
    if (DAT_EXTMEM_1a7b == '\0') {
      uVar3 = 0;
    }
    else {
      uVar3 = 8;
    }
    sub_2752(0,0,uVar3,0,uVar5);
    uVar5 = sub_25c4(0x1a8c);
    sub_2752(0,0,DAT_EXTMEM_1a7c != 0,0,uVar5);
    sub_25f8(0x1a8c);
    uVar2 = BANK0_R3;
    uVar1 = BANK0_R2;
    uVar3 = BANK0_R1;
    uVar5 = BANK0_R0;
    sub_25b3(0x1a89);
    sub_26cb();
    BANK0_R0 = uVar5;
    BANK0_R1 = uVar3;
    BANK0_R2 = uVar1;
    BANK0_R3 = uVar2;
    sub_2660(0x1a8c);
    sub_27ba(0x7d,0x1a);
    puVar7 = &DAT_EXTMEM_1a8c;
    sub_25c4();
    sub_2725();
    *puVar7 = 0x1a;
    puVar7[1] = 0x7d;
    sub_4aef(DAT_EXTMEM_1a7a);
    sub_25b3(0x1a89);
    sub_28a9();
    if (DAT_EXTMEM_1a7c == 0) {
      bVar6 = sub_26c1();
      bVar6 = bVar6 & 0xf7;
    }
    else {
      sub_25b3(0x1a89);
      bVar6 = sub_26c2();
      bVar6 = bVar6 | 0x10;
    }
    sub_0dfe(bVar6);
  }
  return;
}

