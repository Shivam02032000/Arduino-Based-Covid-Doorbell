#include <Wire.h>
const int buzzer=5;
#include <Adafruit_MLX90614.h>
char *typeName[]={"Object:","Ambient:"};

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

#include <LiquidCrystal_I2C.h>
const uint8_t I2C_ADDRESS =0x27;
const uint8_t LCD_CHAR= 16;
const uint8_t LCD_ROW= 2;
LiquidCrystal_I2C lcd(I2C_ADDRESS, LCD_CHAR,LCD_ROW);


void setup() {
  Serial.begin(9600);
pinMode(buzzer,OUTPUT);
  Serial.println("Robojax MLX90614 test");  

   if (!mlx.begin()) //Begin returns 0 on a good init
  {
      lcd.print("MLX90614 Failed");
      lcd.setCursor(0,1);
      lcd.print("check wiring!");      
    while (1)
      ;
  }  
  Wire.begin();
  lcd.begin();
  lcd.backlight(); 
  lcd.clear(); 
      lcd.print("WELCOME");
      lcd.setCursor(0,1);
      lcd.print("Infrared Temp.");          
      delay(2000);       
      clearCharacters(LCD_ROW-1,0, LCD_CHAR-1);
       
  
}//setup() end

void loop() {
 
  printTemp('C');//object temperature in C
  delay(2000);
  
  printTemp('D');//ambient temperature in C
  delay(2000);
  

}

 
float getTemp(char type)
{
   
  float value;
    float tempObjec = mlx.readObjectTempC();//in C object
    if(tempObjec<=24)
{

tone(buzzer,1000);
delay(1000);
noTone(buzzer);
delay(2000);
}
else
{

tone(buzzer,1000);
delay(1000);
noTone(buzzer);
delay(700);
tone(buzzer,1000);
delay(1000);
noTone(buzzer);
delay(700);
tone(buzzer,1000);
delay(1000);
noTone(buzzer);
delay(700);
}
    float tempAmbient = mlx.readAmbientTempC();
   if(type =='F')
   {
    value = mlx.readObjectTempF(); //Fah. Object
   }else if(type =='G')
   {
    value = mlx.readAmbientTempF();//Fah Ambient
   }else if(type =='K')
   {
    value = tempObjec + 273.15;// Object Kelvin
   }else if(type =='L')
   {
    value = tempAmbient + 273.15;//Ambient Kelvin
   }else if(type =='C')
   {
    value = tempObjec;
   }else if(type =='D')
   {
    value = tempAmbient;
   }
   return value;
    
}
 
void printTemp(char type)
{
 clearCharacters(1,0, LCD_CHAR-1 );  
  
  float tmp =getTemp(type);
      lcd.setCursor(0,1);
      
  if(type =='C')
  {

      lcd.print(typeName[0]);  
      lcd.print(" ");
      lcd.print(tmp);        
      lcd.print((char)223);// 
      lcd.print("C");      
              

  }else if(type =='D')
  {
      lcd.print(typeName[1]); 
      lcd.print(" ");
      lcd.print(tmp);        
      lcd.print((char)223);// 
      lcd.print("C");        
  }else if(type =='F')
  {
      lcd.print(typeName[0]); 
      lcd.print(" ");
      lcd.print(tmp);        
      lcd.print((char)223);// 
      lcd.print("F");        
  }else if(type =='G')
  {
      lcd.print(typeName[1]);
      lcd.print(" ");
      lcd.print(tmp);        
      lcd.print((char)223);// 
      lcd.print("F");        
  }

  else if(type =='K')
  {
      lcd.print(typeName[0]); 
      lcd.print(" ");
      lcd.print(tmp);        
      lcd.print((char)223);// 
      lcd.print("K");        
  }  
  else if(type =='L')
  {
      lcd.print(typeName[1]);
      lcd.print(" ");
      lcd.print(tmp);        
      lcd.print((char)223);// 
      lcd.print("K");        

  }


}


void clearCharacters(uint8_t row,uint8_t start, uint8_t stop )
{
    for (int i=start; i<=stop; i++)
    {
    lcd.setCursor (i,row); //  
    lcd.write(254);
    } 

}
