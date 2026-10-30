
char sub_a3d6(void)

{
  return BANK1_R6 + (((BANK1_R7 < cEXTMEM102b + 1U) << 7) >> 7);
}

