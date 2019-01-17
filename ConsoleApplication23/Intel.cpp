#include "intel.h"
#include "generator.h"
// Команеды специфичные только для INTEL ===============

void cli(){ 
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0xFA;G_ADR=G_ADR+1;
     } 
	else if (G_PLA==PL_I32) {// Платформа 32бит 80386
     G_MEM[G_ADR]=0xFA;G_ADR=G_ADR+1;
     }
	else if (G_PLA==PL_I64) {// Платформа 64 бит 
     G_MEM[G_ADR]=0xFA;G_ADR=G_ADR+1;
     }
	else ERR(" ERR cli ");
}

void xor_EAX_EAX(){
     if (G_PLA==PL_I32) {// Платформа 32бит 80386
     G_MEM[G_ADR]=0x66;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0x31;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0xC0;G_ADR=G_ADR+1;
     }
	else if (G_PLA==PL_I64) {// Платформа 64 бит 
     G_MEM[G_ADR]=0x66;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0x31;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0xC0;G_ADR=G_ADR+1;
     }
	else ERR("xor_EAX_EAX"); 
}

 
void inc_DI_(){
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0x47;G_ADR=G_ADR+1;
     } else ERR("inc_DI_");
}
void inc_SI_(){
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0x46;G_ADR=G_ADR+1;
     } else ERR("inc_SI_");
}
void test_AL_AL_(){
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0x84;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0xC0;G_ADR=G_ADR+1;
     } else ERR("test_AL_AL");
}
void test_AX_AX_(){
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0x85;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0xC0;G_ADR=G_ADR+1;
     } else ERR("test_AX_AX");
}
void xor_AX_AX(){
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0x33;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0xC0;G_ADR=G_ADR+1;
     } else ERR("xor_AX_AX");
}
void mov_CS_AX(){
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     ERR("mov_CS_AX"); 
	 } 
	else if (G_PLA==PL_I32) {// Платформа 32бит 80386
	 G_MEM[G_ADR]=0x8E;G_ADR=G_ADR+1;
	 G_MEM[G_ADR]=0xC8;G_ADR=G_ADR+1;
     }
	else if (G_PLA==PL_I64) {// Платформа 64 бит 
     G_MEM[G_ADR]=0x8E;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0xC8;G_ADR=G_ADR+1;
     }
else ERR("mov_CS_AX");
}  
void mov_DS_AX(){
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086  
     G_MEM[G_ADR]=0x8E;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0xD8;G_ADR=G_ADR+1;
     } 
else if (G_PLA==PL_I32) {// Платформа 32бит 80386
     G_MEM[G_ADR]=0x8E;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0xD8;G_ADR=G_ADR+1;
     }
else if (G_PLA==PL_I64) {// Платформа 64 бит 
     G_MEM[G_ADR]=0x8E;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0xD8;G_ADR=G_ADR+1;
     }
else ERR("Ошибка такой команды в выбраной платформе не сущестукет ");



}
void mov_SS_AX(){
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0x8E;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0xD0;G_ADR=G_ADR+1;
     } 
else if (G_PLA==PL_I32) {// Платформа 32бит 80386
     G_MEM[G_ADR]=0x8E;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0xD0;G_ADR=G_ADR+1;
     }
else if (G_PLA==PL_I64) {// Платформа 64 бит 
     G_MEM[G_ADR]=0x8E;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0xD0;G_ADR=G_ADR+1;
     }
else ERR("Ошибка такой команды в выбраной платформе не сущестукет ");



}
void mov_ES_AX(){
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0x8E;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0xC0;G_ADR=G_ADR+1;
     } 
else if (G_PLA==PL_I32) {// Платформа 32бит 80386
     G_MEM[G_ADR]=0x8E;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0xC0;G_ADR=G_ADR+1;
     }
else if (G_PLA==PL_I64) {// Платформа 64 бит 
     G_MEM[G_ADR]=0x8E;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0xC0;G_ADR=G_ADR+1;
     }
