// ConsoleApplication23.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"       
#include <string.h> //
#include <stdlib.h> // Для СИ Компиляции 
#include <stdio.h>  // Для СИ Компиляции 
#include <conio.h>  // Для _getch();   ))))
#pragma warning(disable : 4996) //  Это для  VS си++

const int PL_I16=16; // 16 битный режим интел 
const int PL_I32=32; // 32 битный режим интел 
const int PL_I64=64; // 64 битный режим интел     
const int PL_Z80=80; // Процесор Z80
const int Max_Siz_Mem=1474560;//1474560;// Размер 3.5 диска  

unsigned int  G_PLA=PL_I16;// Глобальаня переменая выбора платформы 
unsigned int  G_ADR=0;// Указатель куда будут транслироваться команды 
unsigned int  L_ADR=0;// Адрес где будет распологаться программа при выполнениии  
unsigned char G_MEM[Max_Siz_Mem];// Готовый код программы 

 
// Переводит из кодировки cp1251  cp866  
void cp1251_cp866 (char* S) {
 int i=0;
 if (S!= NULL)
 for (i=0;S[i]!=0;i++)
 if  ( ((unsigned char)S[i]>=192)  &&  ((unsigned char)S[i]<=223)) S[i]=S[i]-64;else
 if  ( ((unsigned char)S[i]>=224)  &&  ((unsigned char)S[i]<=239)) S[i]=S[i]-64;else
 if  ( ((unsigned char)S[i]>=240)  &&  ((unsigned char)S[i]<=255)) S[i]=S[i]-16;else
 if    ((unsigned char)S[i]==168)  S[i]=(unsigned char)240    ;else
 if    ((unsigned char)S[i]==184)  S[i]=(unsigned char)241    ;
}

typedef struct S_LAB {
  char *NAM;// Название метки 
  unsigned int ADR;// Адрес рапсоложения  
  S_LAB*NEX;// Следующая метка   
} S_LAB;

S_LAB*LABS;

// Универсальные для всех платформ =====================
void PLA_(int iPla) { // Выбор платформы 
    G_PLA=iPla;
}
void ORG_(unsigned int  iAdr) { // Устанавлвиает адрес размещения кода 
     L_ADR=iAdr;
}
void ERR(const char*iStr){
char*lEr=(char*)strdup(iStr);
//cp1251_cp866(lEr);
printf("%s",iStr);
exit(0);
}   
unsigned int ADR_(const char*iNam) { // Возвращает адрес метки  
 unsigned int res=0;
 S_LAB *cur_lab = LABS; // начинаем с первой метки в списке  
 bool ex=false;// Флаг выхода 
 while ((cur_lab != NULL)&&(ex==false))// Перебираем метки 
 if  (strcmp(iNam, cur_lab->NAM)==0) 
      ex=true; else // Если имя совпадает завершаем цикл 
      cur_lab = cur_lab->NEX;// Переходим к следующей переменной 
 if (cur_lab!=NULL) res=cur_lab->ADR;  
 return res;
}     
void STR_(const char*iStr) { // Распологает строку в памяти 
     
     int f=0;
     for (f=0;iStr[f]!=0;f++){
     G_MEM[G_ADR]=iStr[f];G_ADR=G_ADR+1;
     }
     G_MEM[G_ADR]=0;G_ADR=G_ADR+1;

}     
void LAB_(const char*iStr) { // Создает Метку Label

 S_LAB *new_lab=(S_LAB*)malloc(sizeof(S_LAB));   
 new_lab->NAM=strdup(iStr);// Запоминаем имя метки 
 new_lab->ADR=G_ADR+L_ADR;// Запоминаем адрес метки 
 new_lab->NEX=LABS;
 LABS=new_lab;

}                   
void DB_(unsigned char iNom){
     G_MEM[G_ADR]=iNom;G_ADR=G_ADR+1;
}
 

 

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
void xor_AX_AX(){
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0x33;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0xC0;G_ADR=G_ADR+1;
     } 
else if (G_PLA==PL_I32) {// Платформа 32бит 80386
     G_MEM[G_ADR]=0x66;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0x31;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0xC0;G_ADR=G_ADR+1;
     }
else if (G_PLA==PL_I64) {// Платформа 64 бит 
     G_MEM[G_ADR]=0x66;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0x31;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0xC0;G_ADR=G_ADR+1;
     }
else ERR("xor_AX_AX");


}
void mov_CS_AX(){
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     ERR("Ошибка такой команды в выбраной платформе не сущестукет ");
     G_MEM[G_ADR]=0x8E;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0xC8;G_ADR=G_ADR+1;
     } 
else if (G_PLA==PL_I32) {// Платформа 32бит 80386
     G_MEM[G_ADR]=0x8E;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0xC8;G_ADR=G_ADR+1;
     }
