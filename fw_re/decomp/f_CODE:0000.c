
void thunk_FUN_CODE_a4eb(void)

{
  char cVar1;
  undefined1 *puVar2;
  byte bVar3;
  byte *pbVar4;
  byte bVar5;
  byte bVar6;
  byte *pbVar7;
  byte *pbVar8;
  
  puVar2 = &DAT_INTMEM_7f;
  do {
    *puVar2 = 0;
    puVar2 = puVar2 + -1;
  } while (puVar2 != (undefined1 *)0x0);
  SP = 0x4b;
  pbVar7 = &DAT_CODE_2aa3;
  while( true ) {
    bVar3 = 1;
    bVar5 = *pbVar7;
    if (bVar5 == 0) break;
    bVar6 = bVar5 & 0x3f;
    pbVar8 = pbVar7 + 1;
    if (bVar6 >> 5 != 0) {
      bVar3 = bVar5 & 0x1f;
      bVar6 = pbVar7[1];
      pbVar8 = pbVar7 + 2;
      if (bVar6 != 0) {
        bVar3 = bVar3 + 1;
      }
    }
    pbVar7 = pbVar8;
    cVar1 = CARRY1(bVar5 & 0xc0,bVar5 & 0xc0) << 7;
    if ((bVar5 & 0x40) == 0) {
      pbVar4 = (byte *)*pbVar7;
      pbVar7 = pbVar7 + 1;
      do {
        bVar3 = *pbVar7;
        pbVar7 = pbVar7 + 1;
        if (cVar1 < '\0') {
          *(byte *)ZEXT12(pbVar4) = bVar3;
        }
        else {
          *pbVar4 = bVar3;
        }
        pbVar4 = pbVar4 + '\x01';
        bVar6 = bVar6 - 1;
      } while (bVar6 != 0);
    }
    else if (cVar1 < '\0') {
      do {
        bVar3 = *pbVar7;
        pbVar7 = pbVar7 + 1;
        pbVar4 = (byte *)((bVar3 & 0x7f) >> 3 | 0x20);
        bVar5 = *(byte *)((ushort)((bVar3 & 7) + 0xc) + 0xa51e);
        if ((char)bVar3 < '\0') {
          bVar5 = bVar5 | *pbVar4;
        }
        else {
          bVar5 = ~bVar5 & *pbVar4;
        }
        *pbVar4 = bVar5;
        bVar6 = bVar6 - 1;
      } while (bVar6 != 0);
    }
    else {
      pbVar8 = *(byte **)pbVar7;
      pbVar7 = pbVar7 + 2;
      do {
        do {
          bVar5 = *pbVar7;
          pbVar7 = pbVar7 + 1;
          *pbVar8 = bVar5;
          pbVar8 = pbVar8 + 1;
          bVar6 = bVar6 - 1;
        } while (bVar6 != 0);
        bVar3 = bVar3 - 1;
      } while (bVar3 != 0);
    }
  }
  FUN_CODE_4f20();
  return;
}