else ERR("Ошибка такой команды в выбраной платформе не сущестукет ");



}
 
void int_    (unsigned char iNom){
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0xCD;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=iNom;G_ADR=G_ADR+1;
     } 
else if (G_PLA==PL_I32) {// Платформа 32бит 80386
     G_MEM[G_ADR]=0xCD;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=iNom;G_ADR=G_ADR+1;
     }
else if (G_PLA==PL_I64) {// Платформа 64 бит 
     G_MEM[G_ADR]=0xCD;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=iNom;G_ADR=G_ADR+1;
     }
else ERR("Ошибка такой команды в выбраной платформе не сущестукет ");



}
void mov_SP_ (unsigned short iNom){
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0xBC;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[0];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[1];G_ADR=G_ADR+1;
     } 
else ERR("mov_SP_"); 
}
void mov_ESP_(unsigned int iNom) {    
     if (G_PLA==PL_I32) { // Платформа 32бит 80386     
     G_MEM[G_ADR]=0xBC;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[0];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[1];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[2];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[3];G_ADR=G_ADR+1;
     }
else if (G_PLA==PL_I64) { // Платформа 64 бит    
     G_MEM[G_ADR]=0xBC;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[0];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[1];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[2];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[3];G_ADR=G_ADR+1;
     }
else ERR("mov_ESP_"); 
}

void mov_SI_(unsigned short iNom){
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0xBE;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[0];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[1];G_ADR=G_ADR+1;
     } else ERR("mov_SI_");    
}
void mov_DI_(unsigned short iNom){
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0xBF;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[0];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[1];G_ADR=G_ADR+1;
     } else ERR("mov_DI_");    
}
void mov_EDI_(unsigned int iNom){
     if (G_PLA==PL_I32) {// Платформа 32бит 80386     
     G_MEM[G_ADR]=0xBF;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[0];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[1];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[2];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[3];G_ADR=G_ADR+1;
     }
else if (G_PLA==PL_I64) {// Платформа 64 бит    
     G_MEM[G_ADR]=0xBF;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[0];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[1];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[2];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[3];G_ADR=G_ADR+1;
     }
else ERR("mov_EDI_");



}
void mov_BP_(unsigned short iNom){
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0xBD;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[0];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[1];G_ADR=G_ADR+1;
     } 
else if (G_PLA==PL_I32) {// Платформа 32бит 80386
     G_MEM[G_ADR]=0x66;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0xBD;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[0];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[1];G_ADR=G_ADR+1;
     }
else if (G_PLA==PL_I64) {// Платформа 64 бит 
     G_MEM[G_ADR]=0x66;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0xBD;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[0];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[1];G_ADR=G_ADR+1;
     }
else ERR("mov_BP_");
}
 
void mov_AX_(unsigned short iNom){
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0xB8;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[0];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[1];G_ADR=G_ADR+1;
     } 
else if (G_PLA==PL_I32) {// Платформа 32бит 80386
     G_MEM[G_ADR]=0x66;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0xB8;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[0];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[1];G_ADR=G_ADR+1;
     }
else if (G_PLA==PL_I64) {// Платформа 64 бит 
     G_MEM[G_ADR]=0x66;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0xB8;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[0];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[1];G_ADR=G_ADR+1;
     }
else ERR("Ошибка такой команды в выбраной платформе не сущестукет ");



}
void mov_BX_(unsigned short iNom){
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0xBB;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[0];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[1];G_ADR=G_ADR+1;
     } 
else if (G_PLA==PL_I32) {// Платформа 32бит 80386
     G_MEM[G_ADR]=0x66;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0xBB;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[0];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[1];G_ADR=G_ADR+1;
     }
else if (G_PLA==PL_I64) {// Платформа 64 бит 
     G_MEM[G_ADR]=0x66;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0xBB;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[0];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[1];G_ADR=G_ADR+1;
     }
