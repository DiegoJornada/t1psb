#include "lcd.h"
int CONTROL = 0, RIGHT=0, WRONG=0;

void init(int *pswd);
int  play(int *pswd);
void set(int *arr,int index);
void leds();
int howManyLeds(int n);
void verify(int *t, int *pswd);
void tryNumber(int l);
void pause();

int main(){
    int password[] = {0, 0, 0, 0};

    initTimer();

    FIO4DIR = 0x0FF;
    FIO4SET = 0xFF;

    LCDinit();

    LCDputs("##MASTER MIND!##");

    espera(500);
    LCDcomando(0xC0);

    init(password);

    LCDcomando(1);
    LCDputs(" #SENHA SALVA  ");
    LCDcomando(0xC0);
    LCDputs("  SW5:CONTINUA  ");

    pause();

    espera(1000);
    LCDcomando(1);

    if(play(password) < 10) {
        LCDcomando(1);
        LCDputs("#Voce Ganhou\o/#");
    }else{
        LCDcomando(1);
        LCDputs("Voce Perdeu!:(");
    }
    LCDcomando(0xC0);
    LCDputs("  SW5:REINICIA  ");

    pause();

    return 0;
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

int play(int *pswd){
    int try[] = {0,0,0,0};
    int lives=1;
    LCDputs("#0");
    LCDcomando(0xC0);
    LCDputs("       0000");
    while(lives < 11){
        tryNumber(lives);

        if(!(FIO4PIN & 0x100)) set(try,0);	

        if(!(FIO4PIN & 0x200)) set(try,1); 

        if(!(FIO4PIN & 0x400)) set(try,2);	

        if(!(FIO4PIN & 0x800)) set(try,3);	

        if(!(FIO4PIN & 0x1000)){
            verify(try, pswd);
            leds();
            if(RIGHT == 4) break;
            lives++;
        }  
        espera(150);
        leds();
    }
    return lives;
}
void set(int *arr,int index){
    if(arr[index] == 9) arr[index] = 0;

    else arr[index] = arr[index]+1;

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

    else if(n == 0) return 0x00;

}

void verify(int *t, int *pswd){
    RIGHT = 0;
    WRONG = 0;
    int i = 0;
    int m[] = {0, 0, 0, 0};
    for(i ; i<4; i++){
        int j=0;
        for(j;j<4;j++){
            if(t[i] == pswd[j] && m[j] != 1){
                if(i==j) RIGHT++;
                else WRONG++;
                m[j] = 1;
                break;
            }
        }
    }
}

void tryNumber(int l){
    LCDcomando(0x80 + 2);
    if(lives != 10) LCDputchar('0' + l);
    else {
        LCDcomando(0x80 + 1);
        LCDputchar('0' + 1);
        LCDcomando(0x80 + 2);
        LCDputchar('0' + 0);
    }
}

void pause(){
    while(1){ 
        espera(100);
        if(!(FIO4PIN & 0x1000)) break;
    }
}

void UNDEF_Routine(){
}

void SWI_Routine(){
}

void FIQ_Routine(){
}
