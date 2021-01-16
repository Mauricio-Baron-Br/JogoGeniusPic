#define s0   RA0_bit
#define s1   RA1_bit
#define s2   RA2_bit
#define s3   RA3_bit
#define led0 RB0_bit
#define led1 RB1_bit
#define led2 RB2_bit
#define led3 RB3_bit

int led_on(int cor);    // ligar leds

int mem[40], botao = 4, sort = 2, stagio = 0, aux = 0, i;

void main() 
{
     CMCON = 7;     //desabilita comparadores
     TRISA = 0b0001111; //15
     PORTA = 0b0001111; //15
     TRISB = 0;
     PORTB = 0;
     
     Sound_Init(&PORTB, 4);
     sound_play(2000, 100);led0 = 1;
     sound_play(1000, 100);led1 = 1;
     sound_play(1120, 100);led2 = 1;
     sound_play(1330, 100);led3 = 1;
     sound_play(1590, 100);led_on(4); //desligar todos os leds
     delay_ms(500);
     
     while(1)
     {
        mem[stagio] = sort;
        for(i = 0;i < stagio + 1;i++)
        {
          if(mem[i] == 0){led_on(0);}
          if(mem[i] == 1){led_on(1);}
          if(mem[i] == 2){led_on(2);}
          if(mem[i] == 3){led_on(3);}
        }
        while(stagio >= aux)
        {
           while(!(s0 && s1 && s2 && s3)) //aguarda pressionar um botão
           {
              if(!s0){botao = 0;}
              if(!s1){botao = 1;}
              if(!s2){botao = 2;}
              if(!s3){botao = 3;}
              if(sort > -1){sort--;}  //sorteia
              if(sort < 0){sort = 3;}
              delay_ms(5);
           }
           if(botao < 4)
           {
             if(botao == 0){led_on(0);}
             if(botao == 1){led_on(1);}
             if(botao == 2){led_on(2);}
             if(botao == 3){led_on(3);}
             if(botao != mem[aux])      //Confere
             {
                stagio = -1 ; //errado!!
                led0 = 1; led1 = 1; led2 = 1; led3 = 1;
                sound_play(500,500);
                delay_ms(200);
                led_on(4);  //apaga todos os leds
             }
             aux++;
           }
           botao = 4;
         }
        delay_ms(100);
        stagio++;
        aux = 0;
     }
} 
int led_on(int cor)
{
       if(cor == 0){led0 = 1; sound_play(1000,100);}
  else if(cor == 1){led1 = 1; sound_play(1122,100);}
  else if(cor == 2){led2 = 1; sound_play(1259,100);}
  else if(cor == 3){led3 = 1; sound_play(1334,100);}
  delay_ms(100);
  led0 = 0; led1 = 0; led2 = 0; led3 = 0;
  delay_ms(20);
  return 0;
}