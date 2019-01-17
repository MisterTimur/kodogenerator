#include <stdio.h>
#include <stdlib.h>
#include "generator.h"
#include "Loader.h"
#include "File_IMA.h"
int main()
{   
	Init();
	// Гененрируем код 
	G_ADR=0;Loader();// Первый проход 
	G_ADR=0;Loader();// Второй проход     
    printf("Compile Ok Size of %d!\n",G_ADR);
    Create_IMA(G_MEM,Max_Siz_Mem,"TimOs.ima");

}