#include "lcd.h"

void espera(unsigned int t)
{
		unsigned int tf;
		tf = T0TC + t;		// tf = Valor futuro do T0TC
		while (tf != T0TC);		// espera ate que tf==T0TC
}

// Escreve um comando para o LCD
void LCDcomando(int c)
{
		FIO3PIN0 = c;
		FIO4CLR = LCD_RS;		// RS=0: comando
		FIO4SET = LCD_E;
		FIO4CLR = LCD_E;
		espera(20);
}

// Escreve um caractere no LCD
void LCDputchar(int c)
{
		FIO3PIN0 = c;
		FIO4SET = LCD_RS;		// RS=1: caractere
		FIO4SET = LCD_E;
		FIO4CLR = LCD_E;
		espera(8);
}

// Configura LCD
void LCDinit(void)
{
		// Configura portas I/O do LCD
		FIO3DIR |= 0xff;		// Dados do LCD como saidas
		FIO4DIR |= LCD_E | LCD_RS;	// EN e RS do LCD como saidas
		espera(20);
		LCDcomando(0x38);		// Configura LCD para 2 linhas
		LCDcomando(1);		// Limpa display
		LCDcomando(0x0c);		// Apaga cursor
}

// Envia uma mensagem no LCD
void LCDputs(char *txt)
{
		while (*txt)
				LCDputchar(*txt++);
}

void initTimer()
{
		PCONP |= 2;			// Liga energia do Timer 0
		PCLKSEL0 = (PCLKSEL0 & (~0x0c)) | 0x04;	// Divide CCLK por 1 no T0
		T0TCR = 0;			// Desabilita T0
		T0PR = CCLK / 1000 - 1;	// Incrementa T0TC 1000 vezes por segundo
		T0TCR = 2;			// Inicializa T0
		T0TCR = 1;			// Habilita T0
}

