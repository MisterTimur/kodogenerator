#include <stdio.h>
#include <stdlib.h>

#include "File_IMA.h"
#include "Loader.h"
#include "generator.h"

int main(int argc, char *argv[]) {
  Init();
  // Гененрируем код
  PC = 0;
  Loader(); // Первый проход
  printf("=====\r\n");
  PC = 0;
  Loader(); // Второй проход
  printf("Compile Ok Size of %d!\n", PC);
  Create_IMA(Program, MAX_SIZE_MEM, "TimOs.ima");
}
