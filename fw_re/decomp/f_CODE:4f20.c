
void FUN_CODE_4f20(char param_1,byte param_2)

{
  undefined1 uVar1;
  char cVar2;
  char cVar3;
  byte bVar4;
  char cVar5;
  byte bVar6;
  
  DAT_EXTMEM_1fc0 = 0;
  if (cCODE001e == '?') {
    cVar2 = '\0';
    cVar3 = 'c';
  }
  else {
    sub_cfdd();
    sub_0e32(0,100);
    cVar2 = BANK0_R6;
    bVar6 = BANK0_R7;
    sub_cfdd();
    sub_0e32(3,0xe8);
    bVar4 = param_2 + bVar6;
    cVar2 = param_1 + (cVar2 - ((CARRY1(param_2,bVar6) << 7) >> 7));
    sub_cfdd();
    sub_0e32(0,10);
    bVar6 = param_2 + bVar4;
    param_1 = param_1 + (cVar2 - ((CARRY1(param_2,bVar4) << 7) >> 7));
    bVar4 = sub_d000();
    cVar3 = (bVar4 - 0x30) + bVar6;
    cVar2 = ((char)bVar4 >> 7) + (-1 - (((0x2f < bVar4) << 7) >> 7)) +
            (param_1 - ((CARRY1(bVar4 - 0x30,bVar6) << 7) >> 7));
  }
  uVar1 = 100;
  sub_0e44(0,cVar2,cVar3);
  cVar2 = BANK0_R5;
  DAT_EXTMEM_1fc1 = uVar1;
  cVar3 = sub_d00a();
  if (cVar3 == '?') {
    DAT_EXTMEM_1fc2 = 99;
  }
  else {
    if (cVar2 == 'J') {
      cVar3 = sub_d011();
      if (cVar3 == 'a') {
        DAT_EXTMEM_1fc2 = 1;
        goto LAB_CODE_5045;
      }
    }
    cVar3 = sub_d00a();
    if (cVar3 == 'F') {
      DAT_EXTMEM_1fc2 = 2;
    }
    else {
      cVar3 = sub_d011();
      if (cVar3 == 'a') {
        cVar5 = sub_d018();
        if (cVar5 == 'r') {
          DAT_EXTMEM_1fc2 = 3;
          goto LAB_CODE_5045;
        }
      }
      if ((cVar2 == 'A') && (cVar3 == 'p')) {
        DAT_EXTMEM_1fc2 = 4;
      }
      else if (cCODE0020 == 'y') {
        DAT_EXTMEM_1fc2 = 5;
      }
      else {
        cVar2 = cCODE0020;
        cVar3 = sub_d011();
        if ((cVar3 == 'u') && (cVar2 == 'n')) {
          DAT_EXTMEM_1fc2 = 6;
        }
        else {
          cVar2 = sub_d011();
          if (cVar2 == 'u') {
            cVar3 = sub_d018();
            if (cVar3 == 'l') {
              DAT_EXTMEM_1fc2 = 7;
              goto LAB_CODE_5045;
            }
          }
          if ((cCODE001e == 'A') && (cVar2 == 'u')) {
            DAT_EXTMEM_1fc2 = 8;
          }
          else {
            cVar3 = sub_d00a();
            if (cVar3 == 'S') {
              DAT_EXTMEM_1fc2 = 9;
            }
            else if (cVar2 == 'O') {
              DAT_EXTMEM_1fc2 = 10;
            }
            else {
              cVar3 = sub_d00a();
              if (cVar3 == 'N') {
                DAT_EXTMEM_1fc2 = 0xb;
              }
              else {
                DAT_EXTMEM_1fc2 = 99;
                if (cVar2 == 'D') {
                  DAT_EXTMEM_1fc2 = 0xc;
                }
              }
            }
          }
        }
      }
    }
  }
LAB_CODE_5045:
  if (cCODE001e == '?') {
    DAT_EXTMEM_1fc3 = 'c';
  }
  else {
    bVar6 = sub_d000();
    if (((bVar6 ^ 0x80) < 0xb0) << 7 < '\0') {
      cVar2 = '\0';
    }
    else {
      cVar2 = (bVar6 - 0x30) * '\n';
    }
    cVar3 = sub_d000();
    DAT_EXTMEM_1fc3 = cVar3 + -0x30 + cVar2;
  }
  sub_eae4();
  sub_eb9c();
  DAT_EXTMEM_1aa6 = 0;
  DAT_EXTMEM_1aa5 = 8;
  sub_7c18(0xa5,0x1a,1);
  sub_c33c(0);
  sub_eb30(1);
  sub_ee8e(7);
  sub_ee91(9);
  sub_0006();
  sub_e78a(0x2a,0,0xff);
  sub_eaf7();
  sub_ecad(0x2a,0,0xff);
  sub_ed82(200);
  sub_ed82(100);
  DAT_INTMEM_4b = 0xf;
  sub_4454();
  thunk_FUN_CODE_ee9a();
  do {
    sub_6eb9();
    cVar2 = ((DAT_INTMEM_2d < 4) << 7) >> 7;
    if ((byte)-cVar2 <= DAT_INTMEM_2c) {
      sub_1b67(DAT_INTMEM_2c + cVar2);
      if ((_1_4 != '\x01') && ((DAT_EXTMEM_f015 >> 4 & 1) != 1)) {
        sub_ee27();
      }
      DAT_INTMEM_2c = 0;
      DAT_INTMEM_2d = 0;
    }
    cVar2 = ((DAT_INTMEM_27 < 10) << 7) >> 7;
    if ((byte)-cVar2 <= DAT_INTMEM_26) {
      sub_bfba(DAT_INTMEM_26 + cVar2);
      DAT_INTMEM_26 = 0;
      DAT_INTMEM_27 = 0;
    }
    sub_b525();
  } while( true );
}