else ERR("Ошибка такой команды в выбраной платформе не сущестукет ");



}
void mov_CX_(unsigned short iNom){
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0xB9;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[0];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[1];G_ADR=G_ADR+1;
     } 
else if (G_PLA==PL_I32) {// Платформа 32бит 80386
     G_MEM[G_ADR]=0x66;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0xB9;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[0];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[1];G_ADR=G_ADR+1;
     }
else if (G_PLA==PL_I64) {// Платформа 64 бит 
     G_MEM[G_ADR]=0x66;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0xB9;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[0];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[1];G_ADR=G_ADR+1;
     }
else ERR("mov_CX_");



}
      
void mov_AL_(unsigned char iNom){
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0xB0;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=iNom;G_ADR=G_ADR+1;
     } 
else if (G_PLA==PL_I32) {// Платформа 32бит 80386
     G_MEM[G_ADR]=0xB0;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=iNom;G_ADR=G_ADR+1;
     }
else if (G_PLA==PL_I64) {// Платформа 64 бит 
     G_MEM[G_ADR]=0xB0;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=iNom;G_ADR=G_ADR+1;
     }
else ERR("mov_AL_");
}
void mov_AH_(unsigned char iNom){
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0xB4;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=iNom;G_ADR=G_ADR+1;
     } 
else if (G_PLA==PL_I32) {// Платформа 32бит 80386
     G_MEM[G_ADR]=0xB4;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=iNom;G_ADR=G_ADR+1;
     }
else if (G_PLA==PL_I64) {// Платформа 64 бит 
     G_MEM[G_ADR]=0xB4;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=iNom;G_ADR=G_ADR+1;
     }
else ERR("mov_AH_");
}
void mov_BL_(unsigned char iNom){
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0xB3;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=iNom;G_ADR=G_ADR+1;
     } 
else if (G_PLA==PL_I32) {// Платформа 32бит 80386
     G_MEM[G_ADR]=0xB3;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=iNom;G_ADR=G_ADR+1;
     }
else if (G_PLA==PL_I64) {// Платформа 64 бит 
     G_MEM[G_ADR]=0xB3;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=iNom;G_ADR=G_ADR+1;
     }
else ERR("Ошибка такой команды в выбраной платформе не сущестукет ");



}
void mov_BH_(unsigned char iNom){
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0xB7;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=iNom;G_ADR=G_ADR+1;
     } 
else if (G_PLA==PL_I32) {// Платформа 32бит 80386
     G_MEM[G_ADR]=0xB7;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=iNom;G_ADR=G_ADR+1;
     }
else if (G_PLA==PL_I64) {// Платформа 64 бит 
     G_MEM[G_ADR]=0xB7;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=iNom;G_ADR=G_ADR+1;
     }
else ERR("Ошибка такой команды в выбраной платформе не сущестукет ");



}
void mov_DH_(unsigned char iNom){
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0xB6;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=iNom;G_ADR=G_ADR+1;
     } 
else if (G_PLA==PL_I32) {// Платформа 32бит 80386
     G_MEM[G_ADR]=0xB6;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=iNom;G_ADR=G_ADR+1;
     }
else if (G_PLA==PL_I64) {// Платформа 64 бит 
     G_MEM[G_ADR]=0xB6;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=iNom;G_ADR=G_ADR+1;
     }
else ERR("Ошибка такой команды в выбраной платформе не сущестукет ");



}
void mov_DL_(unsigned char iNom){
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0xB2;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=iNom;G_ADR=G_ADR+1;
     } 
else if (G_PLA==PL_I32) {// Платформа 32бит 80386
     G_MEM[G_ADR]=0xB2;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=iNom;G_ADR=G_ADR+1;
     }
else if (G_PLA==PL_I64) {// Платформа 64 бит 
     G_MEM[G_ADR]=0xB2;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=iNom;G_ADR=G_ADR+1;
     }
