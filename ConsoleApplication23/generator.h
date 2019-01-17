#pragma once

#include "common.h"
#include <stdbool.h>

#define MAX_SIZE_MEM 1024*1440
extern uint PC; // Адрес где находимся в масиве G_MEM в данный момент
extern uchar Program[MAX_SIZE_MEM]; // Готовый код программы
extern uint Platform;
extern uint BaseAddres;

bool Init();

uint ADR_(const char *name);

void LAB_(const char *str);

void FUN_(const char *str);

bool LAB_INIT();

void SetPlatform(int platform);

void ORG_(uint addr);

void ERR(const char *str);

void STR_(const char *str);

void STL_(const char *str);

void DB_(uchar value);
