#pragma once
#include "common.h"

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

void int_(uchar iNom);

void mov_SP_(ushort iNom);

void mov_ESP_(uint iNom);

void mov_SI_(ushort iNom);

void mov_DI_(ushort iNom);

void mov_EDI_(uint iNom);

void mov_BP_(ushort iNom);

void mov_AX_(ushort iNom);

void mov_BX_(ushort iNom);

void mov_CX_(ushort iNom);

void mul_DL_();

void inc_DX_();

void mov_SI_AX_();

void add_AX_DX_();

void shl_DL_1_();

void mov_A_DX_(ushort iNom);

void mov_DX_(ushort iNom);

void mov_DX_A_(ushort iNom);

void mov_AX_A_(ushort iNom);

void mov_SI_A_(ushort iNom);

void mov_AL_(uchar iNom);

void mov_AH_(uchar iNom);

void mov_BL_(uchar iNom);

void mov_BH_(uchar iNom);

void mov_DH_(uchar iNom);

void mov_DL_(uchar iNom);

void mov_CL_(uchar iNom);

void mov_CH_(uchar iNom);

void mov_A_DI_AL();

void mov_A_SI_AL();

void mov_AL_A_DI();

void mov_AL_A_SI();

void mov_A_DI_AX();

void mov_A_ES_DI_AL();

void mov_A_ES_SI_AL();

void jmp_byte(const char *iStr);

void jz_byte(const char *iStr);

void call_(const char *iStr);

void ret_();
