#pragma once
#define Max_Siz_Mem 1474560 
extern unsigned int  G_ADR;// ����� ��� ��������� � ������ G_MEM � ������ ������ 
extern unsigned char G_MEM[Max_Siz_Mem];// ������� ��� ���������

void Loader();
bool Init();
