// One_File_Codegenerator.cpp : Этот файл содержит функцию "main". Здесь
// начинается и заканчивается выполнение программы.
//
// Абудлов Тимур 2019 год
//
#pragma region =================================== Заголовочные файлы.

#define _CRT_SECURE_NO_WARNINGS // Отключение предупреждения для потенциально
								// небезопасных функций crt
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <stdbool.h>

#define strdup _strdup
#pragma endregion
#pragma region =================================== Константы         .

#define PL_I16 16                // 16 битный режим интел
#define PL_I32 32                // 32 битный режим интел
#define PL_I64 64                // 64 битный режим интел
#define PL_Z80 80                // Процесор Z80
#define MAX_SIZE_MEM 1024 * 1440 //Размер 3.5 диска

#pragma endregion
#pragma region =================================== Типы.

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

#pragma endregion
#pragma region =================================== Переменные.

uint G_PLA = PL_I16; // Глобальаня переменая выбора платформы
uint G_ADR = 0; // Адрес где находимся в масиве G_MEM в данный момент
uint L_ADR = 0; // Базовый адрес
// Адрес в ходе выполнения программы = L_ADR+G_ADR
uchar G_MEM[MAX_SIZE_MEM]; // Готовый код программы
char *Labs[MAX_SIZE_MEM];  // Списко меток

#pragma endregion
#pragma region =================================== Библиотека.

// Переводит из кодировки cp1251  cp866
void cp1251_cp866(char *S) {
	int i = 0;

	if (S != NULL)
		for (i = 0; S[i] != 0; i++)
			if (((uchar)S[i] >= 192) && ((uchar)S[i] <= 223))
				S[i] = S[i] - 64;
			else if (((uchar)S[i] >= 224) && ((uchar)S[i] <= 239))
				S[i] = S[i] - 64;
			else if (((uchar)S[i] >= 240) && ((uchar)S[i] <= 255))
				S[i] = S[i] - 16;
			else if ((uchar)S[i] == 168)
				S[i] = (uchar)240;
			else if ((uchar)S[i] == 184)
				S[i] = (uchar)241;
}

char *Tr_SumStr(char *iStr1, char *iStr2) { // Сложение строк
	char *res = NULL; // Результирующая строка
	size_t len1;      // Длина первой строки
	size_t len2;      // Длина второй строки

	len1 = strlen(iStr1);
	len2 = strlen(iStr2);
	res = (char *)malloc(len1 + len2 + 1);

	for (int f = 0; iStr1[f] != 0; f++)
		res[f] = iStr1[f];
	for (int f = 0; iStr2[f] != 0; f++)
		res[len1 + f] = iStr2[f];
	res[len1 + len2] = 0;
	return res;
}

#pragma endregion
#pragma region =================================== Метки.

uint ADR_(const char *iNam) { // Возвращает адрес метки

	int res = -1;

	// Поиск локальной метки =================================================
	// Двигаемся вниз по коду пока не встретим глобальную метку
	// либо конец программы либо не найдем
	int i = G_ADR;
	while ((res == -1) // ПОка не нашли метку
		&& (i < MAX_SIZE_MEM) // Пока не дошли до конца программы
		&&
		((Labs[i] == NULL) || (Labs[i][0] == '@'))) // пока это локальная метка
		if ((Labs[i] != NULL) && (strcmp(iNam, (char *)&(Labs[i][1])) == 0))
			res = i;
		else
			i = i + 1;
	// Двигаемся верх по коду пока не встретим глобальную метку
	// либо начало программы либо не найдем
	i = G_ADR;
	while ((res == -1) // ПОка не нашли метку
		&& (i >= 0) // Пока не дошли до конца программы
		&&
		((Labs[i] == NULL) || (Labs[i][0] == '@'))) // пока это локальная метка
		if ((Labs[i] != NULL) && (strcmp(iNam, (char *)&(Labs[i][1])) == 0))
			res = i;
		else
			i = i - 1;
	// ПОиск Глобальной метки =================================================
	// Двигаемся вниз по коду пока не встретим
	// конец программы либо не найдем метку
	i = G_ADR;
	while ((res == -1) // ПОка не нашли метку
		&& (i < MAX_SIZE_MEM)) // Пока не дошли до конца программы
		if ((Labs[i] != NULL) && (strcmp(iNam, Labs[i]) == 0))
			res = i;
		else
			i = i + 1;
	// Двигаемся верх по коду пока не встретим
	// начало программы либо не найдем метку
	i = G_ADR;
	while ((res == -1) // ПОка не нашли метку
		&& (i >= 0)) // Пока не дошли до конца программы
		if ((Labs[i] != NULL) && (strcmp(iNam, Labs[i]) == 0))
			res = i;
		else
			i = i - 1;

	printf(" %s %d \r\n", iNam, res);
	return res + L_ADR;
}
void LAB_(const char *iStr) { // Создает ЛОкальную Метку

	Labs[G_ADR] = Tr_SumStr(strdup("@"), strdup(iStr));
}
void FUN_(const char *iStr) { // Создает глобальную метку
	Labs[G_ADR] = strdup(iStr);
}
bool LAB_INIT() {
	for (int i = 0; i < MAX_SIZE_MEM; i++)
		Labs[i] = NULL;
	return true;
}

#pragma endregion
#pragma region =================================== КРОСС.
// Универсальные для всех платформ =====================

// Выбор платформы
void PLA_(int iPla) { 
	G_PLA = iPla;
}

// Устанавлвиает базовый адрес размещения кода
void ORG_(uint iAdr) { 
	L_ADR = iAdr;
}

// Это типа ошибка компидяции
void ERR(const char *iStr) {
	char *lEr = (char *)strdup(iStr);
	// cp1251_cp866(lEr);
	printf("%s", iStr);
	exit(EXIT_FAILURE);
}

// Распологает строку в памяти
void STR_(const char *iStr) { 
	for (int i = 0; iStr[i] != 0; i++) {
		G_MEM[G_ADR] = iStr[i];
		G_ADR = G_ADR + 1;
	}
	G_MEM[G_ADR] = 0;
	G_ADR = G_ADR + 1;
}

// Создает Метку и строку одинаковые
void STL_(const char *iStr) {
	LAB_(iStr);
	STR_(iStr);
}

// Размещает 1 байт
void DB_(uchar iNom) {
	G_MEM[G_ADR] = iNom;
	G_ADR = G_ADR + 1;
}

void DW_(ushort value) { // Размещает 2 байт
     G_MEM[G_ADR++] = ((uchar *)&value)[0];
	 G_MEM[G_ADR++] = ((uchar *)&value)[1];
}
void DD_(uint value) { // Размещает 2 байт
     G_MEM[G_ADR++] = ((uchar *)&value)[0];
	 G_MEM[G_ADR++] = ((uchar *)&value)[1];
	 G_MEM[G_ADR++] = ((uchar *)&value)[2];
	 G_MEM[G_ADR++] = ((uchar *)&value)[3];
}

