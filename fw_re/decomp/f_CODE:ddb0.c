
byte sub_ddb0(void)

{
  DAT_EXTMEM_1aaa = 0;
  do {
    DAT_EXTMEM_1aab = DAT_EXTMEM_d156 & 7;
    if (DAT_EXTMEM_1aab == 7) {
      return 7;
    }
    sub_e971(10);
    DAT_EXTMEM_1aaa = DAT_EXTMEM_1aaa + 1;
  } while ((DAT_EXTMEM_1aaa < 100) << 7 < '\0');
  return DAT_EXTMEM_1aab;
}