else if (G_PLA==PL_I64) {// Платформа 64 бит 
     G_MEM[G_ADR]=0x8E;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0xC8;G_ADR=G_ADR+1;
     }
else ERR("Ошибка такой команды в выбраной платформе не сущестукет ");



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
void int_(unsigned char iNom){
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
void mov_SP_(unsigned short iNom){
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0xBC;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[0];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[1];G_ADR=G_ADR+1;
     } 
else if (G_PLA==PL_I32) {// Платформа 32бит 80386     
     G_MEM[G_ADR]=0xBC;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[0];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[1];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[2];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[3];G_ADR=G_ADR+1;
     }
else if (G_PLA==PL_I64) {// Платформа 64 бит    
     G_MEM[G_ADR]=0xBC;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[0];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[1];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[2];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[3];G_ADR=G_ADR+1;
     }
else ERR("Ошибка такой команды в выбраной платформе не сущестукет ");



}
void mov_DI_(unsigned short iNom){
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0xBF;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[0];G_ADR=G_ADR+1;
     G_MEM[G_ADR]=((unsigned char*)&iNom)[1];G_ADR=G_ADR+1;
     } 
else if (G_PLA==PL_I32) {// Платформа 32бит 80386     
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
else ERR("Ошибка такой команды в выбраной платформе не сущестукет ");



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
else ERR("Ошибка такой команды в выбраной платформе не сущестукет ");



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
else ERR("Ошибка такой команды в выбраной платформе не сущестукет ");



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
else ERR("Ошибка такой команды в выбраной платформе не сущестукет ");



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
else ERR("Ошибка такой команды в выбраной платформе не сущестукет ");



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
else ERR("Ошибка такой команды в выбраной платформе не сущестукет ");



}
void mov_A_DI_AL(){
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0x88;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0x07;G_ADR=G_ADR+1;
     } 
else if (G_PLA==PL_I32) {// Платформа 32бит 80386
     G_MEM[G_ADR]=0x88;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0x07;G_ADR=G_ADR+1;
     }
else if (G_PLA==PL_I64) {// Платформа 64 бит 
     G_MEM[G_ADR]=0x88;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0x07;G_ADR=G_ADR+1;
     }                                 
else ERR("Ошибка такой команды mov_A_ED_ в выбраной платформе не сущестукет ");



}
void mov_A_DI_AX(){
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0x89;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0x05;G_ADR=G_ADR+1;
     } 
else ERR("Ошибка такой команды mov_A_ED_ в выбраной платформе не сущестукет ");
}
void mov_A_ES_DI_AL(){
     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0x26;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0x88;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=0x05;G_ADR=G_ADR+1;
     } 
else ERR("Ошибка такой команды mov_A_ED_ в выбраной платформе не сущестукет ");
}

void jmp_byte(unsigned int iNom){
  
     //if ((iNom-G_ADR+1>127)||(iNom-G_ADR-1<-127))
     //ERR("Не верное использование команды jmp_byte"); 
     

     if (G_PLA==PL_I16) {// Платформа 16 бит 8086
     G_MEM[G_ADR]=0xEB;G_ADR=G_ADR+1;  
     G_MEM[G_ADR]=(char)(iNom-G_ADR+L_ADR+1);G_ADR=G_ADR+1;
     } 
else if (G_PLA==PL_I32) {// Платформа 32бит 80386
     G_MEM[G_ADR]=0xEB;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=(char)(iNom-G_ADR+1);G_ADR=G_ADR+1;
     }
else if (G_PLA==PL_I64) {// Платформа 64 бит 
     G_MEM[G_ADR]=0xEB;G_ADR=G_ADR+1;
     G_MEM[G_ADR]=(char)(iNom-G_ADR+1);G_ADR=G_ADR+1;
     }
else ERR("Ошибка такой команды в выбраной платформе не сущестукет ");



}

// =====================================================

