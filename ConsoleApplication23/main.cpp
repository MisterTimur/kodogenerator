#include <stdio.h>
#include <stdlib.h>
#include "generator.h"

int main()
{   
	Init();
	// ����������� ��� 
	G_ADR=0;
	Loader();
	G_ADR=0;
	Loader();
	// ���������� �� ����                           
	// ���������� ������� ���� ����� ����� 
	FILE * Tr_File = fopen("TimOs.ima","wb"); 
	int kol=0;
	fseek(Tr_File, 0, SEEK_SET);// ������������ � ������ ����� 
	do{                                     
	fwrite(&G_MEM[kol], 128, 1, Tr_File);// ��������� ����
	kol=kol+128;                         
	} while (kol<Max_Siz_Mem);      
	fclose(Tr_File);  
	printf("Compile Ok Size of %d!\n",G_ADR);
}