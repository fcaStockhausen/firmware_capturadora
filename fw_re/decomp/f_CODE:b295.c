
char sub_b295(byte param_1,byte param_2,char param_3,char param_4)

{
  byte bVar1;
  byte bVar2;
  char cVar3;
  byte *pbVar4;
  
  DAT_EXTMEM_1af6 = 0x10;
  DAT_EXTMEM_1af7 = '\0';
  DAT_EXTMEM_1af4 = param_1;
  DAT_EXTMEM_1af5 = param_2;
  if (param_2 != 0 || param_1 != 0) {
    pbVar4 = &DAT_EXTMEM_1af4;
    bVar1 = param_3 - (((param_2 < param_4 + 1U) << 7) >> 7);
    if (bVar1 <= param_1) {
      sub_1465(param_1 - bVar1,0x10,0);
      bVar2 = pbVar4[1] >> 1 | *pbVar4 << 7;
      cVar3 = BANK0_R7 + bVar2;
      bVar1 = DAT_EXTMEM_1af4;
      sub_104c(0,0,BANK0_R6,DAT_EXTMEM_1af5,BANK0_R4,
               BANK0_R5 -
               ((CARRY1(BANK0_R6,(*pbVar4 >> 1) - ((CARRY1(BANK0_R7,bVar2) << 7) >> 7)) << 7) >> 7))
      ;
      DAT_EXTMEM_1af6 = bVar1;
      DAT_EXTMEM_1af7 = cVar3;
    }
  }
  return DAT_EXTMEM_1af7;
}

