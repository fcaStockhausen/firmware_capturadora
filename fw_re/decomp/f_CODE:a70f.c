
void FUN_CODE_a70f(undefined1 *param_1,char param_2)

{
  byte bVar1;
  char cVar2;
  undefined1 *puVar3;
  char *pcVar4;
  
  DAT_EXTMEM_12a4 = 1;
  if (DAT_EXTMEM_11a0 != '\0') {
    sub_125f(0x1a7e);
    nop();
    nop();
    nop();
    nop();
    puVar3 = &LAB_CODE_1a82;
    sub_125f();
    nop();
    nop();
    nop();
    *param_1 = 0x12;
    func_0x7612();
    bVar1 = func_0x76e4();
                    /* WARNING: Could not recover jumptable at 0x1275. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*(code *)(puVar3 + bVar1))();
    return;
  }
  sub_125f(0x1a7e);
  nop();
  nop();
  nop();
  nop();
  sub_125f(&LAB_CODE_1a82);
  nop();
  nop();
  nop();
  param_2 = param_2 + '\x01';
  sub_6d90(param_2);
  sub_a78c();
  sub_125f(0x1a7e);
  nop();
  nop();
  pcVar4 = &DAT_EXTMEM_1a82;
  sub_125f(0);
  nop();
  nop();
  nop();
  cVar2 = sub_6d90(param_2 + '\x01');
  *pcVar4 = cVar2 + '\x01';
  sub_54ce(7);
  sub_8910(7);
  DAT_EXTMEM_f120 = 0x89;
  return;
}

