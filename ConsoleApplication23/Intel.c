#include "intel.h"
#include "generator.h"

const char *regname[3][9] = {
  { "AL", "CL", "DL", "BL", "AH", "CH", "DH", "BH" },
  { "AX", "CX", "DX", "BX", "SP", "BP", "SI", "DI" },
  { "EAX","ECX","EDX","EBX","ESP","EBP","ESI","EDI" } 
};
/*
	Возвращает индекс регистра или -1 в случае ошибки
*/
static int getRegIndex(const char *reg, int offset) {
	for (int i = 0; i < 8; i++)
	{
		if (!strcmp(reg, regname[offset][i]))
			return i;
	}
	return -1;
}

/*
	Копирует value в reg 
	Формат комманды - B0 + rb — MOV r8, imm8
*/
void movb(const char *reg, uchar value) {
	int i = getRegIndex(reg, 0);
	if (i == -1) 
		ERR("Bad register name");
	switch (Platform) {
	case PL_I16:
	case PL_I32:
	{
		int i = getRegIndex(reg, 0);
		Program[PC++] = 0xB0 + i;
		Program[PC++] = value;
	}
	break;
	default:
		ERR("mov_AL_");
	}
}

/*
	Копирует value в reg 
	Формат комманды - B0 + rw — MOV r16, imm16
*/
void movw(const char *reg, ushort value) {
	int i = getRegIndex(reg, 1);
	if (i == -1) 
		ERR("Bad register name");
	switch (Platform) {
	case PL_I16:
	case PL_I32:
	{
		int i = getRegIndex(reg, 1);
		Program[PC++] = 0xB8 + i;
		Program[PC++] = ((uchar *)&value)[0];
		Program[PC++] = ((uchar *)&value)[1];

	}
	break;
	default:
		ERR("mov_AL_");
	}
}

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
void mov_ESP_(uint value) {
  if (Platform == PL_I32) { // Платформа 32бит 80386
    Program[PC++] = 0xBC;
    Program[PC++] = ((uchar *)&value)[0];
    Program[PC++] = ((uchar *)&value)[1];
    Program[PC++] = ((uchar *)&value)[2];
    Program[PC++] = ((uchar *)&value)[3];
  } else if (Platform == PL_I64) { // Платформа 64 бит
    Program[PC++] = 0xBC;
    Program[PC++] = ((uchar *)&value)[0];
    Program[PC++] = ((uchar *)&value)[1];
    Program[PC++] = ((uchar *)&value)[2];
    Program[PC++] = ((uchar *)&value)[3];
  } else
    ERR("mov_ESP_");
}
void mov_EDI_(uint value) {
  if (Platform == PL_I32) { // Платформа 32бит 80386
    Program[PC++] = 0xBF;
    Program[PC++] = ((uchar *)&value)[0];
    Program[PC++] = ((uchar *)&value)[1];
    Program[PC++] = ((uchar *)&value)[2];
    Program[PC++] = ((uchar *)&value)[3];
  } else if (Platform == PL_I64) { // Платформа 64 бит
    Program[PC++] = 0xBF;
    Program[PC++] = ((uchar *)&value)[0];
    Program[PC++] = ((uchar *)&value)[1];
    Program[PC++] = ((uchar *)&value)[2];
    Program[PC++] = ((uchar *)&value)[3];
  } else
    ERR("mov_EDI_");
}
void mov_A_DX_(ushort value) {
	if (Platform == PL_I16) { // Платформа 16 бит 8086
		Program[PC++] = 0x89;
		Program[PC++] = 0x16;
		Program[PC++] = ((uchar *)&value)[0];
		Program[PC++] = ((uchar *)&value)[1];
	}
	else
		ERR("mov_A_DX_");
}
void mov_DX_A_(ushort value) {
	if (Platform == PL_I16) { // Платформа 16 бит 8086
		Program[PC++] = 0x8B;
		Program[PC++] = 0x16;
		Program[PC++] = ((uchar *)&value)[0];
		Program[PC++] = ((uchar *)&value)[1];
	}
	else
		ERR("mov_DX_A_");
}
void mov_AX_A_(ushort value) {
	if (Platform == PL_I16) { // Платформа 16 бит 8086
		Program[PC++] = 0xA1;
		Program[PC++] = ((uchar *)&value)[0];
		Program[PC++] = ((uchar *)&value)[1];
	}
	else
		ERR("mov_AX_A_");
}
void mov_SI_A_(ushort value) {
	if (Platform == PL_I16) { // Платформа 16 бит 8086
		Program[PC++] = 0x8B;
		Program[PC++] = 0x36;
		Program[PC++] = ((uchar *)&value)[0];
		Program[PC++] = ((uchar *)&value)[1];
	}
	else
		ERR("mov_SI_A");
}

