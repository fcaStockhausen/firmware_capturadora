
char sub_905c(void)

{
  return (char)((ushort)DAT_INTMEM_31 * 4 >> 8) +
         ('\x01' - (((0x45 < (byte)((ushort)DAT_INTMEM_31 * 4)) << 7) >> 7));
}

