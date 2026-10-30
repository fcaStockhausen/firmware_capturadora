
void sub_9310(byte param_1,byte param_2,char param_3)

{
  byte bVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  
  DAT_EXTMEM_1aec = param_3;
  DAT_EXTMEM_1aed = param_1;
  DAT_EXTMEM_1aee = param_2;
  if (param_3 == '\x01') {
    sub_3905();
    sub_d9ef(1);
    sub_93b8(0x11,0x1f,0x11,0x1f,0x11,0x1f);
    sub_3905();
    uVar3 = 1;
  }
  else if (param_3 == '\x02') {
    sub_38bb();
    uVar3 = 0x21;
  }
  else {
    if (param_3 == '\x03') goto LAB_CODE_93ab;
    if (param_3 == '\r') {
      uVar3 = 0;
      uVar2 = 0;
      uVar4 = 0;
LAB_CODE_9399:
      sub_93b8(uVar3,0x1f,uVar2,0x1f,uVar4,0x1f);
      goto LAB_CODE_93ab;
    }
    if (param_3 == '\x0e') {
      sub_38bb();
      uVar3 = 0x21;
    }
    else {
      if (param_3 != '\x0f') {
        sub_ed52();
        goto LAB_CODE_93ab;
      }
      bVar1 = 0x42 - (((param_2 < 0x68) << 7) >> 7);
      if (param_1 < bVar1) {
        uVar3 = 0x41;
        uVar2 = 0x41;
        uVar4 = 0x41;
        goto LAB_CODE_9399;
      }
      sub_38bd(param_1 - bVar1,0x1f);
      uVar3 = 0x21;
    }
  }
  sub_d9ef(uVar3);
LAB_CODE_93ab:
  sub_e971(0xfa);
  sub_e971(0xfa);
  sub_deb5();
  return;
}

