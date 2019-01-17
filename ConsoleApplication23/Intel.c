#include "intel.h"
#include "generator.h"
// Команды специфичные только для INTEL ===============

void NOP_() {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0x90;
  } else if (Platform == PL_I32) { // Платформа 32бит 80386
    Program[PC++] = 0x90;
  } else if (Platform == PL_I64) { // Платформа 64 бит
    Program[PC++] = 0x90;
  } else
    ERR(" ERR NOP_ ");
}
void cli() {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0xFA;
  } else if (Platform == PL_I32) { // Платформа 32бит 80386
    Program[PC++] = 0xFA;
  } else if (Platform == PL_I64) { // Платформа 64 бит
    Program[PC++] = 0xFA;
  } else
    ERR(" ERR cli ");
}

void xor_EAX_EAX() {
  if (Platform == PL_I32) { // Платформа 32бит 80386
    Program[PC++] = 0x66;
    Program[PC++] = 0x31;
    Program[PC++] = 0xC0;
  } else if (Platform == PL_I64) { // Платформа 64 бит
    Program[PC++] = 0x66;
    Program[PC++] = 0x31;
    Program[PC++] = 0xC0;
  } else
    ERR("xor_EAX_EAX");
}

void inc_DI_() {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0x47;
  } else
    ERR("inc_DI_");
}
void inc_SI_() {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0x46;
  } else
    ERR("inc_SI_");
}
void test_AL_AL_() {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0x84;
    Program[PC++] = 0xC0;
  } else
    ERR("test_AL_AL");
}
void test_AX_AX_() {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0x85;
    Program[PC++] = 0xC0;
  } else
    ERR("test_AX_AX");
}
void xor_AX_AX() {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0x33;
    Program[PC++] = 0xC0;
  } else
    ERR("xor_AX_AX");
}
void mov_CS_AX() {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    ERR("mov_CS_AX");
  } else if (Platform == PL_I32) { // Платформа 32бит 80386
    Program[PC++] = 0x8E;
    Program[PC++] = 0xC8;
  } else if (Platform == PL_I64) { // Платформа 64 бит
    Program[PC++] = 0x8E;
    Program[PC++] = 0xC8;
  } else
    ERR("mov_CS_AX");
}
void mov_DS_AX() {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0x8E;
    Program[PC++] = 0xD8;
  } else if (Platform == PL_I32) { // Платформа 32бит 80386
    Program[PC++] = 0x8E;
    Program[PC++] = 0xD8;
  } else if (Platform == PL_I64) { // Платформа 64 бит
    Program[PC++] = 0x8E;
    Program[PC++] = 0xD8;
  } else
    ERR("Ошибка такой команды в выбраной платформе не сущестукет ");
}
void mov_SS_AX() {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0x8E;
    Program[PC++] = 0xD0;
  } else if (Platform == PL_I32) { // Платформа 32бит 80386
    Program[PC++] = 0x8E;
    Program[PC++] = 0xD0;
  } else if (Platform == PL_I64) { // Платформа 64 бит
    Program[PC++] = 0x8E;
    Program[PC++] = 0xD0;
  } else
    ERR("Ошибка такой команды в выбраной платформе не сущестукет ");
}
void mov_ES_AX() {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0x8E;
    Program[PC++] = 0xC0;
  } else if (Platform == PL_I32) { // Платформа 32бит 80386
    Program[PC++] = 0x8E;
    Program[PC++] = 0xC0;
  } else if (Platform == PL_I64) { // Платформа 64 бит
    Program[PC++] = 0x8E;
    Program[PC++] = 0xC0;
  } else
    ERR("Ошибка такой команды в выбраной платформе не сущестукет ");
}

