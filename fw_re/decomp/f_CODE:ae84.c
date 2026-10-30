
char sub_ae84(char param_1,byte param_2)

{
  byte bVar1;
  byte bVar2;
  char cVar3;
  char cVar4;
  byte in_PSW;
  byte *pbVar5;
  
  DAT_EXTMEM_1aee = param_1;
  DAT_EXTMEM_1aef = param_2;
  sub_97e2(0xf1,0x1a,1);
  DAT_EXTMEM_1af0 = in_PSW >> 7;
  cVar3 = ((DAT_EXTMEM_1af2 == '\0') << 7) >> 7;
  cVar4 = DAT_EXTMEM_1af1 + cVar3;
  if (DAT_EXTMEM_1af1 < (byte)-cVar3) {
    cVar3 = ((DAT_EXTMEM_1af4 == '\0') << 7) >> 7;
    cVar4 = DAT_EXTMEM_1af3 + cVar3;
    if ((DAT_EXTMEM_1af3 < (byte)-cVar3) &&
       (cVar3 = ((DAT_EXTMEM_1af6 == '\0') << 7) >> 7, cVar4 = DAT_EXTMEM_1af5 + cVar3,
       (DAT_EXTMEM_1af5 < (byte)-cVar3) << 7 < '\0')) goto LAB_CODE_aec9;
  }
  sub_deb5(cVar4);
LAB_CODE_aec9:
  if (DAT_EXTMEM_1af0 == 0) {
    return '\0';
  }
  cVar3 = '\0';
  do {
    pbVar5 = (byte *)CONCAT11('\x1a' - (((0xeU < (byte)(cVar3 * '\x02')) << 7) >> 7),
                              cVar3 * '\x02' - 0xf);
    bVar1 = *pbVar5;
    bVar2 = DAT_EXTMEM_1aee - (((pbVar5[1] < DAT_EXTMEM_1aef) << 7) >> 7);
    if (bVar2 <= bVar1) {
      return bVar1 - bVar2;
    }
    cVar3 = cVar3 + '\x01';
  } while (cVar3 != '\x03');
  return '\x03';
}

