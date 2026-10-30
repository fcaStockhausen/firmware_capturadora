
undefined1 sub_0121(undefined1 param_1,byte param_2,char *param_3)

{
  byte in_PSW;
  
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  *param_3 = *param_3 + '\x01';
  if (((char)((in_PSW >> 7 | _0_6 ^ 1) << 7) < '\0') ||
     ((char)(((in_PSW >> 7 | (_0_6 ^ 1) & 1) & ~_0_5) << 7) < '\0')) {
    nop();
    BANK0_R0 = BANK0_R0 + '\x01';
  }
  nop();
  BANK0_R0 = BANK0_R0 + '\x01';
  nop();
  nop();
  return *(undefined1 *)
          CONCAT11((param_2 >> 1 | param_2 << 7) >> 1 | (param_2 >> 1) * -0x80,param_1);
}