void int_(uchar iNom) {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0xCD;
    Program[PC++] = iNom;
  } else if (Platform == PL_I32) { // Платформа 32бит 80386
    Program[PC++] = 0xCD;
    Program[PC++] = iNom;
  } else if (Platform == PL_I64) { // Платформа 64 бит
    Program[PC++] = 0xCD;
    Program[PC++] = iNom;
  } else
    ERR("Ошибка такой команды в выбраной платформе не сущестукет ");
}
void mov_SP_(ushort iNom) {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0xBC;
    Program[PC++] = ((uchar *)&iNom)[0];
    Program[PC++] = ((uchar *)&iNom)[1];
  } else
    ERR("mov_SP_");
}
void mov_ESP_(uint iNom) {
  if (Platform == PL_I32) { // Платформа 32бит 80386
    Program[PC++] = 0xBC;
    Program[PC++] = ((uchar *)&iNom)[0];
    Program[PC++] = ((uchar *)&iNom)[1];
    Program[PC++] = ((uchar *)&iNom)[2];
    Program[PC++] = ((uchar *)&iNom)[3];
  } else if (Platform == PL_I64) { // Платформа 64 бит
    Program[PC++] = 0xBC;
    Program[PC++] = ((uchar *)&iNom)[0];
    Program[PC++] = ((uchar *)&iNom)[1];
    Program[PC++] = ((uchar *)&iNom)[2];
    Program[PC++] = ((uchar *)&iNom)[3];
  } else
    ERR("mov_ESP_");
}

void mov_SI_(ushort iNom) {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0xBE;
    Program[PC++] = ((uchar *)&iNom)[0];
    Program[PC++] = ((uchar *)&iNom)[1];
  } else
    ERR("mov_SI_");
}
void mov_DI_(ushort iNom) {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0xBF;
    Program[PC++] = ((uchar *)&iNom)[0];
    Program[PC++] = ((uchar *)&iNom)[1];
  } else
    ERR("mov_DI_");
}
void mov_EDI_(uint iNom) {
  if (Platform == PL_I32) { // Платформа 32бит 80386
    Program[PC++] = 0xBF;
    Program[PC++] = ((uchar *)&iNom)[0];
    Program[PC++] = ((uchar *)&iNom)[1];
    Program[PC++] = ((uchar *)&iNom)[2];
    Program[PC++] = ((uchar *)&iNom)[3];
  } else if (Platform == PL_I64) { // Платформа 64 бит
    Program[PC++] = 0xBF;
    Program[PC++] = ((uchar *)&iNom)[0];
    Program[PC++] = ((uchar *)&iNom)[1];
    Program[PC++] = ((uchar *)&iNom)[2];
    Program[PC++] = ((uchar *)&iNom)[3];
  } else
    ERR("mov_EDI_");
}
void mov_BP_(ushort iNom) {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0xBD;
    Program[PC++] = ((uchar *)&iNom)[0];
    Program[PC++] = ((uchar *)&iNom)[1];
  } else if (Platform == PL_I32) { // Платформа 32бит 80386
    Program[PC++] = 0x66;
    Program[PC++] = 0xBD;
    Program[PC++] = ((uchar *)&iNom)[0];
    Program[PC++] = ((uchar *)&iNom)[1];
  } else if (Platform == PL_I64) { // Платформа 64 бит
    Program[PC++] = 0x66;
    Program[PC++] = 0xBD;
    Program[PC++] = ((uchar *)&iNom)[0];
    Program[PC++] = ((uchar *)&iNom)[1];
  } else
    ERR("mov_BP_");
}

