#include "lcd.h"

void set(int *arr,int index);
int leds(int on, int blink);
int verify(int *t, int *pswd);
void init(void);
void play(void);

int main(){
	int password[] = {0, 0, 0, 0};
	int try[] = {0 ,0 ,0 ,0};

	initTimer();

	FIO4DIR = 0x0FF;
	FIO4SET = 0xFF;

	LCDinit();

	LCDputs("##MASTER MIND!##");
	espera(500);
	LCDcomando(0xc0);

	init();

	LCDcomando(1);
	LCDputs("SENHA SALVA");
	espera(500);

	if(play() < 10) LCDputs("You Win!");
	else LCDputs("You Loose");

	LCDcomando(1);
	espera(500);
	LCDcomando(1);

	return 0;
}

void set(int *arr,int index){
	if(arr[index] == 9) arr[index] = 0;
	else arr[index] = arr[index]+1;
	LCDcomando(0xC0 + (index+7));
	LCDputchar('0' + arr[index]);
	espera(200);
}

int leds(int on, int blink){
	if(on == 4 ){ 
		FIO4CLR = 0xF0;
		return 1;
	}
	else if(on == 3)	FIO4CLR = 0xE0;

	else if(on == 2)	FIO4CLR = 0xC0;

	else if(on == 1)	FIO4CLR = 0x80;

	return 0;
}

int verify(int *t, int *pswd){
	int right=0;
	int wrong=0;
	int i= 0;
	int aux = 0;
	if(right < 4){
		for(i ; i<4; i++){
			int j=0;
			for(j ; j<4;i++){
				if(t[i] == pswd[j]){
					if(i==j) right++
					else wrong++;
					break;
				}
			}
		}
	}
	return leds(right, wrong);
}

void init(void){
	LCDputs("SENHA: 0000");
	while(1){
		if(!(FIO4PIN & 0x100)){
			set(&password,0);
		} 
		if(!(FIO4PIN & 0x200)) {
			set(&password,1);	
		} 
		if(!(FIO4PIN & 0x400)) {
			set(&password,2);	
		} 
		if(!(FIO4PIN & 0x800)) {
			set(&password,3);	
		} 
		if(!(FIO4PIN & 0x1000)) break; 
	}
}
int play(void){
	int lives=0;
	LCDputchar('#');
	LCDcomando(0xC0);
	LCDputs("       0000");
	while(lives < 10){
		LCDcomando(0x80 + 1);
		LCDputchar('0' + lives);
		if(!(FIO4PIN & 0x100)){
			set(t,0);	
		} 
		if(!(FIO4PIN & 0x200)) {
			set(t,1);	
		} 
		if(!(FIO4PIN & 0x400)) {
			set(t,2);	
		} 
		if(!(FIO4PIN & 0x800)) {
			set(t,3);	
		} 
		if(!(FIO4PIN & 0x1000)){
			espera(300);
			if(verify(t,&password) == 1) break;
			lives++;
		}  
	}
	return lives;
}

void UNDEF_Routine(){
}

void SWI_Routine(){
}

void FIQ_Routine(){
}