void db_(uchar value) { // Размещает 1 байт
  G_MEM[G_ADR++] = value;
}
void dw_(ushort value) { // Размещает 2 байт
     G_MEM[G_ADR++] = ((uchar *)&value)[0];
	 G_MEM[G_ADR++] = ((uchar *)&value)[1];
}
void dd_(uint value) { // Размещает 2 байт
     G_MEM[G_ADR++] = ((uchar *)&value)[0];
	 G_MEM[G_ADR++] = ((uchar *)&value)[1];
	 G_MEM[G_ADR++] = ((uchar *)&value)[2];
	 G_MEM[G_ADR++] = ((uchar *)&value)[3];
}
 
#pragma endregion
#pragma region =================================== INTEL.
// Команеды специфичные только для INTEL ===============

void NOP_() {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0x90;
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I32) { // Платформа 32бит 80386
		G_MEM[G_ADR] = 0x90;
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I64) { // Платформа 64 бит
		G_MEM[G_ADR] = 0x90;
		G_ADR = G_ADR + 1;
	}
	else
		ERR(" ERR NOP_ ");
}
void cli() {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0xFA;
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I32) { // Платформа 32бит 80386
		G_MEM[G_ADR] = 0xFA;
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I64) { // Платформа 64 бит
		G_MEM[G_ADR] = 0xFA;
		G_ADR = G_ADR + 1;
	}
	else
		ERR(" ERR cli ");
}
void mov_EDX_(uint value) {
	if (G_PLA== PL_I32) { // Платформа 16 бит 8086
		G_MEM[G_ADR++] = 0xBA;    
		G_MEM[G_ADR++] = ((uchar *)&value)[0];
		G_MEM[G_ADR++] = ((uchar *)&value)[1];
		G_MEM[G_ADR++] = ((uchar *)&value)[2];
		G_MEM[G_ADR++] = ((uchar *)&value)[3];
	}
	else
		ERR("mov_EDX_");
}
void mov_EAX_(uint value) {
	if (G_PLA == PL_I32) { // Платформа 16 бит 8086
		G_MEM[G_ADR++] = 0xB8;    
		G_MEM[G_ADR++] = ((uchar *)&value)[0];
		G_MEM[G_ADR++] = ((uchar *)&value)[1];
		G_MEM[G_ADR++] = ((uchar *)&value)[2];
		G_MEM[G_ADR++] = ((uchar *)&value)[3];
	}
	else
		ERR("mov_EAX_");
}
void mov_AX_A_DD(uint value) {     
    if (G_PLA == PL_I32) { // Платформа 16 бит 8086
		G_MEM[G_ADR++] = 0x66;
		G_MEM[G_ADR++] = 0xA1;
		G_MEM[G_ADR++] = ((uchar *)&value)[0];
		G_MEM[G_ADR++] = ((uchar *)&value)[1];
		G_MEM[G_ADR++] = ((uchar *)&value)[2];
		G_MEM[G_ADR++] = ((uchar *)&value)[3];
	}else 

		ERR("mov_AX_A_DD");
}
void mov_DX_A_DD(uint value) {
	if (G_PLA == PL_I32) { // Платформа 16 бит 8086
		G_MEM[G_ADR++] = 0x66;
		G_MEM[G_ADR++] = 0x8B;
		G_MEM[G_ADR++] = 0x15;
		G_MEM[G_ADR++] = ((uchar *)&value)[0];
		G_MEM[G_ADR++] = ((uchar *)&value)[1];
		G_MEM[G_ADR++] = ((uchar *)&value)[2];
		G_MEM[G_ADR++] = ((uchar *)&value)[3];
	}
	else
		ERR("mov_DX_A_DD");     
}
void add_EAX_EDX_(){
  if (G_PLA == PL_I32) { // Платформа 32бит 80386
    G_MEM[G_ADR++] = 0x01;
    G_MEM[G_ADR++] = 0xD0;
  } else if (G_PLA == PL_I64) { // Платформа 64 бит
    G_MEM[G_ADR++] = 0x01;
    G_MEM[G_ADR++] = 0xD0;
  } else
    ERR("add_EAX_EDX_");
}    
void mov_ESI_EAX_() {
  if (G_PLA == PL_I32) { // Платформа 32 бит 80386
    G_MEM[G_ADR++] = 0x89;
    G_MEM[G_ADR++] = 0xC6;
  } else
  if (G_PLA == PL_I64) { // Платформа 64 бит 80386
    G_MEM[G_ADR++] = 0x89;
    G_MEM[G_ADR++] = 0xC6;
  } else
    ERR("mov_ESI_EAX_");
}
void mov_A_ESI_AL_() {
  if (G_PLA == PL_I32) { // Платформа 32 бит 80386
    G_MEM[G_ADR++] = 0x88;
    G_MEM[G_ADR++] = 0x06;
  } else
  if (G_PLA == PL_I64) { // Платформа 64 бит 80386
    G_MEM[G_ADR++] = 0x67;
    G_MEM[G_ADR++] = 0x88;
    G_MEM[G_ADR++] = 0x06;
  } else
    ERR("mov_A_ESI_AL_");
}
void inc_ESI_() {       
  if (G_PLA == PL_I32) { // Платформа 32 бит 80386
    G_MEM[G_ADR++] = 0x46;   
  } else
  if (G_PLA == PL_I64) { // Платформа 64 бит 8086      
    G_MEM[G_ADR++] = 0xFF;
    G_MEM[G_ADR++] = 0xC6;
  } else
    ERR("inc_ESI_");
}
void mov_A_DD_DX_(uint value) {
	if (G_PLA == PL_I32) { // Платформа 16 бит 8086
		G_MEM[G_ADR++] = 0x66;       //66 89 15 00000000   
		G_MEM[G_ADR++] = 0x89;
		G_MEM[G_ADR++] = 0x15;
		G_MEM[G_ADR++] = ((uchar *)&value)[0];
		G_MEM[G_ADR++] = ((uchar *)&value)[1];
		G_MEM[G_ADR++] = ((uchar *)&value)[2];
		G_MEM[G_ADR++] = ((uchar *)&value)[3];
	}
	else
		ERR("mov_A_DD_DX_");     
}
void mov_SP_AX() {
  if (G_PLA == PL_I16) { // Платформа 16 бит 8086
    G_MEM[G_ADR++] = 0x8B;
    G_MEM[G_ADR++] = 0xE0;
  } else if (G_PLA == PL_I32) { // Платформа 32бит 80386
    G_MEM[G_ADR++] = 0x66;            //6689C4   
    G_MEM[G_ADR++] = 0x89;
    G_MEM[G_ADR++] = 0xC4;   
  } else if (G_PLA == PL_I64) { // Платформа 64 бит
    G_MEM[G_ADR++] = 0x66;            //6689C4   
    G_MEM[G_ADR++] = 0x89;
    G_MEM[G_ADR++] = 0xC4;   
  } else
    ERR("mov_SP_AX");
}
void mov_FS_AX() {
  if (G_PLA == PL_I16) { // Платформа 16 бит 8086
    G_MEM[G_ADR++] = 0x8E;
    G_MEM[G_ADR++] = 0xE0;
  } else if (G_PLA == PL_I32) { // Платформа 32бит 80386
    G_MEM[G_ADR++] = 0x8E;
    G_MEM[G_ADR++] = 0xE0;
  } else if (G_PLA == PL_I64) { // Платформа 64 бит
    G_MEM[G_ADR++] = 0x8E;
    G_MEM[G_ADR++] = 0xE0;
  } else
    ERR("mov_FS_AX");
}
void mov_GS_AX() {
  if (G_PLA == PL_I16) { // Платформа 16 бит 8086
    G_MEM[G_ADR++] = 0x8E;
    G_MEM[G_ADR++] = 0xE8;
  } else if (G_PLA == PL_I32) { // Платформа 32бит 80386
    G_MEM[G_ADR++] = 0x8E;
    G_MEM[G_ADR++] = 0xE8;
  } else if (G_PLA == PL_I64) { // Платформа 64 бит
    G_MEM[G_ADR++] = 0x8E;
    G_MEM[G_ADR++] = 0xE8;
  } else
    ERR("mov_GS_AX");
}


