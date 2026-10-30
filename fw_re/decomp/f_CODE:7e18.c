
void sub_7e18(void)

{
  char cVar1;
  byte bVar2;
  char cVar3;
  char cVar4;
  undefined1 uVar5;
  short sVar6;
  char *pcVar7;
  undefined1 *puVar8;
  
  cVar3 = ' ';
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  DAT_EXTMEM_f820 = 1;
  sub_ee6b();
  cVar1 = sub_90aa();
  if (cVar1 == '\x05') {
    bVar2 = (byte)((ushort)DAT_INTMEM_31 * 4);
    cVar3 = bVar2 + 0x5e;
    cVar4 = (char)((ushort)DAT_INTMEM_31 * 4 >> 8) + ('\x01' - (((0xa1 < bVar2) << 7) >> 7));
  }
  else {
    cVar4 = sub_9073();
  }
  DAT_EXTMEM_f804 = *(undefined1 *)CONCAT11(cVar4,cVar3);
  DAT_EXTMEM_f805 = ((undefined1 *)CONCAT11(cVar4,cVar3))[1];
  DAT_EXTMEM_f806 = 1;
  sub_90a2(0xe2);
  cVar3 = '\x04';
  if (cVar1 == '\x05') {
    sub_9023();
    sub_907f();
    sub_9023();
    bVar2 = sub_90bb();
    cVar1 = bVar2 + 0x5c;
    cVar3 = cVar3 + ('\x01' - (((0xa3 < bVar2) << 7) >> 7));
  }
  else {
    sub_905c();
    sub_9045();
    sub_907f();
    sub_905c();
    sub_9045();
    bVar2 = sub_90bb();
    cVar1 = bVar2 + 0xb8;
    cVar3 = cVar3 + ('\x01' - (((0x47 < bVar2) << 7) >> 7));
  }
  DAT_EXTMEM_f80c = *(undefined1 *)CONCAT11(cVar3,cVar1);
  DAT_EXTMEM_f80d = ((undefined1 *)CONCAT11(cVar3,cVar1))[1];
  DAT_EXTMEM_f80e = 0;
  sVar6 = -0x7f1;
  sub_90a3(1);
  *(undefined1 *)(sVar6 + 1) = 0x21;
  sVar6 = sVar6 + 2;
  sub_90a3(0x10);
  sub_909c();
  cVar1 = sub_909c();
  *(char *)(sVar6 + 1) = cVar1;
  pcVar7 = (char *)(sVar6 + 2);
  *pcVar7 = cVar1 + '\x01';
  cVar1 = sub_90aa();
  uVar5 = (undefined1)((ushort)pcVar7 >> 8);
  if (cVar1 == '\x05') {
    cVar1 = (char)((ushort)DAT_INTMEM_31 * 4 >> 8);
    sub_90c7(CONCAT11(uVar5,(char)((ushort)DAT_INTMEM_31 * 4) + '\\'));
    bVar2 = sub_90bf();
    cVar3 = bVar2 + 0x5e;
    cVar1 = cVar1 + ('\x01' - (((0xa1 < bVar2) << 7) >> 7));
  }
  else {
    bVar2 = (byte)((ushort)DAT_INTMEM_31 * 4);
    puVar8 = (undefined1 *)CONCAT11(uVar5,bVar2 + 0xb8);
    uVar5 = sub_90c7((char)((ushort)DAT_INTMEM_31 * 4 >> 8) +
                     ('\x01' - (((0x47 < bVar2) << 7) >> 7)));
    *puVar8 = uVar5;
    cVar1 = sub_9070();
    cVar3 = (char)puVar8;
  }
  DAT_EXTMEM_f824 = *(undefined1 *)CONCAT11(cVar1,cVar3);
  DAT_EXTMEM_f823 = ((undefined1 *)CONCAT11(cVar1,cVar3))[1];
  FUN_CODE_ee5f();
  return;
}

