#include "Loader.h"
#include "Intel.h"
#include "generator.h"

void VAR_WORD_(const char *name, ushort number) {
  LAB_(name);
  DB_(((uchar *)&number)[0]);
  DB_(((uchar *)&number)[1]);
}
void VAR_BYTE_(const char *name, uchar number) {
  LAB_(name);
  DB_(number);
}

void Tr_Stop() {
  LAB_("ZZZ");
  NOP_();
  jmp_byte("ZZZ");
}
void MyPrint(const char *text) {

  FUN_("MyPrint");
  NOP_();
  movw("DI", ADR_("lText"));
  call_("PRINT16");
  jmp_byte("NEX");
  LAB_("lText");
  STR_(text);
  LAB_("NEX");
  NOP_();
  FUN_("MyPrint");
}
void IncludeMyPrint() {

  // =============================================
  // ������������ ������ ������ � ������� � 16 ������ ������
  // � DS:DI ������ ���� ����� ������

  FUN_("PRINT16"); // ��������� ����� �������
  movw("AX", 0xB800); // mov ax,B800  �����������
  mov_ES_AX();     // mov es,ax    � ES

  mov_AX_A_(ADR_("CURR_Y"));
  movb("DL", 160);
  mul_DL_();
  mov_DX_A_(ADR_("CURR_X"));
  shl_DL_1_();
  add_AX_DX_();
  mov_SI_AX_();

  LAB_("Cikl");
  mov_AL_A_DI();    // mov al,[di]
  test_AL_AL_();    // test al,al
  jz_byte("EX");    // jz EX
  mov_A_ES_SI_AL(); // mov [ES:DI],AL ������� ������ �� �����
  inc_SI_();        // inc Si
  movb("AL", 0x0F);
  mov_A_ES_SI_AL(); // mov [ES:DI],AL ������� �������� ������ �� �����
  inc_SI_();        // inc Si
  inc_DI_();        // inc di
  jmp_byte("Cikl"); // jmp cikl

  LAB_("EX");

  mov_DX_A_(ADR_("CURR_Y")); // ������� �� ���� ������
  inc_DX_();
  mov_A_DX_(ADR_("CURR_Y"));
  movw("DX", 0);
  mov_A_DX_(ADR_("CURR_X"));

  ret_();
  VAR_WORD_("CURR_X", 0);
  VAR_WORD_("CURR_Y", 0);
}
void Loader() {

  SetPlatform(PL_I16); // �������� ���������
  ORG_(0x7C00); // ������������� ����� ������ ���������
  FUN_("");     // ������������� ���������� ������� ��������� ��� �����
  // ������������� ���������� �������� ===========
  xor_AX_AX(); // �������� ���������� �������� AX
  mov_SS_AX(); // ������������� ������� ����� 0
  mov_DS_AX(); // ������������� ������� ������ 0
  mov_ES_AX(); // ������������� ������� ��� ��� ��� �� ����� �� �����  0
  movw("SP", 0xFFFF);
  // =============================================

  // =============================================
  // �������� ����� �����
  movb("AH", 0); // ������������ ����������  ����� ������
  movb("AL", 3); // �����    80x25    16/8           CGA,EGA  b800  Comp,RGB,Enhanced
  int_(0x10); // ���������� 10h

  // �������� ��������
  movb("AH", 5); // ������������ ������ �������� ����� ��������
  movb("AL", 0); // ����� �������� 0
  int_(0x10); // ���������� 10h

  MyPrint(__DATE__" "__TIME__);
  MyPrint("Start Ok");

  // ������ ������
  movb("AH", 2);  // ������������ ��������� �������
  movb("BH", 0);  // ����� ��������
  movb("DH", 25); // ����� ������ ��������� � 25 ����� ��������� ������
  movb("DL", 0);  // �������
  int_(0x10);  // ���������� 10h

  // =============================================
  MyPrint("Start load 18 sectors");

  // �������� ���������� ����� ��������� � �����
  /* �������� http://www.codenet.ru/progr/dos/int_0012.php
  

  02H ������ �������
   ����: DL = ����� ����� (0=���� A...; 80H=��.���� 0; 81H=��.���� 1)
         DH = ����� ������� ������/������
         CH = ����� ������� (��������)(0-n) =�
         CL = ����� ������� (1-n) ===========�== ��. ��������� ����.
         AL = ����� �������� (� ����� �� ������ ��� ���� �������)
         ES:BX => ����� ������ ���������� ���������
         0:0078 => ������� ���������� ������� (��� ������ ������)
         0:0104 => ������� ���������� ��.����� (��� ������� ������)
  

  */

  movw("AX", 0);      // �� ����� ������ � ES ��������� ���� ����� ���
  mov_ES_AX();       // ����� �������� ���� ��������� ���
  movw("BX", 0x7E00); // ����� ������ ��������

  movb("DL", 0);  // ������ � ����� �
  movb("DH", 0);  // ����� ������� ������/������
  movb("CH", 0);  // ����� ������� (��������)(0-n)
  movb("CL", 2);  // ����� �������
  movb("AL", 18); // ���������� �������� ��������
  movb("AH", 2);  // ����� ������������ ���������� 13h
  int_(0x13);  // ���������� ������ � ������

  MyPrint("End load 18 sectors");

  Tr_Stop();

  IncludeMyPrint();

  // ====================================
  // ������ ������ ��� ���������

  // STL_("Hello world")   ;
  // STL_("Start Ok")      ;
  // STL_("Start load 18 sectors")      ;
  // STL_("End load 18 sectors")      ;

  // ====================================
  Program[510] = 0x55;
  Program[511] = 0xaa;
}