void in_AL_(uchar value) {
  if (G_PLA == PL_I16)       { // Платформа 16 бит 8086
    G_MEM[G_ADR++] = 0xE4;
    G_MEM[G_ADR++] = value;
  } else if (G_PLA == PL_I32) { // Платформа 32бит 80386
    G_MEM[G_ADR++] = 0xE4;
    G_MEM[G_ADR++] = value;
  } else if (G_PLA == PL_I64) { // Платформа 64 бит
    G_MEM[G_ADR++] = 0xE4;
    G_MEM[G_ADR++] = value;
  } else
    ERR("in_AL_");
}
void out_AL_(uchar value) {
  if (G_PLA == PL_I16)       { // Платформа 16 бит 8086
    G_MEM[G_ADR++] = 0xE6;
    G_MEM[G_ADR++] = value;
  } else if (G_PLA == PL_I32) { // Платформа 32бит 80386
    G_MEM[G_ADR++] = 0xE6;
    G_MEM[G_ADR++] = value;
  } else if (G_PLA == PL_I64) { // Платформа 64 бит
    G_MEM[G_ADR++] = 0xE6;
    G_MEM[G_ADR++] = value;
  } else
    ERR("out_AL_");
}
void or_AL_(uchar value) {
  if (G_PLA == PL_I16)       { // Платформа 16 бит 8086
    G_MEM[G_ADR++] = 0x0C;
    G_MEM[G_ADR++] = value;
  } else if (G_PLA == PL_I32) { // Платформа 32бит 80386
    G_MEM[G_ADR++] = 0x0C;
    G_MEM[G_ADR++] = value;
  } else if (G_PLA == PL_I64) { // Платформа 64 бит
    G_MEM[G_ADR++] = 0x0C;
    G_MEM[G_ADR++] = value;
  } else
    ERR("or_AL_");
}
void lgdt_(ushort value) {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR++] = 0x0F;
		G_MEM[G_ADR++] = 0x01;
		G_MEM[G_ADR++] = 0x16;
		G_MEM[G_ADR++] = ((uchar *)&value)[0];
		G_MEM[G_ADR++] = ((uchar *)&value)[1];
	}
	else
		ERR("lgdt_");
}
void lidt_(ushort value) {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR++] = 0x0F;
		G_MEM[G_ADR++] = 0x01;
		G_MEM[G_ADR++] = 0x1E;
		G_MEM[G_ADR++] = ((uchar *)&value)[0];
		G_MEM[G_ADR++] = ((uchar *)&value)[1];
	}
	else
		ERR("lidt_");
}
void mov_EAX_CR0(){
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR++] = 0x0F;
		G_MEM[G_ADR++] = 0x20;
		G_MEM[G_ADR++] = 0xC0;                  
	}
	else
		ERR("mov_EAX_CR0"); 

} 
void mov_CR0_EAX(){
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR++] = 0x0F;
		G_MEM[G_ADR++] = 0x22;
		G_MEM[G_ADR++] = 0xC0;                  
	}
	else
		ERR("mov_EAX_CR0"); 

} 
void jmp_32b(ushort value1,ushort value2){
// Команда прыжка в 32 битный режим 
// Дальний переход value1 номер страницы кода 
// Дальний переход value2 адрес внутри страницы  
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR++] = 0xEA;
		G_MEM[G_ADR++] = ((uchar *)&value2)[0];
		G_MEM[G_ADR++] = ((uchar *)&value2)[1];
		G_MEM[G_ADR++] = ((uchar *)&value1)[0];
		G_MEM[G_ADR++] = ((uchar *)&value1)[1];
	}
	else
		ERR("jmp_32b");   
}  
      


void xor_EAX_EAX() {
	if (G_PLA == PL_I32) { // Платформа 32бит 80386
		G_MEM[G_ADR] = 0x66;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0x31;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0xC0;
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I64) { // Платформа 64 бит
		G_MEM[G_ADR] = 0x66;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0x31;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0xC0;
		G_ADR = G_ADR + 1;
	}
	else
		ERR("xor_EAX_EAX");
}

void inc_DI_() {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
    G_MEM[G_ADR++] = 0x47;
  } else
  if (G_PLA == PL_I32) { // Платформа 32 бит 8086
    G_MEM[G_ADR++] = 0x66;
    G_MEM[G_ADR++] = 0x47;
  } else
  if (G_PLA == PL_I64) { // Платформа 64 бит 8086
    G_MEM[G_ADR++] = 0x66;
    G_MEM[G_ADR++] = 0xFF;
    G_MEM[G_ADR++] = 0xC7;
  } else
    ERR("inc_DI_");
}
void inc_SI_() {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0x46;
		G_ADR = G_ADR + 1;
	}
	else
		ERR("inc_SI_");
}
void test_AL_AL_() {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
    G_MEM[G_ADR++] = 0x84;
    G_MEM[G_ADR++] = 0xC0;
  } else
  if (G_PLA == PL_I32) { // Платформа 32 бит 8086
    G_MEM[G_ADR++] = 0x84;
    G_MEM[G_ADR++] = 0xC0;
  } else
  if (G_PLA == PL_I64) { // Платформа 64 бит 8086
    G_MEM[G_ADR++] = 0x84;
    G_MEM[G_ADR++] = 0xC0;
  } else
    ERR("test_AL_AL");
}
void test_AX_AX_() {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0x85;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0xC0;
		G_ADR = G_ADR + 1;
	}
	else
		ERR("test_AX_AX");
}
void xor_AX_AX() {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0x33;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0xC0;
		G_ADR = G_ADR + 1;
	}
	else
		ERR("xor_AX_AX");
}
void mov_CS_AX() {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		ERR("mov_CS_AX");
	}
	else if (G_PLA == PL_I32) { // Платформа 32бит 80386
		G_MEM[G_ADR] = 0x8E;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0xC8;
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I64) { // Платформа 64 бит
		G_MEM[G_ADR] = 0x8E;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0xC8;
		G_ADR = G_ADR + 1;
	}
	else
		ERR("mov_CS_AX");
}
void mov_DS_AX() {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0x8E;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0xD8;
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I32) { // Платформа 32бит 80386
		G_MEM[G_ADR] = 0x8E;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0xD8;
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I64) { // Платформа 64 бит
		G_MEM[G_ADR] = 0x8E;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0xD8;
		G_ADR = G_ADR + 1;
	}
	else
		ERR("Ошибка такой команды в выбраной платформе не сущестукет ");
}
void mov_SS_AX() {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0x8E;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0xD0;
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I32) { // Платформа 32бит 80386
		G_MEM[G_ADR] = 0x8E;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0xD0;
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I64) { // Платформа 64 бит
		G_MEM[G_ADR] = 0x8E;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0xD0;
		G_ADR = G_ADR + 1;
	}
	else
		ERR("Ошибка такой команды в выбраной платформе не сущестукет ");
}
void mov_ES_AX() {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0x8E;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0xC0;
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I32) { // Платформа 32бит 80386
		G_MEM[G_ADR] = 0x8E;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0xC0;
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I64) { // Платформа 64 бит
		G_MEM[G_ADR] = 0x8E;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0xC0;
		G_ADR = G_ADR + 1;
	}
	else
		ERR("Ошибка такой команды в выбраной платформе не сущестукет ");
}

