
char sub_9073(byte param_1)

{
  return (char)((ushort)DAT_INTMEM_31 * (ushort)param_1 >> 8) +
         ('\x01' - (((0x45 < (byte)((ushort)DAT_INTMEM_31 * (ushort)param_1)) << 7) >> 7));
}

