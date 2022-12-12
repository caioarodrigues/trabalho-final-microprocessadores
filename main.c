//definindo os tipos booleanos:
#define true 1
#define false 0

//definindo as variaveis entrada e saida, para nao se confundir ao configurar o micro
#define entrada 1
#define saida 0

//definindo as variaveis de estado, que serirao para controlar o jogo
#define iniciada 1 
#define aguardandoMediador 0
#define naoIniciada 2
// CONFIG1H
#pragma config FOSC = XT_XT     // Oscillator Selection bits (XT oscillator (XT))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = ON         // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = ON      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config ICPRT = OFF      // Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)

#include "lcd.h"
#include <stdio.h>

typedef int bool;
typedef int estado;

typedef struct {
    estado partida;
} estadoPartida;

typedef struct {
	int c1;
	int c2;
    int contagemGeral;
}contador;

contador inicializaContador(){
    contador c;
    c.c1 = 0;
    c.c2 = 0;
    c.contagemGeral = 0;
    
	return c;
}

bool inicializaTravaLed(){
    bool trava = false;
    
    return trava;
}

estadoPartida inicializaVariavelPartida(){
    estadoPartida _estadoPartida;
    
    _estadoPartida.partida = naoIniciada;
    
    return _estadoPartida;
}

bool inicializaVariavelMediador(){
    bool mediador = false;
    
    return mediador;
}

bool inicializaVariavelTravaContagem(){
    bool trava = false;
    
    return trava;
}

int zeraContagem(){
    return 0;
}

void putch(char data){
  escreve_lcd(data);   
}

void setConfiguracaoInicial(void){
    TRISCbits.RC0 = saida;     // RC0 como saída 
    TRISCbits.RC1 = saida;      //rc1 como saida
    TRISAbits.RA0 = saida;      //ra0 como saida
    PORTD = saida;
    TRISD = 0x00;
    inicializa_lcd();
    limpa_lcd();
}

void ligaBuzzer(void){
    PORTAbits.RA0 = true;
    __delay_ms(500);
    PORTAbits.RA0 = false;
}

void imprimeEstadoVariavelPartida(estadoPartida estadoDaPartida, bool travaLed, contador c){
    float c1 = (float) c.c1 / 1000;
    float c2 = (float) c.c2 / 1000;
    
    if(estadoDaPartida.partida == iniciada && travaLed){
        caracter_inicio(1, 0);
        if(c1 != 0)
            printf("J1 = %.2f s ", c1);
        else
            printf("Esperando J1 ");
        
        caracter_inicio(2, 0);
        if(c2 != 0)
            printf("J2 = %.2f s ", c2);
        else
            printf("Esperando J2 ");
    }
    if(estadoDaPartida.partida == naoIniciada && !travaLed && c.contagemGeral == 0 || estadoDaPartida.partida == aguardandoMediador){
        limpa_lcd();
    }
}

contador registraTempoDeApertoBotao(contador c, bool travaLed, estadoPartida ep){
    //se tiver um botao acionado, ele aciona o respectivo led
    
    if(ep.partida == iniciada){
        if(PORTBbits.RB1 && c.c2 == 0){
            c.c2 = c.contagemGeral;
            //jogador 2
            if(!travaLed)
                PORTCbits.RC1 = true;
        }
        else if(PORTBbits.RB0 && c.c1 == 0){
            c.c1 = c.contagemGeral;
            //jogador 1
            if(!travaLed)
                PORTCbits.RC0 = true;
        }
    }
    
    return c;
}

void apagaLeds(){
    PORTCbits.RC1 = false;
    PORTCbits.RC0 = false;   
}

int contaDezMSNoContadorGeral(contador cont){
    __delay_ms(10);
    
    cont.contagemGeral += 10;
    
    return cont.contagemGeral;
}

bool temAlgumLedAceso(){
    if (PORTCbits.RC1 || PORTCbits.RC0) return true;
    return false;
}

void main(void){
    contador cont = inicializaContador();
    bool travaLed = inicializaTravaLed();
    bool isMediadorAcionado = inicializaVariavelMediador();
    bool travaContagemGeral = inicializaVariavelTravaContagem();
    estadoPartida estadoDaPartida = inicializaVariavelPartida();

    setConfiguracaoInicial();
    
    while(true){
        imprimeEstadoVariavelPartida(estadoDaPartida, travaLed, cont);
        travaLed = temAlgumLedAceso();
        
        if(cont.c1 != 0 && cont.c2 != 0){
            //nao ha necessidade de deixar o cronometro rodando se os dois jogadores ja possuem seus 
            //respectivos timers
            travaContagemGeral = true;
        }
        if(estadoDaPartida.partida == naoIniciada && PORTBbits.RB2){
            /*esta eh a condicao para trocar o estado da partida de "nao iniciada" para "aguardando o mediador", 
             ou seja, basta que o estado seja "nao iniciada" e o botao rb2 ser pressionado. */
            estadoDaPartida.partida = aguardandoMediador;
        }
        if(PORTBbits.RB2 && !travaLed && !isMediadorAcionado && estadoDaPartida.partida == aguardandoMediador){
            /*condicao para iniciar a partida ^^^^^, se o botao rb2 for pressionado, se os leds nao estiverem 
             * travados, se o mediador nao tiver pressioado o botao para dar inicio a partida antes e se o 
             * estado da partida for aguardando pelo mediador.*/
            
            isMediadorAcionado = true;
            estadoDaPartida.partida = iniciada;
            travaContagemGeral = false;
            
            limpa_lcd();
            ligaBuzzer();
        }      
        if(PORTBbits.RB2 && travaLed && isMediadorAcionado && estadoDaPartida.partida == iniciada){
            /*aqui esta a condicao de reset da partida ^^^, ou seja, se o botao 3 (rb2) for pressionado
             *  + leds travados + o mediador ja tiver pressionado o botao e se a partida ja tiver sido iniciada. */
            
            estadoDaPartida.partida = naoIniciada;
            isMediadorAcionado = false;
            travaLed = false;
            travaContagemGeral = true;
            
            cont.contagemGeral = zeraContagem();
            cont.c1 = zeraContagem();
            cont.c2 = zeraContagem();
            
            __delay_ms(500);
            limpa_lcd();
            apagaLeds();
            
            continue;
        }
        if(!travaContagemGeral){
            /*O cronometro somente conta se a variavel de trava for false. Ou seja, nao ha necessidade de continuar
             cronometrando no estado "aguardando mediador", quando o reset de partida eh feito e nem quando 
             as variaveis c1 e c2, cujos os mesmos armazenam o tempo de resposta dos jogadores, sao diferente de 
             zero, igualmente.*/
            cont.contagemGeral = contaDezMSNoContadorGeral(cont);
            cont = registraTempoDeApertoBotao(cont, travaLed, estadoDaPartida); 
        }
    }
}

