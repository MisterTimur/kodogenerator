#include "File_IMA.h"
#include <stdio.h>

void Create_IMA(uchar *memory, int size, const char *name) {

  // Записываем на диск
  // Записываем создайм файл образ диска
  FILE *fout = fopen(name, "wb");
  int cnt = 0;
  fseek(fout, 0, SEEK_SET); // Перемещаемся в начало файла
  do {
    fwrite(&memory[cnt], 128, 1, fout); // Загружаем файл
    cnt = cnt + 128;
  } while (cnt < size);
  fclose(fout);
}
