
void sub_9bd5(byte *param_1,byte param_2)

{
  byte bVar1;
  char cVar2;
  byte bVar3;
  
  bVar3 = param_2 - 0x32;
  cVar2 = -1 - (((0x31 < param_2) << 7) >> 7);
  bVar1 = *param_1;
  sub_0e32(bVar1,-(((char)bVar1 >> 7) - (((0x7f < bVar1) << 7) >> 7)),'\x7f' - bVar1,cVar2,bVar3);
  sub_0e44(0,0x32,cVar2 - (((0xe6 < bVar3) << 7) >> 7),bVar3 + 0x19);
  return;
}

