#include "Utils.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
// Переводит из кодировки cp1251  cp866  
void  cp1251_cp866 (char* S) {
	 int i=0;
	 if (S!= NULL)
	 for (i=0;S[i]!=0;i++)
	 if  ( ((unsigned char)S[i]>=192)  &&  ((unsigned char)S[i]<=223)) S[i]=S[i]-64;else
	 if  ( ((unsigned char)S[i]>=224)  &&  ((unsigned char)S[i]<=239)) S[i]=S[i]-64;else
	 if  ( ((unsigned char)S[i]>=240)  &&  ((unsigned char)S[i]<=255)) S[i]=S[i]-16;else
	 if    ((unsigned char)S[i]==168)  S[i]=(unsigned char)240    ;else
	 if    ((unsigned char)S[i]==184)  S[i]=(unsigned char)241    ;
}
char* Tr_SumStr(char* iStr1,char* iStr2){ // Сложение строк   
	char *res=NULL;// Результирующая строка 
	int f=0 ;// Для циклов  
	int len1;// Длина первой строки 
	int len2;// Длина второй строки  
	f=0;
	len1=strlen(iStr1);
	len2=strlen(iStr2);
	res=(char*)malloc(len1+len2+1);
	for (f=0;iStr1[f]!=0;f++) res[f]=iStr1[f];
	for (f=0;iStr2[f]!=0;f++) res[len1+f]=iStr2[f];
	res[len1+len2]=0;   
	return res;
}
