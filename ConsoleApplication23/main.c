#include <stdio.h>
#include <stdlib.h>

#include "File_IMA.h"
#include "Loader.h"
#include "generator.h"

int main() {
  Init();
  // ����������� ���
  G_ADR = 0;
  Loader(); // ������ ������
  printf("=====\r\n");
  G_ADR = 0;
  Loader(); // ������ ������
  printf("Compile Ok Size of %d!\n", G_ADR);
  Create_IMA(G_MEM, MAX_SIZE_MEM, "TimOs.ima");
}
