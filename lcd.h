#ifndef LCD_H
#define LCD_H

#include <arch/nxp/lpc23xx.h>

#define CCLK 12000000

// Defines para bits de controle do LCD
#define LCD_E	(1<<24)
#define LCD_RS	(1<<25)

void espera(unsigned int t);
void LCDcomando(int c);
void LCDputchar(int c);
void LCDinit(void);
void LCDputs(char *txt);
void initTimer();

#endif
