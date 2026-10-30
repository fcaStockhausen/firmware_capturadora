
undefined1 sub_f13a(char param_1,byte *param_2,char param_3,char *param_4,char param_5)

{
  bool bVar1;
  byte bVar2;
  char in_PSW;
  
  nop();
  bVar2 = param_1 + 1;
  *param_2 = bVar2;
  nop();
  nop();
  nop();
  nop();
  nop();
  bVar1 = CARRY1(bVar2,param_5 - (in_PSW >> 7));
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  bVar2 = param_3 + 1U >> 1;
  nop();
  *param_4 = *param_4 + '\x01';
  if (((char)((bVar1 | _0_6 ^ 1) << 7) < '\0') ||
     ((char)(((bVar1 | (_0_6 ^ 1) & 1) & ~_0_5) << 7) < '\0')) {
    nop();
    BANK0_R0 = BANK0_R0 + '\x01';
  }
  nop();
  BANK0_R0 = BANK0_R0 + '\x01';
  nop();
  nop();
  return *(undefined1 *)
          CONCAT11((bVar2 | (param_3 + 1U) * -0x80) >> 1 | bVar2 * -0x80,(char)param_2);
}