void MOV_A_(int c){



};


                
void Loader() {
                                    
    PLA_(PL_I16); // Выбираем платформу 
    ORG_(0x7C00); // Устанавливаем адрес работы программы 
                                                 
    // Устанавливаем сегментные регистры ===========
    xor_AX_AX(); // Обнуляем содержимое регистра AX
    mov_SS_AX(); // Устанавлиавем Сегмент стека 0 
    mov_DS_AX(); // Устанавлиавем Сегмент данных 0 
    mov_ES_AX(); // Устанавлиавем Сегмент Доп сег фиг зн зачем он нужен  0 
    mov_SP_(0xFFFF);
    // =============================================   


    mov_AX_(0xB800);
    mov_ES_AX();  
    mov_DI_(10);
    mov_AL_('T');
    mov_A_ES_DI_AL();   
    mov_DI_(11);
    mov_AL_(0xFF);
    mov_A_ES_DI_AL();   

    DB_(0xEB);
    DB_(0xFE);


 
    /*

    --- ----------------------------------------------------------------------------
    13H писать строку ¦AT¦  EGA  Выдает строку в позиции курсора. символы 0dH
    (CarRet), 0aH (LineFeed), 08H (backspace) и 07H (Beep) трактуются как
    команды управления и не высвечиваются.
    вход:   ES:BP => выводимая строка (спецформат для AL=2 и AL=3)
            CX = длина строки (подсчитываются только символы)
            DH,DL = строка,колонка начала вывода
            BH = номер страницы
            AL = код подфункции:
                 0 = использовать атрибут в BL; не трогать курсор
                 1 = использовать атрибут в BL; курсор - в конец строки
                 2 = формат строки: char,attr, char,attr...; не трогать курсор
                 3 = формат строки: char,attr, char,attr...; передвинуть курсор
    --------------------------------------------------------------------------------

    */
                 
    //mov_BP_(ADR_("Hello world"));// Указываю адрес строки 
    //mov_CX_(11)  ;// Длина строки 
    //mov_DH_(15)  ;// Номер строки на экране куда выводим  
    //mov_DL_(15)  ;// Номер колонки  
    //mov_BH_(0)   ;// Номер страницы 
    //mov_BL_(0xFF);// Цвет фона вывода и Шрифта     
    //mov_AH_(0x13);// Использовать атрибут в BL; курсор - в конец строки
    //mov_AL_(2)   ;// Использовать атрибут в BL; курсор - в конец строки
    //int_(0x10)   ;// Вывод строки в консоль  13h
    //DB_(0xEB);
    //DB_(0xFE);
    
    
     
    // =============================================
    // Выбираем видео режим 
    mov_AH_(0)  ; // ПОдпрограмма установики  видео режима 
    mov_AL_(3)  ; // текст    80x25    16/8           CGA,EGA  b800  Comp,RGB,Enhanced
    int_(0x10)  ; // Прерывание 10h
    
                                   
    // Выбираем страницу 
    mov_AH_(5)  ; // ПОдпрограмма выбора активной видео страницы  
    mov_AL_(0)  ; // Видео страница 0 
    int_(0x10)  ; // Прерывание 10h

    // Прячем курсор 
    mov_AH_(2)  ; // ПОдпрограмма установки курсора  
    mov_BH_(0)  ; // Видео страница 
    mov_DH_(25) ; // Номер строки установка в 25 делет невидимым курсор  
    mov_DL_(0)  ; // Колонка 
    int_(0x10)  ; // Прерывание 10h

    // =============================================
    
    
    // =============================================

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

    mov_AX_(0)     ; // Не можем писать в ES напряимую тока через Рег 
    mov_ES_AX      ; // Адрес сегмента куда загружаем код
    mov_BX_(0x7E00); // Адрес внутри сегмента 

    mov_DL_(0)     ; // Читаем с диска А
    mov_DH_(0)     ; // номер головки чтения/записи
    mov_CH_(0)     ; // Номер дорожки (цилиндра)(0-n) 
    mov_CL_(2)     ; // Номер сектора
    mov_AL_(18)    ; // Количество читаемых секторов 
    mov_AH_(2)     ; // Номер подпрограммы прерывания 13h 
    int_(0x13)     ; // 

    // =============================================

  
    LAB_("Hello world");// Узнаем что за адрес тут в коде 
    STR_("Hello world");// Размещаем текст в памяти 
  

    //ORG_(510);//Загрузочная сигнатура  
    //G_ADR=510;
    //DB_(0x55);
    //DB_(0xAA);
    G_MEM[510]=0x55; 
    G_MEM[511]=0xaa;

}

int main()
{




                           //               100 101 102
    //unsigned int A1=102;   // JMP 100       COD ADR 000
    //unsigned int A2=100;
    //char c=A2-A1;
    //printf("%x",c);
    //_getch();


 // Инициализация структуры для хранения меток 
 S_LAB *LABS=(S_LAB*)malloc(sizeof(S_LAB));
 LABS->ADR=0;// Создаем метку с адресом 0 
 LABS->NAM=strdup("START");// Создаем метку с адресом 0 
 LABS->NEX=NULL;//  

 // Гененрируем код 
 G_ADR=0;
 Loader();
 G_ADR=0;
 Loader();
 // Записываем на диск                           
 // Записываем создайм файл образ диска 
 FILE * Tr_File = fopen("TimOs.ima","wb"); 
 int kol=0;
 fseek(Tr_File, 0, SEEK_SET);// Перемещаемся в начало файла 
 do{                                     
 fwrite(&G_MEM[kol], 128, 1, Tr_File);// Загружаем файл
 kol=kol+128;                         
 } while (kol<Max_Siz_Mem);      
 fclose(Tr_File);  
 printf("Hello World!\n");
    

}

 