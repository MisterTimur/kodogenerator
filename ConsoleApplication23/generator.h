#pragma once
#define Max_Siz_Mem 1474560 
extern unsigned int  G_ADR;// Адрес где находимся в масиве G_MEM в данный момент 
extern unsigned char G_MEM[Max_Siz_Mem];// Готовый код программы

void Loader();
bool Init();