void int_(uchar iNom) {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0xCD;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = iNom;
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I32) { // Платформа 32бит 80386
		G_MEM[G_ADR] = 0xCD;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = iNom;
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I64) { // Платформа 64 бит
		G_MEM[G_ADR] = 0xCD;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = iNom;
		G_ADR = G_ADR + 1;
	}
	else
		ERR("Ошибка такой команды в выбраной платформе не сущестукет ");
}
void mov_SP_(ushort iNom) {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0xBC;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[0];
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[1];
		G_ADR = G_ADR + 1;
	}
	else
		ERR("mov_SP_");
}
void mov_ESP_(uint iNom) {
	if (G_PLA == PL_I32) { // Платформа 32бит 80386
		G_MEM[G_ADR] = 0xBC;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[0];
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[1];
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[2];
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[3];
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I64) { // Платформа 64 бит
		G_MEM[G_ADR] = 0xBC;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[0];
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[1];
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[2];
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[3];
		G_ADR = G_ADR + 1;
	}
	else
		ERR("mov_ESP_");
}

void mov_SI_(ushort iNom) {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0xBE;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[0];
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[1];
		G_ADR = G_ADR + 1;
	}
	else
		ERR("mov_SI_");
}
void mov_DI_(ushort iNom) {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0xBF;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[0];
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[1];
		G_ADR = G_ADR + 1;
	}
	else
		ERR("mov_DI_");
}
void mov_EDI_(uint iNom) {
	if (G_PLA == PL_I32) { // Платформа 32бит 80386
		G_MEM[G_ADR] = 0xBF;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[0];
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[1];
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[2];
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[3];
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I64) { // Платформа 64 бит
		G_MEM[G_ADR] = 0xBF;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[0];
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[1];
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[2];
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[3];
		G_ADR = G_ADR + 1;
	}
	else
		ERR("mov_EDI_");
}
void mov_BP_(ushort iNom) {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0xBD;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[0];
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[1];
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I32) { // Платформа 32бит 80386
		G_MEM[G_ADR] = 0x66;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0xBD;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[0];
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[1];
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I64) { // Платформа 64 бит
		G_MEM[G_ADR] = 0x66;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0xBD;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[0];
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[1];
		G_ADR = G_ADR + 1;
	}
	else
		ERR("mov_BP_");
}

void mov_AX_(ushort iNom) {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0xB8;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[0];
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[1];
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I32) { // Платформа 32бит 80386
		G_MEM[G_ADR] = 0x66;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0xB8;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[0];
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[1];
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I64) { // Платформа 64 бит
		G_MEM[G_ADR] = 0x66;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0xB8;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[0];
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[1];
		G_ADR = G_ADR + 1;
	}
	else
		ERR("Ошибка такой команды в выбраной платформе не сущестукет ");
}
void mov_BX_(ushort iNom) {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0xBB;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[0];
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[1];
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I32) { // Платформа 32бит 80386
		G_MEM[G_ADR] = 0x66;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0xBB;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[0];
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[1];
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I64) { // Платформа 64 бит
		G_MEM[G_ADR] = 0x66;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0xBB;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[0];
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[1];
		G_ADR = G_ADR + 1;
	}
	else
		ERR("Ошибка такой команды в выбраной платформе не сущестукет ");
}
void mov_CX_(ushort iNom) {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0xB9;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[0];
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[1];
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I32) { // Платформа 32бит 80386
		G_MEM[G_ADR] = 0x66;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0xB9;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[0];
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[1];
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I64) { // Платформа 64 бит
		G_MEM[G_ADR] = 0x66;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0xB9;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[0];
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[1];
		G_ADR = G_ADR + 1;
	}
	else
		ERR("mov_CX_");
}

void mul_DL_() {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
    G_MEM[G_ADR++] = 0xF6;
    G_MEM[G_ADR++] = 0xE2;
  } else
  if (G_PLA == PL_I32) { // Платформа 16 бит 8086
    G_MEM[G_ADR++] = 0xF6;
    G_MEM[G_ADR++] = 0xE2;
  } else
    ERR("mul_DL_");
}
void inc_DX_() {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
    G_MEM[G_ADR++] = 0x42;
  } else
  if (G_PLA == PL_I32) { // Платформа 32 бит 8086
    G_MEM[G_ADR++] = 0x66;
    G_MEM[G_ADR++] = 0x42;
  } else
  if (G_PLA == PL_I64) { // Платформа 64 бит 8086
    G_MEM[G_ADR++] = 0x66;   // 66 FF C2   
    G_MEM[G_ADR++] = 0xFF;
    G_MEM[G_ADR++] = 0xC2;

  } else
    ERR("inc_DX_");
}
void mov_SI_AX_() {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0x8B;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0xF0;
		G_ADR = G_ADR + 1;
	}
	else
		ERR("mov_SI_AX_");
}
void add_AX_DX_() {
	 if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0x03; G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0xC2; G_ADR = G_ADR + 1;
	 }
else if (G_PLA == PL_I32) { // Платформа 16 бит 8086
    G_MEM[G_ADR++] = 0x66;
    G_MEM[G_ADR++] = 0x01;
    G_MEM[G_ADR++] = 0xD0;
      } 
else ERR("add_AX_DX_");
}
void shl_DL_1_() {
	 if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0xD0; G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0xE2; G_ADR = G_ADR + 1;
	 }
else if (G_PLA == PL_I32) { // Платформа 32 бит 8086
    G_MEM[G_ADR++] = 0xD0;
    G_MEM[G_ADR++] = 0xE2;
    } 
