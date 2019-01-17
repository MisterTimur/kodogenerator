#pragma once

#define PL_I16 16 // 16 битный режим интел      
#define PL_I32 32 // 32 битный режим интел 
#define PL_I64 64 // 64 битный режим интел 

void NOP_();

void cli();

void xor_EAX_EAX();

void inc_DI_();

void inc_SI_();

void test_AL_AL_();

void test_AX_AX_();

void xor_AX_AX();

void mov_CS_AX();

void mov_DS_AX();

void mov_SS_AX();

void mov_ES_AX();

void int_(unsigned char iNom);

void mov_SP_(unsigned short iNom);

void mov_ESP_(unsigned int iNom);

void mov_SI_(unsigned short iNom);

void mov_DI_(unsigned short iNom);

void mov_EDI_(unsigned int iNom);

void mov_BP_(unsigned short iNom);

void mov_AX_(unsigned short iNom);

void mov_BX_(unsigned short iNom);

void mov_CX_(unsigned short iNom);

void mul_DL_();

void inc_DX_();

void mov_SI_AX_();

void add_AX_DX_();

void shl_DL_1_();

void mov_A_DX_(unsigned short iNom);

void mov_DX_(unsigned short iNom);
                 

void mov_DX_A_(unsigned short iNom);

void mov_AX_A_(unsigned short iNom);

void mov_SI_A_(unsigned short iNom);

void mov_AL_(unsigned char iNom);

void mov_AH_(unsigned char iNom);

void mov_BL_(unsigned char iNom);

void mov_BH_(unsigned char iNom);

void mov_DH_(unsigned char iNom);

void mov_DL_(unsigned char iNom);

void mov_CL_(unsigned char iNom);

void mov_CH_(unsigned char iNom);

void mov_A_DI_AL();

void mov_A_SI_AL();

void mov_AL_A_DI();

void mov_AL_A_SI();

void mov_A_DI_AX();

void mov_A_ES_DI_AL();

void mov_A_ES_SI_AL();

void jmp_byte(const char * iStr);

void jz_byte(const char * iStr);

void call_(const char * iStr);

void ret_();
