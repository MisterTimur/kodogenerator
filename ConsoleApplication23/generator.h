#pragma once
#define Max_Siz_Mem 1474560 
extern unsigned int  G_ADR;// Адрес где находимся в масиве G_MEM в данный момент 
extern unsigned char G_MEM[Max_Siz_Mem];// Готовый код программы
extern unsigned int  G_PLA;
extern unsigned int  L_ADR;

 
bool Init();

unsigned int ADR_(const char * iNam);

void LAB_(const char * iStr);

void FUN_(const char * iStr);

bool LAB_INIT();

void PLA_(int iPla);

void ORG_(unsigned int iAdr);

void ERR(const char * iStr);

void STR_(const char * iStr);

void STL_(const char * iStr);

void DB_(unsigned char iNom);
