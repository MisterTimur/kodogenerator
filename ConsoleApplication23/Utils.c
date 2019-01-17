#include "Utils.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "common.h"

// Переводит из кодировки cp1251  cp866
void cp1251_cp866(char *str) {
	int i = 0;

	if (str != NULL)
		for (i = 0; str[i] != 0; i++)
			if (((uchar)str[i] >= 192) && ((uchar)str[i] <= 223))
				str[i] = str[i] - 64;
			else if (((uchar)str[i] >= 224) && ((uchar)str[i] <= 239))
				str[i] = str[i] - 64;
			else if (((uchar)str[i] >= 240) && ((uchar)str[i] <= 255))
				str[i] = str[i] - 16;
			else if ((uchar)str[i] == 168)
				str[i] = (uchar)240;
			else if ((uchar)str[i] == 184)
				str[i] = (uchar)241;
}

char *StrCat(char *str1, char *str2) { // Сложение строк
	char *res = NULL; // Результирующая строка
	size_t len1;      // Длина первой строки
	size_t len2;      // Длина второй строки

	len1 = strlen(str1);
	len2 = strlen(str2);
	if ((res = (char *)malloc(len1 + len2 + 1)) != NULL)
		sprintf(res, "%s%s", str1, str2);
	return res;
}


