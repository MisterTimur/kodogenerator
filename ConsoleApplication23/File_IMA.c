#include "File_IMA.h"
#include <stdio.h>

void Create_IMA(uchar *G_MEM, int iSize, const char *iNam) {

  // Записываем на диск
  // Записываем создайм файл образ диска
  FILE *Tr_File = fopen(iNam, "wb");
  int kol = 0;
  fseek(Tr_File, 0, SEEK_SET); // Перемещаемся в начало файла
  do {
    fwrite(&G_MEM[kol], 128, 1, Tr_File); // Загружаем файл
    kol = kol + 128;
  } while (kol < iSize);
  fclose(Tr_File);
}
