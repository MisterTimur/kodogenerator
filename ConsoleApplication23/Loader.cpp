#include "Loader.h"
#include "Intel.h"
#include "generator.h"

void VAR_WORD_(const char* iNam,unsigned short iNom) {
   LAB_(iNam);   
   DB_(((unsigned char*)&iNom)[0]);
   DB_(((unsigned char*)&iNom)[1]);
}
void VAR_BYTE_(const char* iNam,unsigned char iNom) {
   LAB_(iNam);   
   DB_(iNom);  
}


void Tr_Stop(){
LAB_("ZZZ");
NOP_();
jmp_byte("ZZZ");   
}
void Tr_Print(const char* iTex){

    FUN_("Tr_Print");  
    NOP_();
    mov_DI_(ADR_("lText"));
    call_("PRINT16");
    jmp_byte("NEX");
    LAB_("lText");             
    STR_(iTex);
    LAB_("NEX");   
    NOP_();
    FUN_("Tr_Print"); 
    
}
void Include_Tr_Print(){    

    // =============================================
    // подпрограмам вывода строки в консоль в 16 битном режиме 
    // В DS:DI должен быть адрес строки 

    FUN_("PRINT16")       ;// Обьявляем новую область   
    mov_AX_(0xB800)       ;// mov ax,B800  Видеопамять 
    mov_ES_AX()           ;// mov es,ax    в ES   
    
    
    mov_AX_A_(ADR_("CURR_Y"));
    mov_DL_(160)             ;
    mul_DL_()                ;   
    mov_DX_A_(ADR_("CURR_X"));
    shl_DL_1_()              ;
    add_AX_DX_()             ;
    mov_SI_AX_()             ;  
 
    LAB_("Cikl")          ;
    mov_AL_A_DI()         ;// mov al,[di]           
    test_AL_AL_()         ;// test al,al
    jz_byte("EX")         ;// jz EX      
    mov_A_ES_SI_AL()      ;// mov [ES:DI],AL Выводим сивмол на экран 
    inc_SI_()             ;// inc Si
    mov_AL_(0x0F)         ;
    mov_A_ES_SI_AL()      ;// mov [ES:DI],AL Выводим атрибуты сивмол на экран 
    inc_SI_()             ;// inc Si
    inc_DI_()             ;// inc di
    jmp_byte("Cikl")      ;// jmp cikl

    LAB_("EX")            ;
    
    mov_DX_A_(ADR_("CURR_Y"));   // Переход на след строку 
    inc_DX_()                ;
    mov_A_DX_(ADR_("CURR_Y"));
    mov_DX_(0)               ;
    mov_A_DX_(ADR_("CURR_X"));
    
    ret_()                ;  
    VAR_WORD_("CURR_X",0) ;
    VAR_WORD_("CURR_Y",0) ;

}
void Loader() {
                                    
    PLA_(PL_I16); // Выбираем платформу 
    ORG_(0x7C00); // Устанавливаем адрес работы программы 
    FUN_("")    ; // Устанавливаем глобальную область видимости для меток                                             
    // Устанавливаем сегментные регистры ===========
    xor_AX_AX(); // Обнуляем содержимое регистра AX
    mov_SS_AX(); // Устанавлиавем Сегмент стека 0 
    mov_DS_AX(); // Устанавлиавем Сегмент данных 0 
    mov_ES_AX(); // Устанавлиавем Сегмент Доп сег фиг зн зачем он нужен  0 
    mov_SP_(0xFFFF);
    // =============================================  
 
    // =============================================
    // Выбираем видео режим 
    mov_AH_(0)  ; // ПОдпрограмма установики  видео режима 
    mov_AL_(3)  ; // текст    80x25    16/8           CGA,EGA  b800  Comp,RGB,Enhanced
    int_(0x10)  ; // Прерывание 10h
    
                                   
    // Выбираем страницу 
    mov_AH_(5)  ; // ПОдпрограмма выбора активной видео страницы  
    mov_AL_(0)  ; // Видео страница 0 
    int_(0x10)  ; // Прерывание 10h
     
    Tr_Print("Start Ok");  
                         
    // Прячем курсор 
    mov_AH_(2)  ; // ПОдпрограмма установки курсора  
    mov_BH_(0)  ; // Видео страница 
    mov_DH_(25) ; // Номер строки установка в 25 делет невидимым курсор  
    mov_DL_(0)  ; // Колонка 
    int_(0x10)  ; // Прерывание 10h

    // =============================================
    Tr_Print("Start load 18 sectors");
   
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
    int_(0x13)     ; // Прерывание работа с диском 

    Tr_Print("End load 18 sectors");       

    Tr_Stop();             
                    
    Include_Tr_Print();                   
       
    // ==================================== 
    // Всякие данные для программы                           

    //STL_("Hello world")   ; 
    //STL_("Start Ok")      ;
    //STL_("Start load 18 sectors")      ;
    //STL_("End load 18 sectors")      ;
 

    
    // ==================================== 
    G_MEM[510]=0x55; 
    G_MEM[511]=0xaa;

}