else ERR("shl_DL_1_");      
}
void mov_A_DX_(ushort iNom) {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0x89;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0x16;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[0];
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[1];
		G_ADR = G_ADR + 1;
	}
	else
		ERR("mov_A_DX_");
}
void mov_DX_(ushort value) {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR++] = 0xBA;
		G_MEM[G_ADR++] = ((uchar *)&value)[0];
		G_MEM[G_ADR++] = ((uchar *)&value)[1];
	} else
	if (G_PLA == PL_I32) { // Платформа 32 бит 8086
		G_MEM[G_ADR++] = 0x66;
		G_MEM[G_ADR++] = 0xBA;
		G_MEM[G_ADR++] = ((uchar *)&value)[0];
		G_MEM[G_ADR++] = ((uchar *)&value)[1];
	} else
	if (G_PLA == PL_I64) { // Платформа 64 бит 8086
		G_MEM[G_ADR++] = 0x66;
		G_MEM[G_ADR++] = 0xBA;
		G_MEM[G_ADR++] = ((uchar *)&value)[0];
		G_MEM[G_ADR++] = ((uchar *)&value)[1];
	} else
		ERR("mov_DX_");
}
void mov_DX_A_(ushort iNom) {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0x8B;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0x16;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[0];
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[1];
		G_ADR = G_ADR + 1;
	}
	else
		ERR("mov_DX_A_");
}
void mov_AX_A_(ushort iNom) {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0xA1;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[0];
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[1];
		G_ADR = G_ADR + 1;
	}
	else
		ERR("mov_AX_A_");
}
void mov_SI_A_(ushort iNom) {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0x8B;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0x36;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[0];
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((uchar *)&iNom)[1];
		G_ADR = G_ADR + 1;
	}
	else
		ERR("mov_SI_A");
}

void mov_AL_(uchar iNom) {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0xB0;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = iNom;
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I32) { // Платформа 32бит 80386
		G_MEM[G_ADR] = 0xB0;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = iNom;
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I64) { // Платформа 64 бит
		G_MEM[G_ADR] = 0xB0;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = iNom;
		G_ADR = G_ADR + 1;
	}
	else
		ERR("mov_AL_");
}
void mov_AH_(uchar iNom) {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0xB4;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = iNom;
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I32) { // Платформа 32бит 80386
		G_MEM[G_ADR] = 0xB4;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = iNom;
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I64) { // Платформа 64 бит
		G_MEM[G_ADR] = 0xB4;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = iNom;
		G_ADR = G_ADR + 1;
	}
	else
		ERR("mov_AH_");
}
void mov_BL_(uchar iNom) {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0xB3;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = iNom;
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I32) { // Платформа 32бит 80386
		G_MEM[G_ADR] = 0xB3;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = iNom;
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I64) { // Платформа 64 бит
		G_MEM[G_ADR] = 0xB3;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = iNom;
		G_ADR = G_ADR + 1;
	}
	else
		ERR("Ошибка такой команды в выбраной платформе не сущестукет ");
}
void mov_BH_(uchar iNom) {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0xB7;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = iNom;
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I32) { // Платформа 32бит 80386
		G_MEM[G_ADR] = 0xB7;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = iNom;
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I64) { // Платформа 64 бит
		G_MEM[G_ADR] = 0xB7;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = iNom;
		G_ADR = G_ADR + 1;
	}
	else
		ERR("Ошибка такой команды в выбраной платформе не сущестукет ");
}
void mov_DH_(uchar iNom) {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0xB6;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = iNom;
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I32) { // Платформа 32бит 80386
		G_MEM[G_ADR] = 0xB6;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = iNom;
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I64) { // Платформа 64 бит
		G_MEM[G_ADR] = 0xB6;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = iNom;
		G_ADR = G_ADR + 1;
	}
	else
		ERR("Ошибка такой команды в выбраной платформе не сущестукет ");
}
void mov_DL_(uchar iNom) {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0xB2;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = iNom;
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I32) { // Платформа 32бит 80386
		G_MEM[G_ADR] = 0xB2;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = iNom;
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I64) { // Платформа 64 бит
		G_MEM[G_ADR] = 0xB2;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = iNom;
		G_ADR = G_ADR + 1;
	}
	else
		ERR("Ошибка такой команды в выбраной платформе не сущестукет ");
}
void mov_CL_(uchar iNom) {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0xB1;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = iNom;
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I32) { // Платформа 32бит 80386
		G_MEM[G_ADR] = 0xB1;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = iNom;
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I64) { // Платформа 64 бит
		G_MEM[G_ADR] = 0xB1;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = iNom;
		G_ADR = G_ADR + 1;
	}
	else
		ERR("Ошибка такой команды в выбраной платформе не сущестукет ");
}
void mov_CH_(uchar iNom) {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0xB5;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = iNom;
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I32) { // Платформа 32бит 80386
		G_MEM[G_ADR] = 0xB5;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = iNom;
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I64) { // Платформа 64 бит
		G_MEM[G_ADR] = 0xB5;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = iNom;
		G_ADR = G_ADR + 1;
	}
	else
		ERR("mov_CH_");
}

void mov_A_DI_AL() {
	//  mov [di],al
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0x88;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0x05;
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I32) { // Платформа 32бит 80386
		G_MEM[G_ADR] = 0x67;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0x88;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0x05;
		G_ADR = G_ADR + 1;
	}
	else
		ERR("mov_A_DI_AL");
}
void mov_A_SI_AL() {
	//  mov [di],al
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0x88;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0x04;
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I32) { // Платформа 32бит 80386
		G_MEM[G_ADR] = 0x67;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0x88;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0x04;
		G_ADR = G_ADR + 1;
	}
	else
		ERR("mov_A_SI_AL");
}
void mov_AL_A_DI() {
	//  mov al,[di]
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0x8A;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0x05;
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I32) { // Платформа 32бит 80386
		G_MEM[G_ADR] = 0x67;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0x8A;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0x05;
		G_ADR = G_ADR + 1;
	}
	else
		ERR("mov_AL_A_DI");
}
void mov_AL_A_SI() {
	//  mov al,[di]
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0x8A;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0x04;
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I32) { // Платформа 32бит 80386
		G_MEM[G_ADR] = 0x67;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0x8A;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0x04;
		G_ADR = G_ADR + 1;
	}
	else
		ERR("mov_AL_A_SI");
}

void mov_A_DI_AX() {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0x89;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0x05;
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I32) { // Платформа 32 бит 80386
		G_MEM[G_ADR] = 0x67;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0x66;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0x89;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0x05;
		G_ADR = G_ADR + 1;
	}
	else
		ERR("mov_A_DI_AX");
}

void mov_A_ES_DI_AL() {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0x26;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0x88;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0x05;
		G_ADR = G_ADR + 1;          // 26 67 88 05
	}
	else if (G_PLA == PL_I32) { // Платформа 32 бит 80386
		G_MEM[G_ADR] = 0x26;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0x67;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0x88;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0x05;
		G_ADR = G_ADR + 1;
	}
	else
		ERR("mov_A_ES_DI_AL");
}
void mov_A_ES_SI_AL() {
	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0x26;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0x88;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0x04;
		G_ADR = G_ADR + 1;          // 26 67 88 05
	}
	else if (G_PLA == PL_I32) { // Платформа 32 бит 80386
		G_MEM[G_ADR] = 0x26;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0x67;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0x88;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = 0x04;
		G_ADR = G_ADR + 1;
	}
	else
		ERR("mov_A_ES_SI_AL");
}

