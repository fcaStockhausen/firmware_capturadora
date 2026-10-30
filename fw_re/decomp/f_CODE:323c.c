
char sub_323c(void)

{
  char in_PSW;
  
  return DAT_EXTMEM_1b23 - (in_PSW >> 7);
}

