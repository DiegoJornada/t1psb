#include "lcd.h"

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
	else if(on == 3){
		FIO4CLR = 0xE0;
	}
	else if(on == 2){
		FIO4CLR = 0xC0;
	}
	else if(on == 1){
		FIO4CLR = 0x80;
	}
	return 0;
}
int verify(int *t, int *pswd){
	int right=0;
	int wrong=0;
	int i= 0;
	for(i ; i<4 ; i++){
		if(t[i] == pswd[i]) right++;
	}
	i = 0 ;
	int aux = 0;
	if(right < 4){
	for(i ; i<4; i++){
		int j=0;
		for(j ; j<4;i++){
			if(t[i] == pswd[j]){
				aux++;
				break;
			}
		}
	}
	wrong = aux - right;
	}
	return leds(right, wrong);
}
int main(){
	int password[] = {0, 0, 0, 0};

	int try[] = {0 ,0 ,0 ,0};

	int *t = &try;
	int lives = 0;

	initTimer();

	FIO4DIR = 0x0FF;		/* LED1 como saida */
	FIO4SET = 0xFF;
	LCDinit();
	LCDputs("##MASTER MIND!##");
	espera(500);
	LCDcomando(0xc0);
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
	LCDcomando(1);
	LCDputs("SENHA SALVA");
	espera(500);
	LCDcomando(1);
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
			int  v = verify(t,&password);
			if(v == 1) break;
			
			lives++;
		}  
	}
	espera(500);
	LCDcomando(1);
	LCDputs("FIM!!!");

	espera(4000);
	return 0;
}



void UNDEF_Routine(){
}

void SWI_Routine(){
}

void FIQ_Routine(){
}
