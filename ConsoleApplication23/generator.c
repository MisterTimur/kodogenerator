// ConsoleApplication23.cpp : Этот файл содержит функцию "main". Здесь
// начинается и заканчивается выполнение программы.
//
//
// Кодегенератор
// Абдулов Тимур 2019 год
//

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Intel.h"
#include "Utils.h"
#include "common.h"
#include "generator.h"

/*	Подавление ошибки C4996 */
#define strdup _strdup

#pragma region =================================== Переменные .

int Platform = PL_I16;		// Глобальаня переменая выбора платформы
uint PC = 0;	// Адрес где находимся в масиве G_MEM в данный момент
uint BaseAddres = 0;		// Базовый адрес
// Адрес в ходе выполнения программы = BaseAddres + ProgramCounter
uchar Program[MAX_SIZE_MEM]; // Готовый код программы
char *Labels [MAX_SIZE_MEM]; // Списко меток

#pragma endregion
#pragma region =================================== Метки .

uint ADR_(const char *name) { // Возвращает адрес метки

  int res = -1;

  // ПОиск локальной метки =================================================
  // Двигаемся вниз по коду пока не встретим глобальную метку
  // либо конец программы либо не найдем
  int i = PC;
  while ((res == -1)           // ПОка не нашли метку
         && (i < MAX_SIZE_MEM) // Пока не дошли до конца программы
         &&
         ((Labels[i] == NULL) || (Labels[i][0] == '@'))) // пока это локальная метка
    if ((Labels[i] != NULL) && (strcmp(name, (char *)&(Labels[i][1])) == 0))
      res = i;
    else
      i = i + 1;
  // Двигаемся верх по коду пока не встретим глобальную метку
  // либо начало программы либо не найдем
  i = PC;
  while ((res == -1) // ПОка не нашли метку
         && (i >= 0) // Пока не дошли до конца программы
         &&
         ((Labels[i] == NULL) || (Labels[i][0] == '@'))) // пока это локальная метка
    if ((Labels[i] != NULL) && (strcmp(name, (char *)&(Labels[i][1])) == 0))
      res = i;
    else
      i = i - 1;
  // ПОиск Глобальной метки =================================================
  // Двигаемся вниз по коду пока не встретим
  // конец программы либо не найдем метку
  i = PC;
  while ((res == -1)            // ПОка не нашли метку
         && (i < MAX_SIZE_MEM)) // Пока не дошли до конца программы
    if ((Labels[i] != NULL) && (strcmp(name, Labels[i]) == 0))
      res = i;
    else
      i = i + 1;
  // Двигаемся верх по коду пока не встретим
  // начало программы либо не найдем метку
  i = PC;
  while ((res == -1)  // ПОка не нашли метку
         && (i >= 0)) // Пока не дошли до конца программы
    if ((Labels[i] != NULL) && (strcmp(name, Labels[i]) == 0))
      res = i;
    else
      i = i - 1;

  printf(" %s %d \r\n", name, res);
  return res + BaseAddres;
}
void LAB_(const char *str) { // Создает ЛОкальную Метку

  Labels[PC] = StrCat(strdup("@"), strdup(str));
}
void FUN_(const char *str) { // Создает глобальную метку

  Labels[PC] = strdup(str);
}
bool LAB_INIT() {
  int f = 0;
  for (f = 0; f < MAX_SIZE_MEM; f++)
    Labels[f] = NULL;
  return true;
}

#pragma endregion
#pragma region =================================== Метки 2.

// Просто соединение строк... Это уже было где-то ранее
void SumStr(char *s1, const char *s2, int *l) {
  int i = 0;
  while (s2[i] != 0)
    s1[*l + i] = s2[i++];
  *l = *l + i;
  s1[*l] = 0;
}
// Просто замена части строки
void StrPartReplace(char *s1, const char *s2, int l) {
  int i = 0;
  while (s2[i] != 0)
    s1[l + i] = s2[i++];
}
// Переводит целое число в строку
void IntToStr(char *bfr, int bfrLen, uint n) {
  uint b = n;
  int l = bfrLen - 1;
  bfr[l] = '\0';
  while (l-- > 0) {
    bfr[l] = 48 + b % 10;
    b = b / 10;
  }
}

typedef struct lab lab;
struct lab {          // Структура метки
  char labelName[25]; // Имя метки
  int adress;         // Адрес, по которому метка находится
  bool TrueAdress; // Если истина, то адрес указывает на ранее объявленную метку
  lab *next;       // Ссылка на слудющую метку с уникальным именем
  lab *up;         // Ссылка на следующую метку с тем же именем
};
lab FirstLabel; // Начало списка меток
lab *LastLabel =
    &FirstLabel; // Конец списка меток (чтобы было удобнее добавлять их в конец)
int LabelError = 0; // Если значение этой переменной не будет равно нулю, значит
                    // в коде есть не объявленная метка
