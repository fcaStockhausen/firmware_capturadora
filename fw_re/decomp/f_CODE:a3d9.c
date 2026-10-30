
char sub_a3d9(char *param_1)

{
  return BANK1_R6 + (((BANK1_R7 < *param_1 + 1U) << 7) >> 7);
}