void int_(uchar value) {
  if (Platform == PL_I16) { // Платформа 16 бит 8086
    Program[PC++] = 0xCD;
    Program[PC++] = value;
  } else if (Platform == PL_I32) { // Платформа 32бит 80386
    Program[PC++] = 0xCD;
    Program[PC++] = value;
  } else if (Platform == PL_I64) { // Платформа 64 бит
    Program[PC++] = 0xCD;
    Program[PC++] = value;
  } else
    ERR("Ошибка такой команды в выбраной платформе не сущестукет ");
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

void jmp_byte(const char *str) {

  uint value = ADR_(str);

  if (Platform == PL_I16) { // Платформа 16 бит 8086
    char lAdr = value - (PC + BaseAddres + 2);
    Program[PC++] = 0xEB;
    Program[PC++] = (char)(lAdr);
  } else if (Platform == PL_I32) { // Платформа 32бит 80386
    char lAdr = value - (PC + BaseAddres + 2);
    Program[PC++] = 0xEB;
    Program[PC++] = (char)(lAdr);
  } else if (Platform == PL_I64) { // Платформа 64 бит
    char lAdr = value - (PC + BaseAddres + 2);
    Program[PC++] = 0xEB;
    Program[PC++] = (char)(lAdr);
  } else
    ERR("jmp_byte");
}
void jz_byte(const char *str) {

  uint value = ADR_(str);

  if (Platform == PL_I16) { // Платформа 16 бит 8086
    char lAdr = value - (PC + BaseAddres + 2);
    Program[PC++] = 0x74;
    Program[PC++] = (char)(lAdr);
  } else if (Platform == PL_I32) { // Платформа 32бит 80386
    char lAdr = value - (PC + BaseAddres + 2);
    Program[PC++] = 0x74;
    Program[PC++] = (char)(lAdr);
  } else if (Platform == PL_I64) { // Платформа 64 бит
    char lAdr = value - (PC + BaseAddres + 2);
    Program[PC++] = 0x74;
    Program[PC++] = (char)(lAdr);
  } else
    ERR("jz_byte");
}
void call_(const char *str) {

  uint value = ADR_(str);

  if (Platform == PL_I16) { // Платформа 16 бит 8086
    short lAdr = value - (PC + BaseAddres + 3);
    Program[PC++] = 0xE8;
    Program[PC++] = ((char *)(&lAdr))[0];
    Program[PC++] = ((char *)(&lAdr))[1];
  } else if (Platform == PL_I32) { // Платформа 32бит 80386
    int lAdr = value - (PC + BaseAddres + 5);
    Program[PC++] = 0xE8;
    Program[PC++] = ((char *)(&lAdr))[0];
    Program[PC++] = ((char *)(&lAdr))[1];
    Program[PC++] = ((char *)(&lAdr))[2];
    Program[PC++] = ((char *)(&lAdr))[3];
  } else if (Platform == PL_I64) { // Платформа 64 бит
    int lAdr = value - (PC + BaseAddres + 5);
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