// Добавляет метку в список
void MakeLabel(lab *l) {
  lab *CurLab = malloc(sizeof(lab));      // Создаём новый элемент
  //TODO: добавить проверку CurLab на равенство NULL
  CurLab->up = NULL;          // Инициализация переменной
  CurLab->next = NULL;        // Инициализация переменной
  CurLab->TrueAdress = false; // Инициализация переменной
  CurLab->adress = PC;     // Запоминаем адрес метки
  if (l == NULL) { // Если имя метки встечается первый раз, то её необходимо
                   // добавить в общий список
    LastLabel->next = CurLab; // Корректируем адрес следующей метки в текущей
                              // последней метке с уникальным именем
    LastLabel = CurLab;       // Устанавливаем новую метку как последнюю
  } else {          // Иначе добавляем её в список меток с тем же именем
    l->up = CurLab; // Привязываем её к списку меток с тем же именем
  }
}
// Определяет метки, на которые надо будет "перемещаться"
void JumpTo(const char *LabelName) {
  lab *Labels = FirstLabel.next; // Переключаемся на первую настоящую метку
  bool LabelIsExist =
      false; // Станет true, если метка будет найде в общем спике
  while (Labels != NULL) { // Обход всего списка меток с уникальными именами                                                                                                                   
		/*
		Если будет найдена метка с заданным именем, то необходимо будет проверить
		является ли она ранее объявленной. Для этого происходит проверка переменной TrueAdress
		на истинность. Если её значение = ложь, то это означает, что метка ещё не была объявлена,
		А если же она была объявлена ранее, то в "код" просто записывается её адрес
		и происходит принудительный выход из процедуры.
		*/

    if (strcmp(Labels->labelName, LabelName) ==
        0) { // Если в списке есть метка с указанным именем, то
      if (Labels->TrueAdress) { // Если она содержит нужный адрес, то
        char bfr[5];
        bfr[4] = 0; // Буфер для хранения результата преобразования числа в
                    // строку (для наглядности работы)
        IntToStr(bfr, 5, Labels->adress); // Преобразование числа в строку
        SumStr((char *)&Program, bfr,
               (int *)&PC); // Добавление этой строки в "код"
        return;                // Больше здесь делать нечего
      }
      LabelIsExist =
          true; // метка найдена, то очивидно, что она не была объявлена ранее
      break;    // прерываем цикл, чтобы в переменной Labels осталась ссылка на
                // нужную метку
    }
    Labels = Labels->next; // Переход к следующей метке
  }
  if (LabelIsExist) { // Если метка с тем же именем уже встречалась ранее
    while (Labels->up !=
           NULL) {         // Перемещаемся в конец списка меток с тем же именем
      Labels = Labels->up; // Перемещение далее по списку
    }
    MakeLabel(Labels); // И кладём её на этот список
  } else { // Иначе создаём такую метку и добавляем её в общий список
    MakeLabel(NULL);
    strcpy(LastLabel->labelName, LabelName); // Записываем её имя
  }
  SumStr((char *)&Program, "0000",
         (int *)&PC); // Пока что в "коде" на месте метки будут нули
  LabelError++;          // Метка есть, но она не объявлена
}
// Устанавливает метку в коде
void SetLabel(const char *LabelName) {
  lab *Labels = FirstLabel.next; // Переключаемся на первую настоящую метку
  lab *LabCur = NULL;            // "Корень" меток с тем же именем
  while (Labels != NULL) {       // Обход всего списка
    if (strcmp(Labels->labelName, LabelName) ==
        0) {       // Если в списке есть метка с таким именем, то
      char bfr[5]; // Буфер для хранения адреса в виде текста
      IntToStr(bfr, 5,
               PC); // Преобразование числа в строку (для наглядности)
      LabCur =
          Labels; // Запоминаем адрес начала списка меток, имеющих такое имя
      while (Labels != NULL) { // Заменяем все ранее встреченные метки с
                               // заданным именем на нужный адрес
        StrPartReplace((char *)&Program, bfr,
                       Labels->adress); // Замена части "кода"
        Labels = Labels->up; // Переход к следующей метке с тем же именем
        LabelError--; // Одна из меток была заменена на нужный адрес, поэтому
                      // счётчик "ошибка" надо уменьшить на еденицу
      }
      LabCur->adress = PC; // Теперь корневая метка с указанным именем будет
                              // содержать нужный адрес
      LabCur->TrueAdress = true; // Помечаем этот адрес как истинный, на который
                                 // будут осуществляться "передоды"
      // И удаляем оставшиеся метки с таким же именем из памяти
      Labels = LabCur->up; // Переключаемся на первый удаляемый элемент
      (*LabCur).up = NULL; // Обнуление переменной "следующая метка с таким же
                           // именем", так как они все будут удалены
      while (Labels != NULL) { // Пока они ещё существуют
        LabCur = Labels; // Запоминаем адрес переменной, которую нужно удалить
        Labels = Labels->up; // Переходим к следующей переменной, пока есть
                             // такая возможность
        free(LabCur);       // Удаление переменной из памяти
      }
      return; // Делать в этой процедуре больше нечего
    }
    Labels = Labels->next; // Переход к следующей метке
  }
  if (LabCur == NULL) { // Встретилась метка, на которую ранее не было переходов
    MakeLabel(NULL);    // Значит такую метку надо создать
    // Эта метка была добавлена в конец списка меток. Поэтому сейчас она
    // хранится в переменной LastLabel
    strcpy(LastLabel->labelName, LabelName); // Записываем её имя
    LastLabel->TrueAdress = true; // Эта метка содержит адрес, на который надо
                                  // будет заменять другие метки с тем же именем
  }
}
uint ADR2_(const char *name) { // Возвращает адрес метки

  int res = -1;

  // ПОиск локальной метки =================================================
  // Двигаемся вниз по коду пока не встретим глобальную метку
  // либо конец программы либо не найдем
  int f = PC;
  while ((res == -1)           // ПОка не нашли метку
         && (f < MAX_SIZE_MEM) // Пока не дошли до конца программы
         &&
         ((Labels[f] == NULL) || (Labels[f][0] == '@'))) // пока это локальная метка
    if ((Labels[f] != NULL) && (strcmp(name, (char *)&(Labels[f][1])) == 0))
      res = f;
    else
      f = f + 1;
  // Двигаемся верх по коду пока не встретим глобальную метку
  // либо начало программы либо не найдем
  f = PC;
  while ((res == -1) // ПОка не нашли метку
         && (f >= 0) // Пока не дошли до конца программы
         &&
         ((Labels[f] == NULL) || (Labels[f][0] == '@'))) // пока это локальная метка
    if ((Labels[f] != NULL) && (strcmp(name, (char *)&(Labels[f][1])) == 0))
      res = f;
    else
      f = f - 1;
  // ПОиск Глобальной метки =================================================
  // Двигаемся вниз по коду пока не встретим
  // конец программы либо не найдем метку
  f = PC;
  while ((res == -1)            // ПОка не нашли метку
         && (f < MAX_SIZE_MEM)) // Пока не дошли до конца программы
    if ((Labels[f] != NULL) && (strcmp(name, Labels[f]) == 0))
      res = f;
    else
      f = f + 1;
  // Двигаемся верх по коду пока не встретим
  // начало программы либо не найдем метку
  f = PC;
  while ((res == -1)  // ПОка не нашли метку
         && (f >= 0)) // Пока не дошли до конца программы
    if ((Labels[f] != NULL) && (strcmp(name, Labels[f]) == 0))
      res = f;
    else
      f = f - 1;

  printf(" %s %d \r\n", name, res);
  return res + BaseAddres;
}
void LAB2_(const char *str) { // Создает ЛОкальную Метку

  Labels[PC] = StrCat(strdup("@"), strdup(str));
}
void FUN2_(const char *str) { // Создает глобальную метку

  Labels[PC] = strdup(str);
}
bool LAB2_INIT() {
  int f = 0;
  for (f = 0; f < MAX_SIZE_MEM; f++)
    Labels[f] = NULL;
  return true;
}