void jmp_byte(const char *iStr) {

	uint iNom = ADR_(iStr);

	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		char lAdr = iNom - (G_ADR + L_ADR + 2);
		G_MEM[G_ADR] = 0xEB;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = (char)(lAdr);
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I32) { // Платформа 32бит 80386
		char lAdr = iNom - (G_ADR + L_ADR + 2);
		G_MEM[G_ADR] = 0xEB;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = (char)(lAdr);
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I64) { // Платформа 64 бит
		char lAdr = iNom - (G_ADR + L_ADR + 2);
		G_MEM[G_ADR] = 0xEB;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = (char)(lAdr);
		G_ADR = G_ADR + 1;
	}
	else
		ERR("jmp_byte");
}
void jz_byte(const char *iStr) {

	uint iNom = ADR_(iStr);

	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		char lAdr = iNom - (G_ADR + L_ADR + 2);
		G_MEM[G_ADR] = 0x74;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = (char)(lAdr);
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I32) { // Платформа 32бит 80386
		char lAdr = iNom - (G_ADR + L_ADR + 2);
		G_MEM[G_ADR] = 0x74;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = (char)(lAdr);
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I64) { // Платформа 64 бит
		char lAdr = iNom - (G_ADR + L_ADR + 2);
		G_MEM[G_ADR] = 0x74;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = (char)(lAdr);
		G_ADR = G_ADR + 1;
	}
	else
		ERR("jz_byte");
}
void call_(const char *iStr) {

	uint iNom = ADR_(iStr);

	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		short lAdr = iNom - (G_ADR + L_ADR + 3);
		G_MEM[G_ADR] = 0xE8;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((char *)(&lAdr))[0];
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((char *)(&lAdr))[1];
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I32) { // Платформа 32бит 80386
		int lAdr = iNom - (G_ADR + L_ADR + 5);
		G_MEM[G_ADR] = 0xE8;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((char *)(&lAdr))[0];
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((char *)(&lAdr))[1];
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((char *)(&lAdr))[2];
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((char *)(&lAdr))[3];
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I64) { // Платформа 64 бит
		int lAdr = iNom - (G_ADR + L_ADR + 5);
		G_MEM[G_ADR] = 0xE8;
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((char *)(&lAdr))[0];
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((char *)(&lAdr))[1];
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((char *)(&lAdr))[2];
		G_ADR = G_ADR + 1;
		G_MEM[G_ADR] = ((char *)(&lAdr))[3];
		G_ADR = G_ADR + 1;
	}
	else
		ERR("call_");
}
void ret_() {

	if (G_PLA == PL_I16) { // Платформа 16 бит 8086
		G_MEM[G_ADR] = 0xC3;
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I32) { // Платформа 32бит 80386
		G_MEM[G_ADR] = 0xEB;
		G_ADR = G_ADR + 1;
	}
	else if (G_PLA == PL_I64) { // Платформа 64 бит
		G_MEM[G_ADR] = 0xEB;
		G_ADR = G_ADR + 1;
	}
	else
		ERR("ret_");
}

// =====================================================
#pragma endregion
#pragma region =================================== FUNC.

void VAR_WORD_(const char *iNam, ushort iNom) {
	LAB_(iNam);
	DB_(((uchar *)&iNom)[0]);
	DB_(((uchar *)&iNom)[1]);
}
void VAR_BYTE_(const char *iNam, uchar iNom) {
	LAB_(iNam);
	DB_(iNom);
}
void VAR_WORD_GLOBAL(const char *name, ushort number) {
  FUN_(name);
  DB_(((uchar *)&number)[0]);
  DB_(((uchar *)&number)[1]);
}
void VAR_BYTE_GLOBAL(const char *name, uchar number) {
  FUN_(name);
  DB_(number);
}

void Tr_Stop() {
	LAB_("ZZZ");
	NOP_();
	jmp_byte("ZZZ");
}
void Tr_Print(const char *iTex) {
	FUN_("Tr_Print");
	NOP_();
	mov_DI_(ADR_("lText"));
	call_("PRINT16");
	jmp_byte("NEX");
	LAB_("lText");
	STR_(iTex);
	LAB_("NEX");
	NOP_();
	FUN_("Tr_Print");
}
void Tr_Print32(const char *text) {

  FUN_("MyPrint32");
   
  NOP_();
   
  mov_EDI_(ADR_("lText"));
  //movw("DI", ADR_("lText")); нужно будет выяснить почему тут зависало 
    
  call_("PRINT32");
  jmp_byte("NEX");
  LAB_("lText");
  STR_(text);
  LAB_("NEX");
  NOP_();
  FUN_("MyPrint32");

}

void IncludeMyPrint() {

  // =============================================
  // подпрограмам вывода строки в консоль в 16 битном режиме
  // В DS:DI должен быть адрес строки
  G_PLA=PL_I16; // Выбираем платформу
  FUN_("PRINT16"); // Обьявляем новую область
  mov_AX_(0xB800); // mov ax,B800  Видеопамять
  mov_ES_AX();     // mov es,ax    в ES

  // Вычислем координату по Y
  mov_AX_A_(ADR_("CURR_Y"));
  mov_DL_(160);
  mul_DL_();

  // Вычислем координату по X
  mov_DX_A_(ADR_("CURR_X"));
  shl_DL_1_();
  add_AX_DX_();   
  mov_SI_AX_();

  LAB_("Cikl");     
  mov_AL_A_DI();    // mov al,[di]
  test_AL_AL_();    // test al,al
  jz_byte("EX");    // jz EX
  mov_A_ES_SI_AL(); // mov [ES:DI],AL Выводим сивмол на экран
  inc_SI_();        // inc Si
  mov_AL_(0x0F);
  mov_A_ES_SI_AL(); // mov [ES:SI],AL Выводим атрибуты сивмол на экран
  inc_SI_();        // inc Si
  inc_DI_();        // inc di
  jmp_byte("Cikl"); // jmp cikl       
  LAB_("EX");

  mov_DX_A_(ADR_("CURR_Y")); // Переход на след строку
  inc_DX_();
  mov_A_DX_(ADR_("CURR_Y"));
  mov_DX_(0);
  mov_A_DX_(ADR_("CURR_X"));
  ret_();
         
  //-------------------------------------------------------------------
  G_PLA=PL_I32; // Выбираем платформу
  FUN_("PRINT32"); // Обьявляем новую область
  
  mov_EAX_(0);// ОБнуляю EAX                                    
  mov_EDX_(0);// ОБнуляю EDX                                      
  // Вычислем координату по Y
  mov_AX_A_DD(ADR_("CURR_Y"));// Читаю в AX координату по Y
  mov_DL_(160);//
  mul_DL_();//Умножаю координату по Y на длину строки в байтх 
  // Вычислем координату по X
  mov_DX_A_DD(ADR_("CURR_X"));// Загружаю коо по Х
  shl_DL_1_();// Умножаю на 2 
  add_AX_DX_(); // ПРиьавляю к координате  вычселеной по Y
  mov_EDX_(0xB8000);// ЗАгржаю адрес видео памяти 
  add_EAX_EDX_(); // ПРибавляю его к  
  mov_ESI_EAX_();

  LAB_("Cikl");
  mov_AL_A_DI();    // mov al,[di]
  test_AL_AL_();    // test al,al
  jz_byte("EX");    // jz EX
  mov_A_ESI_AL_(); // mov [ES:DI],AL Выводим сивмол на экран
  inc_ESI_();        // inc Si
  mov_AL_(0x0F);
  mov_A_ESI_AL_();   // mov [ESI],AL Выводим атрибуты сивмол на экран
  inc_ESI_();        // inc Si
  inc_DI_();        // inc di
  jmp_byte("Cikl"); // jmp cikl       
  LAB_("EX");
   NOP_();Tr_Stop()    ;
  mov_DX_A_DD(ADR_("CURR_Y")); // Переход на след строку
  inc_DX_();
  mov_A_DD_DX_(ADR_("CURR_Y"));         
  mov_DX_(0);       
  mov_A_DD_DX_(ADR_("CURR_X"));

  ret_();


  VAR_WORD_GLOBAL("CURR_X", 0);
  VAR_WORD_GLOBAL("CURR_Y", 0);
}

