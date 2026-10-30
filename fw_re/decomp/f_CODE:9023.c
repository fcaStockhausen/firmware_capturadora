
undefined1 sub_9023(byte param_1)

{
  byte bVar1;
  undefined1 uVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  
  bVar1 = (byte)((ushort)DAT_INTMEM_31 * (ushort)param_1);
  puVar3 = (undefined1 *)
           CONCAT11((char)((ushort)DAT_INTMEM_31 * (ushort)param_1 >> 8) +
                    ('\x01' - (((0xa3 < bVar1) << 7) >> 7)),bVar1 + 0x5c);
  uVar2 = puVar3[1];
  bVar1 = (byte)((ushort)DAT_INTMEM_31 * 4);
  puVar4 = (undefined1 *)
           CONCAT11((char)((ushort)DAT_INTMEM_31 * 4 >> 8) + ('\x01' - (((0xa1 < bVar1) << 7) >> 7))
                    ,bVar1 + 0x5e);
  sub_1465(*puVar4,puVar4[1],*puVar3,uVar2);
  sub_104c(0,0,0,0x80);
  return uVar2;
}

