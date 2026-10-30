
undefined1 sub_c0cb(char param_1)

{
  undefined1 uVar1;
  
  CCAPM3 = 0;
  CCAPM4 = 0;
  if (param_1 == '\0') {
    CMOD = 0xc;
    uVar1 = 0xcc;
    if (DAT_EXTMEM_1c55 != '\0') {
      uVar1 = 0x8c;
    }
    CCAPM0 = uVar1;
  }
  else {
    CMOD = 2;
    uVar1 = 0xc0;
    if (DAT_EXTMEM_1c55 != '\0') {
      uVar1 = 0x80;
    }
    CCAPM0 = uVar1;
  }
  CCAPM1 = 0;
  CCAPM2 = 0;
  CCAPM3 = 0;
  CCAPM4 = 0x78;
  if (param_1 == '\0') {
    CMOD = 0xc;
    uVar1 = 0xcc;
    if (DAT_EXTMEM_1c55 != '\0') {
      uVar1 = 0x8c;
    }
    CCAPM0 = uVar1;
  }
  else {
    CMOD = 2;
    uVar1 = 0xc0;
    if (DAT_EXTMEM_1c55 != '\0') {
      uVar1 = 0x80;
    }
    CCAPM0 = uVar1;
  }
  CCAPM1 = 0;
  CCAPM2 = 0;
  return 0;
}

