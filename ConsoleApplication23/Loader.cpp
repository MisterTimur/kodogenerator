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
    // ������������ ������ ������ � ������� � 16 ������ ������ 
    // � DS:DI ������ ���� ����� ������ 

    FUN_("PRINT16")       ;// ��������� ����� �������   
    mov_AX_(0xB800)       ;// mov ax,B800  ����������� 
    mov_ES_AX()           ;// mov es,ax    � ES   
    
    
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
    mov_A_ES_SI_AL()      ;// mov [ES:DI],AL ������� ������ �� ����� 
    inc_SI_()             ;// inc Si
    mov_AL_(0x0F)         ;
    mov_A_ES_SI_AL()      ;// mov [ES:DI],AL ������� �������� ������ �� ����� 
    inc_SI_()             ;// inc Si
    inc_DI_()             ;// inc di
    jmp_byte("Cikl")      ;// jmp cikl

    LAB_("EX")            ;
    
    mov_DX_A_(ADR_("CURR_Y"));   // ������� �� ���� ������ 
    inc_DX_()                ;
    mov_A_DX_(ADR_("CURR_Y"));
    mov_DX_(0)               ;
    mov_A_DX_(ADR_("CURR_X"));
    
    ret_()                ;  
    VAR_WORD_("CURR_X",0) ;
    VAR_WORD_("CURR_Y",0) ;

}
void Loader() {
                                    
    PLA_(PL_I16); // �������� ��������� 
    ORG_(0x7C00); // ������������� ����� ������ ��������� 
    FUN_("")    ; // ������������� ���������� ������� ��������� ��� �����                                             
    // ������������� ���������� �������� ===========
    xor_AX_AX(); // �������� ���������� �������� AX
    mov_SS_AX(); // ������������� ������� ����� 0 
    mov_DS_AX(); // ������������� ������� ������ 0 
    mov_ES_AX(); // ������������� ������� ��� ��� ��� �� ����� �� �����  0 
    mov_SP_(0xFFFF);
    // =============================================  
 
    // =============================================
    // �������� ����� ����� 
    mov_AH_(0)  ; // ������������ ����������  ����� ������ 
    mov_AL_(3)  ; // �����    80x25    16/8           CGA,EGA  b800  Comp,RGB,Enhanced
    int_(0x10)  ; // ���������� 10h
    
                                   
    // �������� �������� 
    mov_AH_(5)  ; // ������������ ������ �������� ����� ��������  
    mov_AL_(0)  ; // ����� �������� 0 
    int_(0x10)  ; // ���������� 10h
     
    Tr_Print("Start Ok");  
                         
    // ������ ������ 
    mov_AH_(2)  ; // ������������ ��������� �������  
    mov_BH_(0)  ; // ����� �������� 
    mov_DH_(25) ; // ����� ������ ��������� � 25 ����� ��������� ������  
    mov_DL_(0)  ; // ������� 
    int_(0x10)  ; // ���������� 10h

    // =============================================
    Tr_Print("Start load 18 sectors");
   
    // �������� ���������� ����� ��������� � �����
    /* �������� http://www.codenet.ru/progr/dos/int_0012.php
    
    02H ������ �������
     ����: DL = ����� ����� (0=���� A...; 80H=��.���� 0; 81H=��.���� 1)
           DH = ����� ������� ������/������
           CH = ����� ������� (��������)(0-n) =�
           CL = ����� ������� (1-n) ===========�== ��. ��������� ����.
           AL = ����� �������� (� ����� �� ������ ��� ���� �������)
           ES:BX => ����� ������ ���������� ���������
           0:0078 => ������� ���������� ������� (��� ������ ������)
           0:0104 => ������� ���������� ��.����� (��� ������� ������)
    
    */
   
    mov_AX_(0)     ; // �� ����� ������ � ES ��������� ���� ����� ��� 
    mov_ES_AX      ; // ����� �������� ���� ��������� ���
    mov_BX_(0x7E00); // ����� ������ �������� 

    mov_DL_(0)     ; // ������ � ����� �
    mov_DH_(0)     ; // ����� ������� ������/������
    mov_CH_(0)     ; // ����� ������� (��������)(0-n) 
    mov_CL_(2)     ; // ����� �������
    mov_AL_(18)    ; // ���������� �������� �������� 
    mov_AH_(2)     ; // ����� ������������ ���������� 13h 
    int_(0x13)     ; // ���������� ������ � ������ 

    Tr_Print("End load 18 sectors");       

    Tr_Stop();             
                    
    Include_Tr_Print();                   
       
    // ==================================== 
    // ������ ������ ��� ���������                           

    //STL_("Hello world")   ; 
    //STL_("Start Ok")      ;
    //STL_("Start load 18 sectors")      ;
    //STL_("End load 18 sectors")      ;
 

    
    // ==================================== 
    G_MEM[510]=0x55; 
    G_MEM[511]=0xaa;

}

