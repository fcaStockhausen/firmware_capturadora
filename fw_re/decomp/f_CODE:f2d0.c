
/* WARNING: Control flow encountered bad instruction data */

byte sub_f2d0(byte param_1,undefined1 *param_2,char param_3)

{
  byte bVar1;
  char in_PSW;
  
  bVar1 = param_3 - (in_PSW >> 7);
  DAT_INTMEM_48 = DAT_INTMEM_48 | 0xf5;
  HPSTAT = *param_2;
  if (param_3 == '\x01') {
    return ((byte)(param_2 +
                  (((param_1 | (byte)param_2) - bVar1 & 0x4b) * '\x02' -
                  ((((param_1 | (byte)param_2) < bVar1) << 7) >> 7))) | 0x34) ^ DAT_INTMEM_23 | 0xd2
    ;
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