else ERR("Ошибка такой команды в выбраной платформе не сущестукет ");



}
void mov_CL_(unsigned char iNom){
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0xB1;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=iNom;G_ADR=G_ADR+1;
     } 
else if (G_PLA==PL_I32) {// Платформа 32бит 80386
     G_MEM[G_ADR]=0xB1;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=iNom;G_ADR=G_ADR+1;
     }
else if (G_PLA==PL_I64) {// Платформа 64 бит 
     G_MEM[G_ADR]=0xB1;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=iNom;G_ADR=G_ADR+1;
     }
else ERR("Ошибка такой команды в выбраной платформе не сущестукет ");



}
void mov_CH_(unsigned char iNom){
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0xB5;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=iNom;G_ADR=G_ADR+1;
     } 
else if (G_PLA==PL_I32) {// Платформа 32бит 80386
     G_MEM[G_ADR]=0xB5;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=iNom;G_ADR=G_ADR+1;
     }
else if (G_PLA==PL_I64) {// Платформа 64 бит 
     G_MEM[G_ADR]=0xB5;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=iNom;G_ADR=G_ADR+1;
     }
else ERR("mov_CH_");   
}

void mov_A_DI_AL() {  
     //  mov [di],al         
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0x88;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0x05;G_ADR=G_ADR+1;
     } 
else if (G_PLA==PL_I32) {// Платформа 32бит 80386
     G_MEM[G_ADR]=0x67;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0x88;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0x05;G_ADR=G_ADR+1;
     }                                 
else ERR("mov_A_DI_AL"); 
}
void mov_A_SI_AL() {  
     //  mov [di],al         
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0x88;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0x04;G_ADR=G_ADR+1;
     } 
else if (G_PLA==PL_I32) {// Платформа 32бит 80386
     G_MEM[G_ADR]=0x67;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0x88;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0x04;G_ADR=G_ADR+1;
     }                                 
else ERR("mov_A_SI_AL"); 
}
void mov_AL_A_DI() {  
     //  mov al,[di]         
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0x8A;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0x05;G_ADR=G_ADR+1;
     } 
else if (G_PLA==PL_I32) {// Платформа 32бит 80386
     G_MEM[G_ADR]=0x67;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0x8A;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0x05;G_ADR=G_ADR+1;
     }                                 
else ERR("mov_AL_A_DI"); 
}
void mov_AL_A_SI() {  
     //  mov al,[di]         
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0x8A;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0x04;G_ADR=G_ADR+1;
     } 
else if (G_PLA==PL_I32) {// Платформа 32бит 80386
     G_MEM[G_ADR]=0x67;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0x8A;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0x04;G_ADR=G_ADR+1;
     }                                 
else ERR("mov_AL_A_SI"); 
}


void mov_A_DI_AX(){
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0x89;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0x05;G_ADR=G_ADR+1;
     } 
else if (G_PLA==PL_I32) {// Платформа 32 бит 80386
     G_MEM[G_ADR]=0x67;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0x66;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0x89;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0x05;G_ADR=G_ADR+1;
     }    
else ERR("mov_A_DI_AX");
}

void mov_A_ES_DI_AL(){
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0x26;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0x88;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0x05;G_ADR=G_ADR+1; // 26 67 88 05   
     } 
else if (G_PLA==PL_I32) {// Платформа 32 бит 80386
     G_MEM[G_ADR]=0x26;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0x67;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0x88;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0x05;G_ADR=G_ADR+1;   
     }
else ERR("mov_A_ES_DI_AL");
}
void mov_A_ES_SI_AL(){
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0x26;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0x88;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0x04;G_ADR=G_ADR+1; // 26 67 88 05   
     } 
else if (G_PLA==PL_I32) {// Платформа 32 бит 80386
     G_MEM[G_ADR]=0x26;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0x67;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0x88;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0x04;G_ADR=G_ADR+1;   
     }
