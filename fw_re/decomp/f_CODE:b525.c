
void sub_b525(void)

{
  if (DAT_EXTMEM_1029 != DAT_INTMEM_33) {
    EA = 0;
    if ((DAT_INTMEM_33 == '\0') || (DAT_EXTMEM_12a4 != '\x01')) {
      if (DAT_INTMEM_33 == '\0') {
        DAT_EXTMEM_1029 = DAT_INTMEM_33;
        sub_d681();
      }
    }
    else {
      DAT_EXTMEM_1029 = DAT_INTMEM_33;
      if (DAT_INTMEM_36 != '\0') {
        DAT_INTMEM_36 = '\0';
        sub_48bf();
      }
      sub_99e6();
    }
    EA = 1;
  }
  if ((DAT_INTMEM_36 != '\0') && (DAT_INTMEM_33 != '\0')) {
    DAT_INTMEM_36 = '\0';
    sub_48bf();
  }
  if (DAT_EXTMEM_102a != DAT_INTMEM_34) {
    DAT_EXTMEM_102a = DAT_INTMEM_34;
    if (DAT_INTMEM_34 == '\0') {
      sub_ee1f();
    }
    else {
      sub_ee27();
    }
  }
  if (DAT_EXTMEM_11ad == '\x01') {
    DAT_EXTMEM_102a = '\0';
  }
  FUN_CODE_993b();
  return;
}

