
void sub_81f1(byte param_1,byte param_2)

{
  byte bVar1;
  char cVar2;
  byte bVar3;
  byte bVar4;
  undefined1 uVar5;
  undefined1 *puVar6;
  
  DAT_EXTMEM_1ae5 = '\0';
  DAT_EXTMEM_1ae6 = 0;
  bVar1 = 0;
  DAT_EXTMEM_1ae7 = 2;
  puVar6 = &DAT_EXTMEM_1ae8;
  uVar5 = sub_416e(0,0);
  puVar6[1] = uVar5;
  if (param_1 < 0x12U - (((param_2 < 0x12) << 7) >> 7)) {
    bVar3 = 3;
    cVar2 = '\x03';
    DAT_EXTMEM_1ae9 = 0;
    DAT_EXTMEM_1aea = '\x01';
    DAT_EXTMEM_1aec = 0;
  }
  else if (param_1 < 0x24U - (((param_2 < 0x23) << 7) >> 7)) {
    bVar3 = 2;
    cVar2 = '\x02';
    DAT_EXTMEM_1ae9 = 1;
    DAT_EXTMEM_1aea = '\x02';
    DAT_EXTMEM_1aec = 1;
  }
  else if (param_1 < 0x48U - (((param_2 < 0x44) << 7) >> 7)) {
    bVar3 = 1;
    cVar2 = '\x01';
    DAT_EXTMEM_1aec = 2;
    DAT_EXTMEM_1ae9 = 2;
    DAT_EXTMEM_1aea = '\x02';
  }
  else {
    bVar3 = 0;
    cVar2 = '\0';
    DAT_EXTMEM_1ae9 = 3;
    DAT_EXTMEM_1aea = '\x01';
    DAT_EXTMEM_1aec = 3;
  }
  bVar4 = cVar2 * ' ';
  sub_41b6(0x1ae6,4,DAT_EXTMEM_1ae5 << 5 | (byte)((ushort)bVar3 * 0x80 >> 8),
           (byte)((ushort)bVar3 * 0x80) | bVar4);
  bVar3 = 6;
  sub_d277(param_1,bVar4 | bVar1,BANK0_R2,bVar4 | bVar1,6);
  puVar6 = &DAT_EXTMEM_1ae7;
  sub_41b6(8,DAT_EXTMEM_1aea * '\x02' | (byte)((ushort)DAT_EXTMEM_1aeb * 0x40 >> 8),
           (char)((ushort)DAT_EXTMEM_1aeb * 0x40));
  sub_d277(param_1,bVar3 | puVar6[1],BANK0_R2,bVar3 | puVar6[1],0x10);
  bVar1 = (byte)((ushort)DAT_EXTMEM_1ae9 * 4) | DAT_EXTMEM_1aec;
  sub_d277((char)((ushort)DAT_EXTMEM_1ae9 * 4 >> 8),bVar1,BANK0_R2,bVar1,0x15);
  return;
}

