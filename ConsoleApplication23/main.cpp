#include <stdio.h>
#include <stdlib.h>
#include "generator.h"
#include "Loader.h"

int main()
{   
	Init();
	// ����������� ��� 
	G_ADR=0;Loader();// ������ ������ 
	G_ADR=0;Loader();// ������ ������     
    printf("Compile Ok Size of %d!\n",G_ADR);
    Create_IMA("TimOs.ima");

}