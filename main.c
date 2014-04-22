

#include "lcd.h"
int CONTROL = 0, RIGHT=0, WRONG=0;

void set(int *arr,int index);
void verify(int *t, int *pswd);
void init(int *pswd);
void leds();
int  play(int *pswd);

int main(){
		int password[] = {0, 0, 0, 0};

		initTimer();

		FIO4DIR = 0x0FF;
		FIO4SET = 0xFF;

		LCDinit();

		LCDputs("##MASTER MIND!##");

		espera(500);
		LCDcomando(0xc0);

		init(password);

		LCDcomando(1);
		LCDputs("SENHA SALVA");
		espera(500);
		LCDcomando(1);


		if(play(password) < 10) {
				LCDcomando(1);
				LCDputs("#Voce Ganhou!!#");
		}else{
				LCDcomando(1);
				LCDputs("Voce Perdeu!:(");
		}

		espera(4000);
		return 0;
}

void set(int *arr,int index){
		if(arr[index] == 9) arr[index] = 0;

		else arr[index] = arr[index]+1;

		LCDcomando(0xC0 + (index+7));
		LCDputchar('0' + arr[index]);
}
int ledAux(int n){
		if(n == 4 )					return 0xF0;

		else if(n == 3) return 0xE0;

		else if(n == 2) return 0xC0;

		else if(n == 1) return 0x80;
		
		else if(n == 0) return 0x00;

}
void leds(){
		FIO4SET = 0xFF;
	 int on = ledAux(RIGHT);
		int bl = 0x0;
		if(CONTROL==0){
			 bl = ledAux(WRONG)>>RIGHT;
				CONTROL = 1;
		}else{
				CONTROL = 0;
		}
				FIO4CLR = on|bl;
		/*
		Se m==1				FIO4CLR = on | b; m = 0
		Senão						FIO4CLR = on m =1;
		*/
}

void verify(int *t, int *pswd){
		int i= 0;
		for(i ; i<4; i++){
				int j=0;
				for(j ; j<4;j++){
						if(t[i] == pswd[j]){
								if(i==j) RIGHT++;

								else WRONG++;

								break;
						}
				}
		}
}

void init(int *pswd){
		LCDputs("SENHA: 0000");
		while(1){
				if(!(FIO4PIN & 0x100)) set(pswd,0);

				if(!(FIO4PIN & 0x200)) set(pswd,1); 

				if(!(FIO4PIN & 0x400)) set(pswd,2); 

				if(!(FIO4PIN & 0x800)) set(pswd,3);

				if(!(FIO4PIN & 0x1000)) break; 
				espera(150);
		}
}

/*
			a=111000
			b=000010
			fio4pin=a|fio4pin^br
	*/

int play(int *pswd){
		int try[] = {0,0,0,0};
		int lives=0;
		LCDputchar('#');
		LCDcomando(0xC0);
		LCDputs("       0000");
		while(lives < 10){
				LCDcomando(0x80 + 1);
				LCDputchar('0' + lives);
				if(!(FIO4PIN & 0x100)) set(try,0);	

				if(!(FIO4PIN & 0x200)) set(try,1); 

				if(!(FIO4PIN & 0x400)) set(try,2);	

				if(!(FIO4PIN & 0x800)) set(try,3);	

				if(!(FIO4PIN & 0x1000)){
						RIGHT = WRONG = 0;
						verify(try, pswd);
						if(RIGHT == 4) break;
						lives++;
				}  
						espera(150);
						leds();
		}
		return lives;
}

void UNDEF_Routine(){
}

void SWI_Routine(){
}

void FIQ_Routine(){
}
