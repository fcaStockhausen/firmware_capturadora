
/* WARNING: Removing unreachable block (CODE,0x58eb) */
/* WARNING: Removing unreachable block (CODE,0x58f6) */
/* WARNING: Removing unreachable block (CODE,0x5900) */
/* WARNING: Removing unreachable block (CODE,0x5903) */
/* WARNING: Removing unreachable block (CODE,0x5959) */
/* WARNING: Removing unreachable block (CODE,0x5977) */
/* WARNING: Removing unreachable block (CODE,0x5984) */
/* WARNING: Removing unreachable block (CODE,0x59b6) */

char sub_585f(byte param_1,byte param_2,undefined1 param_3)

{
  byte bVar1;
  
  DAT_EXTMEM_1abe = 0xff;
  DAT_EXTMEM_1abf = 0xff;
  bVar1 = 7 - (((param_2 < 0xd0) << 7) >> 7);
  if ((bVar1 <= param_1) &&
     (bVar1 = 0x75 - (((param_2 < 0x31) << 7) >> 7), (param_1 < bVar1) << 7 < '\0')) {
    DAT_EXTMEM_1aad = 0;
    DAT_EXTMEM_1aae = 8;
    DAT_EXTMEM_1aaa = param_3;
    DAT_EXTMEM_1aab = param_1;
    DAT_EXTMEM_1aac = param_2;
    sub_1465(0,8,param_1,param_2);
                    /* WARNING: Subroutine does not return */
    sub_1253(0x1ab6);
  }
  DAT_EXTMEM_1aaa = param_3;
  DAT_EXTMEM_1aab = param_1;
  DAT_EXTMEM_1aac = param_2;
  return param_1 - bVar1;
}