void mov_AX_(ushort iNom) {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0xB8;
    Program[PC++] = ((uchar *)&iNom)[0];
    Program[PC++] = ((uchar *)&iNom)[1];
  } else if (Platform == PL_I32) { // Платформа 32бит 80386
    Program[PC++] = 0x66;
    Program[PC++] = 0xB8;
    Program[PC++] = ((uchar *)&iNom)[0];
    Program[PC++] = ((uchar *)&iNom)[1];
  } else if (Platform == PL_I64) { // Платформа 64 бит
    Program[PC++] = 0x66;
    Program[PC++] = 0xB8;
    Program[PC++] = ((uchar *)&iNom)[0];
    Program[PC++] = ((uchar *)&iNom)[1];
  } else
    ERR("Ошибка такой команды в выбраной платформе не сущестукет ");
}
void mov_BX_(ushort iNom) {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0xBB;
    Program[PC++] = ((uchar *)&iNom)[0];
    Program[PC++] = ((uchar *)&iNom)[1];
  } else if (Platform == PL_I32) { // Платформа 32бит 80386
    Program[PC++] = 0x66;
    Program[PC++] = 0xBB;
    Program[PC++] = ((uchar *)&iNom)[0];
    Program[PC++] = ((uchar *)&iNom)[1];
  } else if (Platform == PL_I64) { // Платформа 64 бит
    Program[PC++] = 0x66;
    Program[PC++] = 0xBB;
    Program[PC++] = ((uchar *)&iNom)[0];
    Program[PC++] = ((uchar *)&iNom)[1];
  } else
    ERR("Ошибка такой команды в выбраной платформе не сущестукет ");
}
void mov_CX_(ushort iNom) {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0xB9;
    Program[PC++] = ((uchar *)&iNom)[0];
    Program[PC++] = ((uchar *)&iNom)[1];
  } else if (Platform == PL_I32) { // Платформа 32бит 80386
    Program[PC++] = 0x66;
    Program[PC++] = 0xB9;
    Program[PC++] = ((uchar *)&iNom)[0];
    Program[PC++] = ((uchar *)&iNom)[1];
  } else if (Platform == PL_I64) { // Платформа 64 бит
    Program[PC++] = 0x66;
    Program[PC++] = 0xB9;
    Program[PC++] = ((uchar *)&iNom)[0];
    Program[PC++] = ((uchar *)&iNom)[1];
  } else
    ERR("mov_CX_");
}

void mul_DL_() {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0xF6;
    Program[PC++] = 0xE2;
  } else
    ERR("mul_AL_");
}
void inc_DX_() {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0x42;
  } else
    ERR("inc_DX_");
}
void mov_SI_AX_() {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0x8B;
    Program[PC++] = 0xF0;
  } else
    ERR("mov_SI_AX_");
}
void add_AX_DX_() {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0x03;
    Program[PC++] = 0xC2;
  } else
    ERR("add_AX_DX_");
}
void shl_DL_1_() {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0xD0;
    Program[PC++] = 0xE2;
  } else
    ERR("shl_DL_1_");
}
void mov_A_DX_(ushort iNom) {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0x89;
    Program[PC++] = 0x16;
    Program[PC++] = ((uchar *)&iNom)[0];
    Program[PC++] = ((uchar *)&iNom)[1];
  } else
    ERR("mov_A_DX_");
}
void mov_DX_(ushort iNom) {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0xBA;
    Program[PC++] = ((uchar *)&iNom)[0];
    Program[PC++] = ((uchar *)&iNom)[1];
  } else
    ERR("mov_DX_");
}
void mov_DX_A_(ushort iNom) {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0x8B;
    Program[PC++] = 0x16;
    Program[PC++] = ((uchar *)&iNom)[0];
    Program[PC++] = ((uchar *)&iNom)[1];
  } else
    ERR("mov_DX_A_");
}
void mov_AX_A_(ushort iNom) {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0xA1;
    Program[PC++] = ((uchar *)&iNom)[0];
    Program[PC++] = ((uchar *)&iNom)[1];
  } else
    ERR("mov_AX_A_");
}
void mov_SI_A_(ushort iNom) {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0x8B;
    Program[PC++] = 0x36;
    Program[PC++] = ((uchar *)&iNom)[0];
    Program[PC++] = ((uchar *)&iNom)[1];
  } else
    ERR("mov_SI_A");
}