#pragma endregion
#pragma region =================================== Крос АСМ .

// Универсальные для всех платформ =====================

void SetPlatform(int platform) { // Выбор платформы
  Platform = platform;
}
void ORG_(uint addr) { // Устанавлвиает базовый адрес размещения кода
  BaseAddres = addr;
}
void ERR(const char *str) { // Это типа ошибка компидяции
  char *lEr = (char *)strdup(str);
  // cp1251_cp866(lEr);
  printf("%s", str);
  exit(0);
}
void STR_(const char *str) { // Распологает строку в памяти

  int f = 0;
  for (f = 0; str[f] != 0; f++) {
    Program[PC] = str[f];
    PC = PC + 1;
  }
  Program[PC] = 0;
  PC = PC + 1;
}
void STL_(const char *str) {
  // Создает Метку и строку одинаковые
  LAB_(str);
  STR_(str);
}

void DB_(uchar value) { // Размещает 1 байт
  Program[PC++] = value;
}
void DW_(ushort value) { // Размещает 2 байт
     Program[PC++] = ((uchar *)&value)[0];
	 Program[PC++] = ((uchar *)&value)[1];
}
void DD_(uint value) { // Размещает 2 байт
     Program[PC++] = ((uchar *)&value)[0];
	 Program[PC++] = ((uchar *)&value)[1];
	 Program[PC++] = ((uchar *)&value)[2];
	 Program[PC++] = ((uchar *)&value)[3];
}

void db_(uchar value) { // Размещает 1 байт
  Program[PC++] = value;
}
void dw_(ushort value) { // Размещает 2 байт
     Program[PC++] = ((uchar *)&value)[0];
	 Program[PC++] = ((uchar *)&value)[1];
}
void dd_(uint value) { // Размещает 2 байт
     Program[PC++] = ((uchar *)&value)[0];
	 Program[PC++] = ((uchar *)&value)[1];
	 Program[PC++] = ((uchar *)&value)[2];
	 Program[PC++] = ((uchar *)&value)[3];
}


#pragma endregion
#pragma region =================================== Инициализация .
bool Init() {
  LAB_INIT();
  return true;
}
#pragma endregion
