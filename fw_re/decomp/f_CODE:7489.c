
/* WARNING: Removing unreachable block (CODE,0x750c) */

char sub_7489(byte param_1,byte param_2)

{
  byte bVar1;
  char cVar2;
  char cVar3;
  
  bVar1 = 1 - (((param_2 < 0x90) << 7) >> 7);
  cVar3 = (param_1 < bVar1) << 7;
  cVar2 = param_1 - bVar1;
  DAT_EXTMEM_1aaa = param_1;
  DAT_EXTMEM_1aab = param_2;
  if ((param_1 >= bVar1) && (cVar2 = sub_10eb(0,0,0x84,0xd0,0,0,param_1,param_2), -1 < cVar3)) {
    DAT_EXTMEM_1aac = 1;
    DAT_EXTMEM_1aad = 7;
    sub_1465(DAT_EXTMEM_1aaa,DAT_EXTMEM_1aab,uCODEf3d8,uCODEf3d9);
                    /* WARNING: Subroutine does not return */
    sub_1253(&LAB_CODE_1aac_2);
  }
  return cVar2;
}

