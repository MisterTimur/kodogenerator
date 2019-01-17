#pragma once
#include "common.h"
#include <stdbool.h>

#define MAX_SIZE_MEM 1024*1440
extern uint PC; // ����� ��� ��������� � ������ G_MEM � ������ ������
extern uchar Program[MAX_SIZE_MEM]; // ������� ��� ���������
extern uint Platform;
extern uint BaseAddres;

bool Init();

uint ADR_(const char *iNam);

void LAB_(const char *iStr);

void FUN_(const char *iStr);

bool LAB_INIT();

void SetPlatform(int iPla);

void ORG_(uint iAdr);

void ERR(const char *iStr);

void STR_(const char *iStr);

void STL_(const char *iStr);

void DB_(uchar iNom);
