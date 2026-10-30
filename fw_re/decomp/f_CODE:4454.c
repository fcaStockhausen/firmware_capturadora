
void sub_4454(byte param_1)

{
  char cVar1;
  char cVar2;
  byte bVar3;
  byte bVar4;
  
  sub_3371(0x1c06);
  sub_3371(0x1c0c);
  sub_3371(0x1c0a);
  sub_3371(0x1c08);
  sub_a601(1);
  sub_585f(0x61,0xa8,1);
  sub_da22(1);
  DAT_EXTMEM_f005 = DAT_EXTMEM_f005 & 0xbf;
  if ((DAT_EXTMEM_1fd4 != 0xff) || (DAT_EXTMEM_1fd5 != -1)) {
    DAT_EXTMEM_1069 = DAT_EXTMEM_1fd5;
    DAT_EXTMEM_106a = DAT_EXTMEM_1fd4;
    DAT_EXTMEM_1057 = DAT_EXTMEM_1fd5;
    DAT_EXTMEM_1058 = DAT_EXTMEM_1fd4;
    param_1 = DAT_EXTMEM_1fd4;
  }
  cVar2 = (DAT_EXTMEM_1fd6 != 0xff) << 7;
  if ((DAT_EXTMEM_1fd6 != 0xff) || (DAT_EXTMEM_1fd7 != -1)) {
    DAT_EXTMEM_106b = DAT_EXTMEM_1fd7;
    DAT_EXTMEM_106c = DAT_EXTMEM_1fd6;
    DAT_EXTMEM_1059 = DAT_EXTMEM_1fd7;
    DAT_EXTMEM_105a = DAT_EXTMEM_1fd6;
    param_1 = DAT_EXTMEM_1fd6;
  }
  if (DAT_EXTMEM_1fe0 == 0xff) {
    DAT_EXTMEM_1aa7 = 0;
    while (sub_3223(0x1073), cVar2 < '\0') {
      cVar1 = '\x10' - (((0x8c < param_1) << 7) >> 7);
      cVar2 = '\0';
      sub_3154(CONCAT11(cVar1,param_1 + 10),*(undefined1 *)CONCAT11(cVar1,param_1 + 0x73));
    }
    DAT_EXTMEM_1aa7 = 0;
    while (sub_3223(0x1089), cVar2 < '\0') {
      cVar1 = '\x10' - (((0x76 < param_1) << 7) >> 7);
      cVar2 = '\0';
      sub_3154(CONCAT11(cVar1,param_1 + 0x4b),*(undefined1 *)CONCAT11(cVar1,param_1 + 0x89));
    }
  }
  else {
    DAT_EXTMEM_1aa7 = 1;
    while( true ) {
      cVar2 = (DAT_EXTMEM_1aa7 < DAT_EXTMEM_1fe0) << 7;
      if (DAT_EXTMEM_1aa7 >= DAT_EXTMEM_1fe0) break;
      cVar1 = '\x1f' - (((0x1f < DAT_EXTMEM_1aa7) << 7) >> 7);
      cVar2 = *(char *)CONCAT11(cVar1,DAT_EXTMEM_1aa7 - 0x20);
      param_1 = DAT_EXTMEM_1aa7;
      bVar3 = sub_339f(CONCAT11(cVar1,DAT_EXTMEM_1aa7 * '\x02' + '\n'));
      cVar1 = '$' - (((0xf4 < bVar3) << 7) >> 7);
      *(undefined1 *)CONCAT11(cVar1,bVar3 + 0xb) = 0;
      bVar3 = sub_33ab(CONCAT11(cVar1,param_1 - 0x20));
      *(byte *)CONCAT11('&' - (((0xb4 < bVar3) << 7) >> 7),bVar3 + 0x4b) = param_1;
      sub_3157(0,CONCAT11('&' - (((0xb3U < (byte)(cVar2 * '\x02')) << 7) >> 7),cVar2 * '\x02' + 0x4c
                         ));
    }
    bVar3 = DAT_EXTMEM_1fe0;
    sub_33f1(DAT_EXTMEM_1aa7 - DAT_EXTMEM_1fe0,0x240a);
    DAT_EXTMEM_264c = 3;
    DAT_EXTMEM_264b = bVar3;
  }
  if (DAT_EXTMEM_1ff0 == 0xff) {
    DAT_EXTMEM_1aa7 = 0;
    while (sub_3223(0x109f), cVar2 < '\0') {
      cVar1 = '\x10' - (((0x60 < param_1) << 7) >> 7);
      cVar2 = '\0';
      sub_3154(CONCAT11(cVar1,param_1 + 0x14),*(undefined1 *)CONCAT11(cVar1,param_1 + 0x9f));
    }
    DAT_EXTMEM_1aa7 = 0;
    while (sub_3223(0x10df), cVar2 < '\0') {
      cVar1 = '\x10' - (((0x20 < param_1) << 7) >> 7);
      cVar2 = '\0';
      sub_3154(CONCAT11(cVar1,param_1 + 0x54),*(undefined1 *)CONCAT11(cVar1,param_1 - 0x21));
    }
  }
  else {
    DAT_EXTMEM_1aa7 = 1;
    while (DAT_EXTMEM_1aa7 < DAT_EXTMEM_1ff0) {
      cVar1 = '\x1f' - (((0xf < DAT_EXTMEM_1aa7) << 7) >> 7);
      cVar2 = *(char *)CONCAT11(cVar1,DAT_EXTMEM_1aa7 - 0x10);
      bVar3 = DAT_EXTMEM_1aa7;
      bVar4 = sub_339f(CONCAT11(cVar1,DAT_EXTMEM_1aa7 * '\x02' + '\x14'));
      cVar1 = ' ' - (((0xea < bVar4) << 7) >> 7);
      *(undefined1 *)CONCAT11(cVar1,bVar4 + 0x15) = 0;
      bVar4 = sub_33ab(CONCAT11(cVar1,bVar3 - 0x10));
      *(byte *)CONCAT11(' ' - (((0xab < bVar4) << 7) >> 7),bVar4 + 0x54) = bVar3;
      sub_3157(0,CONCAT11(' ' - (((0xaaU < (byte)(cVar2 * '\x02')) << 7) >> 7),cVar2 * '\x02' + 0x55
                         ));
    }
    bVar3 = DAT_EXTMEM_1ff0;
    sub_33f1(DAT_EXTMEM_1aa7 - DAT_EXTMEM_1ff0,0x2014);
    DAT_EXTMEM_2055 = 3;
    DAT_EXTMEM_2054 = bVar3;
  }
  DAT_EXTMEM_f01f = DAT_EXTMEM_f01f & 0x6f;
  bVar3 = P3;
  P3 = bVar3 | 0x3c;
  bVar3 = IEN1;
  IEN1 = bVar3 | 0x3c;
  _2_6 = 0;
  _2_5 = 0;
  DAT_EXTMEM_f00b = DAT_EXTMEM_f00b | 3;
  sub_e036();
  DAT_EXTMEM_f016 = DAT_EXTMEM_f016 & 0xbf;
  sub_000e();
  EX0 = 1;
  return;
}