#pragma endregion


     
// Таблица GDT     
void  gdt_00(){
;// НУЛЕВОЙ ДИСКРИПТОР  -; // Его использовать в процессоре нельзя
dw_(0)   ; // младшее слово предела
dw_(0)   ; // младшее слово предела
db_(0)   ; // младшее слово адреса
db_(0)   ; // младшее слово адреса
db_(0)   ; // младшее слово адреса
db_(0)   ; // младшее слово адреса
;// ---------------------;
}
void  gdt_01(){
;// ДИСКРИПТОР КОДА -----; // CS
dw_(0xFFFF)     ;//;// младшее слово предела  размер сегмента минус один элемент
dw_(0x00)       ;//;// младшее слово адреса
db_(0x00)       ;//;// 3-й (из четырёх) байт адреса
db_(0b10011010) ;//;{  Свойства сегмента 10011010 
//;  1 = 1 Бит P (Present) - Присутствие сегмента в памяти. Если этот бит
//;        установлен, то сегмент есть в памяти, если сброшен, то его нет.
//;  2 = 0 Поле DPL 1 Бит  - Уровень привилегий, который имеет объект
//;  3 = 0 Поле DPL 2 Бит  - Уровень привилегий, который имеет объект
//;  4 = 1 Поле Тип Сегмента 1101 - Сегмент кода для выполнения/чтения
//;  5 = 1 Поле Тип Сегмента 1001 - Сегмент Данных
//;  6 = 0 Поле Тип Сегмента
//;  7 = 1 Поле Тип Сегмента
//;  8 = 0 использовался ли за последнее время этот сегмент или нет при первом
//;        же обращение в 1 устанавливаеться
//;//}
db_(0b11001111) ;//;b ;{  Свойства сегмента
//; 1 = 1 если 1 то размер указываеться в 4кб страницах иначе просто в байтах
//; 2 = 1 если 1 то 32 битный код в сегменте иначе 16 битный
//; 3 = 0 Зарезервированный бит. Intel не рекомендует использовать этот бит
//; 4 = 0 Бит пользователя. Этот бит процессор не использует и позволяет программе
//;       использовать его в своих целях.
//; 5 старшая часть предела
//; 6 старшая часть предела
//; 7 старшая часть предела
//; 8 старшая часть предела
//;}
db_(0x00)       ;// 4-й байт адреса
//;// ------------------------------------------------------------------;
}
void  gdt_02(){    
//;// ДИСКРИПТОР ДАННЫХ ------------------------------------------------; // DS
dw_(0xFFFF)    ;// младшее слово предела
dw_(0x00)      ;// младшее слово адреса
db_(0x00)      ;// 3-й (из четырёх) байт адреса
db_(0b10010010);//{ Свойства сегмента
//;  1 = 1 Бит P (Present) - Присутствие сегмента в памяти. Если этот бит
//;      установлен, то сегмент есть в памяти, если сброшен, то его нет.
//;  2 = 0 Поле DPL 1 Бит  - Уровень привилегий, который имеет объект
//;  3 = 0 Поле DPL 2 Бит  - Уровень привилегий, который имеет объект
//;  4 = 1 Поле Тип Сегмента 1101 - Сегмент кода для выполнения/чтения
//;  5 = 1 Поле Тип Сегмента 1001 - Сегмент Данных
//;  6 = 0 Поле Тип Сегмента
//;  7 = 1 Поле Тип Сегмента
//;  8 = 0 использовался ли за последнее время этот сегмент или нет при первом
//;        же обращение в 1 устанавливаеться
//;//}
db_(0b11001111); //;{ Свойства сегмента
//; 1 = 1 если 1 то размер указываеться в 4кб страницах иначе просто в байтах
//; 2 = 1 если 1 то 32 битный код в сегменте иначе 16 битный
//; 3 = 0 Зарезервированный бит. Intel не рекомендует использовать этот бит
//; 4 = 0 Бит пользователя. Этот бит процессор не использует и позволяет программе
//;       использовать его в своих целях.
//; 5 старшая часть предела
//; 6 старшая часть предела
//; 7 старшая часть предела
//; 8 старшая часть предела   
db_(0x00)       ;// 4-й байт адреса
;// ---------------------;
}
void  gdt(){

FUN_("GDT_START");
gdt_00();// НУЛЕВОЙ ДИСКРИПТОР
gdt_01();// Дексриптор кода 
gdt_02();// Дексриптор Данных  

int  Siz_Gdt=ADR_("GDT")-ADR_("GDT_START");

FUN_("GDT");
dw_(Siz_Gdt);// Рземер таблицы
dd_(ADR_("GDT_START"));// Адрес таблицы
FUN_("GDT_END");

//DB      $09,$08         ; // Размер таблицы
//DB      $09,$0A,$0B,$0C ; // Адрес таблицы

} 
// Таблица IDT    
void  idt(){ 
// Таблица IDT     

        LAB_("IDT_START");   
        //; //Interrupt Descriptor Table
        dd_(0);//; // 0  Division by zero
        dd_(0);//; // 1  Debugger
        dd_(0);//; // 2  NMI
        dd_(0);//; // 3  Breakpoint
        dd_(0);//; // 4  Overflow
        dd_(0);//; // 5  Bounds
        dd_(0);//; // 6  Invalid Opcode
        dd_(0);//; // 7  Coprocessor not available
        dd_(0);//; // 8  Double fault
        dd_(0);//; // 9  Coprocessor Segment Overrun (386 or earlier only)
        dd_(0);//; // 10 Invalid Task State Segment
        dd_(0);//; // 11 Segment not present
        dd_(0);//; // 12 Stack Fault
        dd_(0);//; // 13 General protection fault
        dd_(0);//; // 14 Page fault
        dd_(0);//; // 15 reserved
        dd_(0);//; // 16 Math Fault
        dd_(0);//; // 17 Alignment Check
        dd_(0);//; // 18 Machine Check
        dd_(0);//; // 19 SIMD Floating-Point Exception
        dd_(0);//; // 20 Virtualization Exception
        dd_(0);//; // 21 Control Protection Exception
        dd_(0);//; // 22
        dd_(0);//; // 23
        dd_(0);//; // 24
        dd_(0);//; // 25
        dd_(0);//; // 26
        dd_(0);//; // 27
        dd_(0);//; // 28
        dd_(0);//; // 29
        dd_(0);//; // 30
        dd_(0);//; // 31
        dd_(0);//; // IRQ 0 - системный таймер
        dd_(0);//; // IRQ 1 - клавиатура
        dd_(0);//; // IRQ 2 - Дополнительный контроллер прерываний
        dd_(0);//; // IRQ 3 - Порты Com 1 и 3
        dd_(0);//; // IRQ 4 - Порты Com 2 и 4
        dd_(0);//; // IRQ 5 - Свободно
        dd_(0);//; // IRQ 6 - Контроллер гибких дисков (FDD)
        dd_(0);//; // IRQ 7 - Параллельный порт LPT
        dd_(0);//; // IRQ 8 - Часы реального времени CMOS
        dd_(0);//; // IRQ 9 - Совмещено с IRQ 2
        dd_(0);//; // IRQ 10- Свободно
        dd_(0);//; // IRQ 11- Свободно
        dd_(0);//; // IRQ 12- Порт мыши PS/2
        dd_(0);//; // IRQ 13- Сопроцессор (в настоящее время не используется)
        dd_(0);//; // IRQ 14- Первый контроллер IDE
        dd_(0);//; // IRQ 15- Второй контроллер IDE
        //--------------------------------------------------------------
        dw_(0);// Размер таблицы прерываний -1 байт
        dd_(0);// Адрес таблицы прерываний
        LAB_("IDT_END");
}                    


