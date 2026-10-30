
byte sub_d131(byte param_1)

{
  if (param_1 < 2) {
    return param_1 - 2;
  }
  if ((param_1 != 2) && (param_1 != 3)) {
    if ((param_1 != 4) && (param_1 != 5)) {
      if ((param_1 != 6) && (param_1 != 7)) {
        if (param_1 == 9) {
          return DAT_EXTMEM_1192;
        }
        return param_1;
      }
      return DAT_EXTMEM_1191;
    }
    return DAT_EXTMEM_1190;
  }
  return DAT_EXTMEM_118f;
}

