
void sub_ad16(undefined1 param_1)

{
  char cVar1;
  byte bVar2;
  
  sub_ba27(param_1,0x1b73);
  sub_e8e0();
  bVar2 = DAT_EXTMEM_1b73;
  sub_af72();
  if (bVar2 != 0) {
    cVar1 = DAT_EXTMEM_1b74;
    sub_af72();
    if (cVar1 != '\0') {
      sub_e8e0();
      bVar2 = DAT_EXTMEM_1b73 | 1;
      sub_af72();
      if (bVar2 != 0) {
        DAT_EXTMEM_1b7a = 0;
        DAT_EXTMEM_1b7b = 0;
        while (bVar2 = (DAT_EXTMEM_1b75 + (-1 - (((DAT_EXTMEM_1b76 != '\0') << 7) >> 7))) -
                       (((DAT_EXTMEM_1b7b < DAT_EXTMEM_1b76 - 1U) << 7) >> 7),
              DAT_EXTMEM_1b7a < bVar2) {
          sub_c440(0);
          sub_ba12(0x1b77);
          DAT_EXTMEM_1b7b = DAT_EXTMEM_1b7b + 1;
          if (DAT_EXTMEM_1b7b == 0) {
            DAT_EXTMEM_1b7a = DAT_EXTMEM_1b7a + 1;
          }
        }
        sub_c440(DAT_EXTMEM_1b7a - bVar2,1);
        sub_ba32(0x1b77);
      }
    }
  }
  FUN_CODE_e8f7();
  return;
}

