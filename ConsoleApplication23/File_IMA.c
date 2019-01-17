#include "File_IMA.h"
#include <stdio.h>

void Create_IMA(uchar *memory, int size, const char *name) {

  // ���������� �� ����
  // ���������� ������� ���� ����� �����
  FILE *fout = fopen(name, "wb");
  int cnt = 0;
  fseek(fout, 0, SEEK_SET); // ������������ � ������ �����
  do {
    fwrite(&memory[cnt], 128, 1, fout); // ��������� ����
    cnt = cnt + 128;
  } while (cnt < size);
  fclose(fout);
}