void mov_AL_(uchar iNom) {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0xB0;
    Program[PC++] = iNom;
  } else if (Platform == PL_I32) { // Платформа 32бит 80386
    Program[PC++] = 0xB0;
    Program[PC++] = iNom;
  } else if (Platform == PL_I64) { // Платформа 64 бит
    Program[PC++] = 0xB0;
    Program[PC++] = iNom;
  } else
    ERR("mov_AL_");
}
void mov_AH_(uchar iNom) {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0xB4;
    Program[PC++] = iNom;
  } else if (Platform == PL_I32) { // Платформа 32бит 80386
    Program[PC++] = 0xB4;
    Program[PC++] = iNom;
  } else if (Platform == PL_I64) { // Платформа 64 бит
    Program[PC++] = 0xB4;
    Program[PC++] = iNom;
  } else
    ERR("mov_AH_");
}
void mov_BL_(uchar iNom) {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0xB3;
    Program[PC++] = iNom;
  } else if (Platform == PL_I32) { // Платформа 32бит 80386
    Program[PC++] = 0xB3;
    Program[PC++] = iNom;
  } else if (Platform == PL_I64) { // Платформа 64 бит
    Program[PC++] = 0xB3;
    Program[PC++] = iNom;
  } else
    ERR("Ошибка такой команды в выбраной платформе не сущестукет ");
}
void mov_BH_(uchar iNom) {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0xB7;
    Program[PC++] = iNom;
  } else if (Platform == PL_I32) { // Платформа 32бит 80386
    Program[PC++] = 0xB7;
    Program[PC++] = iNom;
  } else if (Platform == PL_I64) { // Платформа 64 бит
    Program[PC++] = 0xB7;
    Program[PC++] = iNom;
  } else
    ERR("Ошибка такой команды в выбраной платформе не сущестукет ");
}
void mov_DH_(uchar iNom) {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0xB6;
    Program[PC++] = iNom;
  } else if (Platform == PL_I32) { // Платформа 32бит 80386
    Program[PC++] = 0xB6;
    Program[PC++] = iNom;
  } else if (Platform == PL_I64) { // Платформа 64 бит
    Program[PC++] = 0xB6;
    Program[PC++] = iNom;
  } else
    ERR("Ошибка такой команды в выбраной платформе не сущестукет ");
}
void mov_DL_(uchar iNom) {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0xB2;
    Program[PC++] = iNom;
  } else if (Platform == PL_I32) { // Платформа 32бит 80386
    Program[PC++] = 0xB2;
    Program[PC++] = iNom;
  } else if (Platform == PL_I64) { // Платформа 64 бит
    Program[PC++] = 0xB2;
    Program[PC++] = iNom;
  } else
    ERR("Ошибка такой команды в выбраной платформе не сущестукет ");
}
void mov_CL_(uchar iNom) {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0xB1;
    Program[PC++] = iNom;
  } else if (Platform == PL_I32) { // Платформа 32бит 80386
    Program[PC++] = 0xB1;
    Program[PC++] = iNom;
  } else if (Platform == PL_I64) { // Платформа 64 бит
    Program[PC++] = 0xB1;
    Program[PC++] = iNom;
  } else
    ERR("Ошибка такой команды в выбраной платформе не сущестукет ");
}
void mov_CH_(uchar iNom) {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0xB5;
    Program[PC++] = iNom;
  } else if (Platform == PL_I32) { // Платформа 32бит 80386
    Program[PC++] = 0xB5;
    Program[PC++] = iNom;
  } else if (Platform == PL_I64) { // Платформа 64 бит
    Program[PC++] = 0xB5;
    Program[PC++] = iNom;
  } else
    ERR("mov_CH_");
}

void mov_A_DI_AL() {
  //  mov [di],al
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0x88;
    Program[PC++] = 0x05;
  } else if (Platform == PL_I32) { // Платформа 32бит 80386
    Program[PC++] = 0x67;
    Program[PC++] = 0x88;
    Program[PC++] = 0x05;
  } else
    ERR("mov_A_DI_AL");
}
void mov_A_SI_AL() {
  //  mov [di],al
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0x88;
    Program[PC++] = 0x04;
  } else if (Platform == PL_I32) { // Платформа 32бит 80386
    Program[PC++] = 0x67;
    Program[PC++] = 0x88;
    Program[PC++] = 0x04;
  } else
    ERR("mov_A_SI_AL");
}
void mov_AL_A_DI() {
  //  mov al,[di]
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0x8A;
    Program[PC++] = 0x05;
  } else if (Platform == PL_I32) { // Платформа 32бит 80386
    Program[PC++] = 0x67;
    Program[PC++] = 0x8A;
    Program[PC++] = 0x05;
  } else
    ERR("mov_AL_A_DI");
}
void mov_AL_A_SI() {
  //  mov al,[di]
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0x8A;
    Program[PC++] = 0x04;
  } else if (Platform == PL_I32) { // Платформа 32бит 80386
    Program[PC++] = 0x67;
    Program[PC++] = 0x8A;
    Program[PC++] = 0x04;
  } else
    ERR("mov_AL_A_SI");
}