else ERR("mov_A_ES_SI_AL");
}

void jmp_byte(const char*iStr){

     unsigned int iNom=ADR_(iStr);  
     
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     char lAdr=iNom-(G_ADR+L_ADR+2);
     G_MEM[G_ADR]=0xEB;G_ADR=G_ADR+1;  
     G_MEM[G_ADR]=(char)(lAdr);G_ADR=G_ADR+1;
     } 
else if (G_PLA==PL_I32) {// Платформа 32бит 80386
     char lAdr=iNom-(G_ADR+L_ADR+2);
     G_MEM[G_ADR]=0xEB;G_ADR=G_ADR+1;  
     G_MEM[G_ADR]=(char)(lAdr);G_ADR=G_ADR+1;
     }
else if (G_PLA==PL_I64) {// Платформа 64 бит 
     char lAdr=iNom-(G_ADR+L_ADR+2);
     G_MEM[G_ADR]=0xEB;G_ADR=G_ADR+1;  
     G_MEM[G_ADR]=(char)(lAdr);G_ADR=G_ADR+1;
     }
else ERR("jmp_byte");   

}
void jz_byte(const char*iStr){

     unsigned int iNom=ADR_(iStr);  
     
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     char lAdr=iNom-(G_ADR+L_ADR+2);
     G_MEM[G_ADR]=0x74;G_ADR=G_ADR+1;  
     G_MEM[G_ADR]=(char)(lAdr);G_ADR=G_ADR+1;
     } 
else if (G_PLA==PL_I32) {// Платформа 32бит 80386
     char lAdr=iNom-(G_ADR+L_ADR+2);
     G_MEM[G_ADR]=0x74;G_ADR=G_ADR+1;  
     G_MEM[G_ADR]=(char)(lAdr);G_ADR=G_ADR+1;
     }
else if (G_PLA==PL_I64) {// Платформа 64 бит 
     char lAdr=iNom-(G_ADR+L_ADR+2);
     G_MEM[G_ADR]=0x74;G_ADR=G_ADR+1;  
     G_MEM[G_ADR]=(char)(lAdr);G_ADR=G_ADR+1;
     }
else ERR("jz_byte");   

}
void call_(const char*iStr){
     
     unsigned int iNom=ADR_(iStr);
     
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086   
     short lAdr=iNom-(G_ADR+L_ADR+3);        
     G_MEM[G_ADR]=0xE8;G_ADR=G_ADR+1;  
     G_MEM[G_ADR]=((char*)(&lAdr))[0];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((char*)(&lAdr))[1];G_ADR=G_ADR+1;
     } 
else if (G_PLA==PL_I32) {// Платформа 32бит 80386
     int lAdr=iNom-(G_ADR+L_ADR+5);  
     G_MEM[G_ADR]=0xE8;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((char*)(&lAdr))[0];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((char*)(&lAdr))[1];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((char*)(&lAdr))[2];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((char*)(&lAdr))[3];G_ADR=G_ADR+1;
     }
else if (G_PLA==PL_I64) {// Платформа 64 бит
     int lAdr=iNom-(G_ADR+L_ADR+5);    
     G_MEM[G_ADR]=0xE8;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((char*)(&lAdr))[0];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((char*)(&lAdr))[1];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((char*)(&lAdr))[2];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((char*)(&lAdr))[3];G_ADR=G_ADR+1;
     }
else ERR("call_");   

}
void ret_(){     
     
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0xC3;G_ADR=G_ADR+1;                        
     } 
else if (G_PLA==PL_I32) {// Платформа 32бит 80386
     G_MEM[G_ADR]=0xEB;G_ADR=G_ADR+1;                   
     }
else if (G_PLA==PL_I64) {// Платформа 64 бит 
     G_MEM[G_ADR]=0xEB;G_ADR=G_ADR+1;                 
     }
else ERR("ret_");   

}
