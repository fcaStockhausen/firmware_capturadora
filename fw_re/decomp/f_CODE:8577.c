
void sub_8577(char *param_1,byte param_2,char param_3,char param_4,undefined1 param_5)

{
  undefined1 *puVar1;
  
  puVar1 = (undefined1 *)(param_1[1] + param_2);
  if (param_4 == '\x01') {
    *(undefined1 *)CONCAT11(param_3 + (*param_1 - ((CARRY1(param_1[1],param_2) << 7) >> 7)),puVar1)
         = param_5;
    return;
  }
  if (param_4 == '\0') {
    *puVar1 = param_5;
    return;
  }
  if (param_4 == -2) {
    *(undefined1 *)ZEXT12(puVar1) = param_5;
  }
  return;
}

