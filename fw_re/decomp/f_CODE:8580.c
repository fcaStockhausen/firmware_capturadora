
void sub_8580(undefined1 *param_1,undefined1 param_2,char param_3,undefined1 param_4)

{
  if (param_3 == '\x01') {
    *(undefined1 *)CONCAT11(param_2,param_1) = param_4;
    return;
  }
  if (param_3 == '\0') {
    *param_1 = param_4;
    return;
  }
  if (param_3 == -2) {
    *(undefined1 *)ZEXT12(param_1) = param_4;
  }
  return;
}

