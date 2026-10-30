
void sub_c836(byte param_1,char param_2)

{
  undefined1 uVar1;
  byte bVar2;
  byte in_PSW;
  
  bVar2 = sub_125f(0x1b13);
  nop();
  nop();
  nop();
  DAT_INTMEM_7f = DAT_INTMEM_7f & bVar2;
  in_PSW = in_PSW & 0xdd;
  sub_c925(*(undefined1 *)(ushort)param_1);
  uVar1 = 1;
  sub_ed82();
  sub_125f(0x1b13);
  nop();
  nop();
  nop();
  if ((char)in_PSW < '\0') {
    sub_c925(*(undefined1 *)(ushort)param_1);
    sub_3a41();
    sub_d336();
    sub_cf0a();
    sub_a68a(0,0x20,8);
    sub_38fc();
    sub_d336(0x32);
    sub_38fc();
    sub_d336(0x52);
    sub_38fc();
    sub_d336(0x72);
    return;
  }
  DAT_EXTMEM_1c50 = uVar1;
  DAT_EXTMEM_1c51 = param_2;
  uVar1 = sub_25b0();
  sub_12da(uVar1);
  sub_2749(0x1c50);
  sub_25b0();
  sub_28f7();
  sub_1379();
  if (DAT_EXTMEM_1c51 == '\x05') {
    sub_25b0();
    sub_283c();
  }
  else {
    sub_25aa(0x1c50);
    sub_25eb();
    sub_2952();
  }
  sub_0f94();
  sub_25aa(0x1c50);
  sub_25eb();
  sub_28c4();
  return;
}

