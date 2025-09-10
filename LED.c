#include <Arduino.h>
#include<avr/io.h>
#include<util/delay.h>

#define DATA_PIND7 PD7
#define DATA_PIND6 PB0
#define DATA_PIND5 PB1
#define DATA_PIND4 PB2
#define Enable PB3
#define DATA_RS PB4

void lcd_pulse()
{

  PORTB |= (1<<Enable); //enable high
  _delay_ms(100);
  PORTB &= ~(1<<Enable); //enable low
  _delay_ms(200);
  
}

int lcd_command(unsigned char cmd)
{
  PORTB &= ~(1<<DATA_RS); //command mode
  
  if(cmd & 0x10) //send higher nibble
  {
    PORTB |= (1<<DATA_PIND4); //set 1
  }
  else
  {
    PORTB &= ~(1<<DATA_PIND4); //clear 0
  }

  if(cmd & 0x20) //send higher nibble
  {
    PORTB |= (1<<DATA_PIND5); //set 1
  }
  else
  {
    PORTB &= ~(1<<DATA_PIND5); //clear 0
  }
  if(cmd & 0x40) //send higher nibble
  {
    PORTB |= (1<<DATA_PIND6); //set 1
  }
  else
  {
    PORTB &= ~(1<<DATA_PIND6); //clear 0
  } 

  if(cmd & 0x80) //send higher nibble
  {
    PORTB |= (1<<DATA_PIND7); //set 1
  }
  else
  {
    PORTB &= ~(1<<DATA_PIND7); //clear 0
  }



  lcd_pulse(); //send pulse



  if(cmd & 0x01) //send lower nibble
  {
    PORTB |= (1<<DATA_PIND4); //set 1
  }
  else
  {
    PORTB &= ~(1<<DATA_PIND4); //clear 0
  }   
  if(cmd & 0x02) //send lower nibble
  {
    PORTB |= (1<<DATA_PIND5); //set 1
  }
  else
  {
    PORTB &= ~(1<<DATA_PIND5); //clear 0
  }

  if(cmd & 0x04) //send lower nibble
  {
    PORTB |= (1<<DATA_PIND6); //set 1
  }
  else
  {
    PORTB &= ~(1<<DATA_PIND6); //clear 0
  }

  if(cmd & 0x08) //send lower nibble
  {
    PORTB |= (1<<DATA_PIND7); //set 1
  }
  else
  {
    PORTB &= ~(1<<DATA_PIND7); //clear 0
  }

  lcd_pulse(); //send pulse


}

int lcd_init()
{
  _delay_ms(200); //wait for lcd to power up
  lcd_command(0X02); //4 bit mode
  lcd_command(0X28);//2 line, 5*7 matrix
  lcd_command(0X0C);//display on, cursor off
  lcd_command(0X06);//increment cursor
  lcd_command(0X01);//clear display
  _delay_ms(2);
  
}

void lcd_print(char *str){
    while(*str)
    {
        lcd_data(*str++);
    }

}

void lcd_data(unsigned char data)
{
  

}



int main(){

  DDRB=0xFF;
   DDRD |= (1<<DATA_PIND7);
   lcd_init();

   lcd_command(0x80); //1st line, 1st position
   lcd_print("Hello World! ");

   lcd_command(0xC0); //2nd line, 1st position
    lcd_print("LCD Working :");

    while(1){
      //loop forever
    }
   

  
  return 0;
}