void mov_A_DI_AX() {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0x89;
    Program[PC++] = 0x05;
  } else if (Platform == PL_I32) { // Платформа 32 бит 80386
    Program[PC++] = 0x67;
    Program[PC++] = 0x66;
    Program[PC++] = 0x89;
    Program[PC++] = 0x05;
  } else
    ERR("mov_A_DI_AX");
}

void mov_A_ES_DI_AL() {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0x26;
    Program[PC++] = 0x88;
    Program[PC++] = 0x05;
  } else if (Platform == PL_I32) { // Платформа 32 бит 80386
    Program[PC++] = 0x26;
    Program[PC++] = 0x67;
    Program[PC++] = 0x88;
    Program[PC++] = 0x05;
  } else
    ERR("mov_A_ES_DI_AL");
}
void mov_A_ES_SI_AL() {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0x26;
    Program[PC++] = 0x88;
    Program[PC++] = 0x04;
  } else if (Platform == PL_I32) { // Платформа 32 бит 80386
    Program[PC++] = 0x26;
    Program[PC++] = 0x67;
    Program[PC++] = 0x88;
    Program[PC++] = 0x04;
  } else
    ERR("mov_A_ES_SI_AL");
}

void jmp_byte(const char *iStr) {

  uint iNom = ADR_(iStr);

  if (Platform == PL_I16) { // Платформа 16 бит 8086
    char lAdr = iNom - (PC + BaseAddres + 2);
    Program[PC++] = 0xEB;
    Program[PC++] = (char)(lAdr);
  } else if (Platform == PL_I32) { // Платформа 32бит 80386
    char lAdr = iNom - (PC + BaseAddres + 2);
    Program[PC++] = 0xEB;
    Program[PC++] = (char)(lAdr);
  } else if (Platform == PL_I64) { // Платформа 64 бит
    char lAdr = iNom - (PC + BaseAddres + 2);
    Program[PC++] = 0xEB;
    Program[PC++] = (char)(lAdr);
  } else
    ERR("jmp_byte");
}
void jz_byte(const char *iStr) {

  uint iNom = ADR_(iStr);

  if (Platform == PL_I16) { // Платформа 16 бит 8086
    char lAdr = iNom - (PC + BaseAddres + 2);
    Program[PC++] = 0x74;
    Program[PC++] = (char)(lAdr);
  } else if (Platform == PL_I32) { // Платформа 32бит 80386
    char lAdr = iNom - (PC + BaseAddres + 2);
    Program[PC++] = 0x74;
    Program[PC++] = (char)(lAdr);
  } else if (Platform == PL_I64) { // Платформа 64 бит
    char lAdr = iNom - (PC + BaseAddres + 2);
    Program[PC++] = 0x74;
    Program[PC++] = (char)(lAdr);
  } else
    ERR("jz_byte");
}
void call_(const char *iStr) {

  uint iNom = ADR_(iStr);

  if (Platform == PL_I16) { // Платформа 16 бит 8086
    short lAdr = iNom - (PC + BaseAddres + 3);
    Program[PC++] = 0xE8;
    Program[PC++] = ((char *)(&lAdr))[0];
    Program[PC++] = ((char *)(&lAdr))[1];
  } else if (Platform == PL_I32) { // Платформа 32бит 80386
    int lAdr = iNom - (PC + BaseAddres + 5);
    Program[PC++] = 0xE8;
    Program[PC++] = ((char *)(&lAdr))[0];
    Program[PC++] = ((char *)(&lAdr))[1];
    Program[PC++] = ((char *)(&lAdr))[2];
    Program[PC++] = ((char *)(&lAdr))[3];
  } else if (Platform == PL_I64) { // Платформа 64 бит
    int lAdr = iNom - (PC + BaseAddres + 5);
    Program[PC++] = 0xE8;
    Program[PC++] = ((char *)(&lAdr))[0];
    Program[PC++] = ((char *)(&lAdr))[1];
    Program[PC++] = ((char *)(&lAdr))[2];
    Program[PC++] = ((char *)(&lAdr))[3];
  } else
    ERR("call_");
}
void ret_() {

  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0xC3;
  } else if (Platform == PL_I32) { // Платформа 32бит 80386
    Program[PC++] = 0xEB;
  } else if (Platform == PL_I64) { // Платформа 64 бит
    Program[PC++] = 0xEB;
  } else
    ERR("ret_");
}