void Loader()
{
	PLA_(PL_I16); // Выбираем платформу
	ORG_(0x7C00); // Устанавливаем адрес работы программы
	FUN_(""); // Устанавливаем глобальную область видимости для меток
	// Устанавливаем сегментные регистры ===========
	xor_AX_AX(); // Обнуляем содержимое регистра AX
	mov_SS_AX(); // Устанавлиавем Сегмент стека 0
	mov_DS_AX(); // Устанавлиавем Сегмент данных 0
	mov_ES_AX(); // Устанавлиавем Сегмент Доп сег фиг зн зачем он нужен  0
	mov_SP_(0xFFFF);
	// =============================================

	// =============================================
	// Выбираем видео режим
	mov_AH_(0); // ПОдпрограмма установики  видео режима
	mov_AL_(3); // текст    80x25    16/8           CGA,EGA  b800  Comp,RGB,Enhanced
	int_(0x10); // Прерывание 10h

	// Выбираем страницу
	mov_AH_(5); // ПОдпрограмма выбора активной видео страницы
	mov_AL_(0); // Видео страница 0
	int_(0x10); // Прерывание 10h

	Tr_Print("Start Ok");

	// Прячем курсор
	mov_AH_(2); // ПОдпрограмма установки курсора
	mov_BH_(0); // Видео страница
	mov_DH_(25); // Номер строки установка в 25 делет невидимым курсор
	mov_DL_(0); // Колонка
	int_(0x10); // Прерывание 10h

	// =============================================
	Tr_Print("Start load 18 sectors");

	// Загрузка оставшейся части программы с диска
	/* Источник http://www.codenet.ru/progr/dos/int_0012.php

	02H читать секторы
	вход: DL = номер диска (0=диск A...; 80H=тв.диск 0; 81H=тв.диск 1)
	   DH = номер головки чтения/записи
	   CH = номер дорожки (цилиндра)(0-n) =¬
	   CL = номер сектора (1-n) ===========¦== См. замечание ниже.
	   AL = число секторов (в сумме не больше чем один цилиндр)
	   ES:BX => адрес буфера вызывающей программы
	   0:0078 => таблица параметров дискеты (для гибких дисков)
	   0:0104 => таблица параметров тв.диска (для твердых дисков)

	*/

	mov_AX_(0); // Не можем писать в ES напряимую тока через Рег
	mov_ES_AX(); // Адрес сегмента куда загружаем код
	mov_BX_(0x7E00); // Адрес внутри сегмента

	mov_DL_(0); // Читаем с диска А
	mov_DH_(0); // номер головки чтения/записи
	mov_CH_(0); // Номер дорожки (цилиндра)(0-n)
	mov_CL_(2); // Номер сектора
	mov_AL_(18); // Количество читаемых секторов
	mov_AH_(2); // Номер подпрограммы прерывания 13h
	int_(0x13); // Прерывание работа с диском

	Tr_Print("End load 18 sectors");
    Tr_Print("Init 32 bit mode");
  //Tr_Stop();
  //-----------;
  cli()        ; // Запрещаем прерывания 
  in_AL_(0x70) ; // Запрещаем NMI 
  or_AL_(0x80) ;
  out_AL_(0x70);
  //-----------;
  in_AL_(0x92) ;   
  or_AL_(2)    ; // Адресная линия A20   
  out_AL_(0x92);   
  //-----------;
  lgdt_(ADR_("GDT"));// Загрузка таблицы дискрипторов памяти  
  lidt_(ADR_("GDT"));// Загрузка таблицы дискрипторов прерываний
  //-----------;   
  mov_EAX_CR0();
  or_AL_(1)    ;
  mov_CR0_EAX();
  //-----------;
  jmp_32b(8,ADR_("32 Bit Start"));
  NOP_();   
  IncludeMyPrint();
  FUN_("32 Bit Start");
  G_PLA=PL_I32; // Выбираем платформу
  NOP_();
  // Загрузка селекторов 
  //;//---------------;
  mov_AX_(0x10);//mov ax, 10h       ;
  mov_DS_AX();//mov ds, ax
  mov_SS_AX();//mov ss, ax
  mov_ES_AX();//mov es, ax
  mov_SP_AX();//mov esp,2FFFFh;          
  mov_AX_(0x0);//mov ax, 0
  mov_FS_AX();//mov fs, ax
  mov_GS_AX();//mov gs, ax
  //;//---------------;  
                  
  Tr_Print32("32 bit mode Ok.");
  Tr_Stop();

  gdt();// Размещаме таблицу GDT

	G_MEM[510] = 0x55;
	G_MEM[511] = 0xaa;
}
void Create_IMA(uchar* G_MEM, int iSize, const char* iNam)
{
	// Записываем на диск
	// Записываем создайм файл образ диска
	FILE* fout = fopen(iNam, "wb");
	int cnt = 0;
	fseek(fout, 0, SEEK_SET); // Перемещаемся в начало файла
	do {
		fwrite(&G_MEM[cnt], 128, 1, fout); // Загружаем файл
		cnt = cnt + 128;
	} while (cnt < iSize);
	fclose(fout);
}
void Init()
{
	LAB_INIT();
}
int main()
{
	Init();
	// Гененрируем код
	G_ADR = 0;
	Loader(); // Первый проход
	printf("=====\r\n");
	G_ADR = 0;
	Loader(); // Второй проход
	printf("Compile Ok Size of %d!\n", G_ADR);
	Create_IMA(G_MEM, MAX_SIZE_MEM, "TimOs.ima");
}
