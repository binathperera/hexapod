
void printLCD(String str,int col,int line){
  lcd.setCursor(col,line);
  lcd.print(str);
}
void do_blink(){
  for(int i=3;i<=10;i+=6){
    lcd.setCursor(i,0);
    lcd.write(6);
    lcd.setCursor(i+1,0);
    lcd.write(6);
    lcd.setCursor(i+2,0);
    lcd.write(6);
    lcd.setCursor(i+3,0);
    lcd.write(6);
  }
}
void unblink(){
  for(int i=3;i<=10;i+=6){
    lcd.setCursor(i,0);
    lcd.write(1);
    lcd.setCursor(i,1);
    lcd.write(2);
    lcd.setCursor(i+1,0);
    lcd.write(3);
    lcd.setCursor(i+1,1);
    lcd.write(3);
    lcd.setCursor(i+2,0);
    lcd.write(3);
    lcd.setCursor(i+2,1);
    lcd.write(3);
    lcd.setCursor(i+3,0);
    lcd.write(4);
    lcd.setCursor(i+3,1);
    lcd.write(5);
  }
 }

