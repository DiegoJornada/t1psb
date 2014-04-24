#include "lcd.h"
int CONTROL = 0, RIGHT=0, WRONG=0;
int CP [] = {0,0,0,0,0,0,0,0,0,0};  
int CT [] = {0,0,0,0,0,0,0,0,0,0};  

void init(int *pswd);
int  play(int *pswd);
void set(int *arr,int index, int *ac);
void leds();
int howManyLeds(int n);
void verify(int *t, int *pswd);
void tryNumber(int l);
void pause();
void win();
int main(){
	 int password[] = {0, 0, 0, 0};

	 initTimer();

	 FIO4DIR = 0x0FF;
	 FIO4SET = 0xFF;

	 LCDinit();

	 LCDputs("##MASTER MIND!##");

	 LCDcomando(0xC0);
	 
	 init(password);
	 
	 LCDcomando(1);
	 LCDputs("##SENHA SALVA##");
	 LCDcomando(0xC0);
	 LCDputs("  SW5:CONTINUA  ");

	 pause();

	 LCDcomando(1);

	 if(play(password) <= 10) {
			LCDcomando(1);
			LCDputs("#Voce Ganhou!o/#");
	 		FIO4SET = 0XFF;
			win();

	 }else{
			FIO4SET = 0xFF;	
			LCDcomando(1);
			LCDputs("Voce Perdeu!:(");
	 }
	 LCDcomando(0xC0);
	 LCDputs("  SW5:REINICIA  ");

	 pause();

	 return 0;
}
int countZero(int *arr){
	 int i, count=0;
	for(i=0;i<4;i++)
		 if(arr[i]==0)
				count++;
	return count;
}
void init(int *pswd){
	 LCDputs("SENHA: 0000");
	 while(1){
			if(!(FIO4PIN & 0x100)) set(pswd, 0, CP);

			if(!(FIO4PIN & 0x200)) set(pswd, 1, CP); 

			if(!(FIO4PIN & 0x400)) set(pswd, 2, CP); 

			if(!(FIO4PIN & 0x800)) set(pswd, 3, CP);

			if(!(FIO4PIN & 0x1000) && countZero(pswd) < 2) break; 
			espera(100);
	 }
}

int play(int *pswd){
	 int try[] = {0,0,0,0};
	 int lives=1;
	 LCDputs("TENTATIVA #0");
	 LCDcomando(0xC0);
	 LCDputs("       0000");
	 while(lives < 11){
			tryNumber(lives);

			if(!(FIO4PIN & 0x100)) set(try, 0, CT);	

			if(!(FIO4PIN & 0x200)) set(try, 1, CT); 

			if(!(FIO4PIN & 0x400)) set(try, 2, CT);	

			if(!(FIO4PIN & 0x800)) set(try, 3, CT);	

			if(!(FIO4PIN & 0x1000) && countZero(try) < 2){
				 verify(try, pswd);
				 leds();
				 if(RIGHT == 4) break;
				 lives++;
			}  
			espera(100);
			leds();
	 }
	 return lives;
}
int next(int *ac, int v){
	 if(ac[v] == 0 ) return v;
	 v+=1;
	 if(v > 9) v=0;
	 /*LCDputchar('0' + v);*/
	 return next(ac,v);
}
void set(int *arr,int index, int *ac){
	 int val = arr[index];
	 /*LCDputchar('0' + v);*/
	 int n = next(ac, val);
	 ac[val] = 0;
	 ac[n] = 1;
	 if(arr[index] == 9){
			arr[index] = 0;
	 }else{
			arr[index] = n;
	 }
	 LCDcomando(0xC0 + (index+7));
	 LCDputchar('0' + arr[index]);
}
void leds(){
	 FIO4SET = 0xFF;
	 int on  = howManyLeds(RIGHT);
	 int bl  = 0x0;
	 if(CONTROL==0){
			bl  = howManyLeds(WRONG)>>RIGHT;
			CONTROL = 1;
	 }else{
			CONTROL = 0;
	 }
	 FIO4CLR = on|bl;
}

int howManyLeds(int n){
	 if(n == 4 ) return 0xF0;

	 else if(n == 3) return 0xE0;

	 else if(n == 2) return 0xC0;

	 else if(n == 1) return 0x80;

	 return 0x00;

}

void verify(int *t, int *pswd){
	 RIGHT = 0;
	 WRONG = 0;
	 
	 int m[] = {0, 0, 0, 0};
	 
	 if(t[0] == pswd[0]){
			RIGHT++;
			m[0] = 1;
	 }
	 if(t[1] == pswd[1]){
			RIGHT++;
			m[1]=1;
	 }
	 if(t[2] == pswd[2]){
			RIGHT++;
			m[2]=1;
	 }
	 if(t[3] == pswd[3]){
			RIGHT++;
			m[3]=1;
	 }

	 int i;
	 for(i=0 ; i<4; i++){
			int j;
			for(j=0;j<4;j++){
				 if(t[i] == pswd[j] && m[j] != 1){
						m[j] = 1;
						WRONG++;
						break;
				 }
			}
	 }
}

void tryNumber(int l){
	 LCDcomando(0x80 + 11);
	 if(l != 10) LCDputchar('0' + l);
	 else {
			LCDcomando(0x80 + 11);
			LCDputchar('0' + 1);
			LCDcomando(0x80 + 12);
			LCDputchar('0' + 0);
	 }
}

void pause(){
	 while(1){ 
			espera(100);
			if(!(FIO4PIN & 0x1000)) break;
	 }
}
void win(){
	 int i;
	 for(i=0; i<3; i++){
	 	FIO4CLR = 0XFF;
		espera(500);
	 	FIO4SET = 0XFF;
		espera(500);
	 }
}
void UNDEF_Routine(){
}

void SWI_Routine(){
}

void FIQ_Routine(){
}
