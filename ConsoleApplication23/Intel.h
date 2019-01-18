#pragma once
#include "common.h"

#define PL_I16 16 // 16 битный режим интел
#define PL_I32 32 // 32 битный режим интел
#define PL_I64 64 // 64 битный режим интел

void movb(const char * reg, uchar value);

void movw(const char * reg, ushort value);

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

void int_(uchar value);

void in_AL_(uchar value);

void out_AL_(uchar value);

void or_AL_(uchar value);

void lgdt_(ushort value);

void lidt_(ushort value);

void mov_EAX_CR0();

void mov_CR0_EAX();

void jmp_32b(ushort value1, ushort value2);

void mov_ESP_(uint value);

void mov_EDI_(uint value);

void mul_DL_();

void inc_DX_();

void mov_SI_AX_();

void add_AX_DX_();

void shl_DL_1_();

void mov_A_DX_(ushort value);

void mov_DX_A_(ushort value);

void mov_AX_A_(ushort value);

void mov_SI_A_(ushort value);

void mov_A_DI_AL();

void mov_A_SI_AL();

void mov_AL_A_DI();

void mov_AL_A_SI();

void mov_A_DI_AX();

void mov_A_ES_DI_AL();

void mov_A_ES_SI_AL();

void jmp_byte(const char *str);

void jz_byte(const char *str);

void call_(const char *str);

void ret_();
