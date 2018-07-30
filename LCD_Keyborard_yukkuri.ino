#include <PS2Keyboard.h>
#include <LiquidCrystal.h>


//Keyboard Settings
const int DataPin = 2;
const int IRQpin =  3;
PS2Keyboard keyboard;

//LCD Settings
LiquidCrystal lcd(9,8,7,4,6,5);
const int lcd_col = 20;
const int lcd_low = 4;


void setup() {
  //Keyboard
  delay(1000);
  keyboard.begin(DataPin, IRQpin, PS2Keymap_Japanese);
  
  //LCD
  lcd.begin(lcd_col, lcd_low);
  lcd.clear();
  lcd.cursor();
  
  Serial.begin(9600);
  Serial.println("?");
  delay(2000);
  Serial.println("yukkurisine");
}

static int lcd_cal_col = 0;
static int lcd_cal_row = 0;
char str[512]={'¥0'};
int stri =0;

void loop() {
  if (keyboard.available()) {
    
    if(lcd_cal_col==0 && lcd_cal_row==0){
      lcd.setCursor(0, 0);
      lcd_cal_col =0;
      lcd_cal_row =0;
    }
    
    // read the next key
    char c = keyboard.read();
  
    // check for some of the special keys
    if (c == PS2_ENTER) {
//      Serial.print(str);
      Serial.write((byte*)str,stri);
      Serial.println("");
      stri =0;
      str[0] = 'NULL';
      
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd_cal_col =0;
      lcd_cal_row =0;
    } else if (c == PS2_TAB) {
      Serial.print("[Tab]");
    } else if (c == PS2_F1) {
      Serial.println("nikonikogijutubu");
    } else if (c == PS2_F2) {
      Serial.println("yukkurisiteittene");
    } else if (c == PS2_F3) {
      Serial.println("yukkurisine");
    } else if (c == PS2_F4) {
      Serial.println("enuthi-kkyouto shuttensimasu");
    } else if (c == PS2_F5) {
      Serial.println("ko/i/yo");
    } else if (c == PS2_F6) {
      Serial.println("fa/bo/re/yo");
    } else if (c == PS2_F7) {
      Serial.print("[F7]");
    } else if (c == PS2_F8) {
      Serial.print("[F8]");
    } else if (c == PS2_F9) {
      Serial.print("[F9]");
    } else if (c == PS2_F10) {
      Serial.print("[F10]");
    } else if (c == PS2_F11) {
      Serial.print("[F11]");
    } else if (c == PS2_F12) {
      Serial.print("[F12]");
    } else if (c == PS2_ESC) {
      Serial.print("[ESC]");
    } else if (c == PS2_PAGEDOWN) {
      Serial.print("[PgDn]");
    } else if (c == PS2_PAGEUP) {
      Serial.print("[PgUp]");
    } else if (c == PS2_LEFTARROW) {
      Serial.print("[Left]");
    } else if (c == PS2_RIGHTARROW) {
      Serial.print("[Right]");
    } else if (c == PS2_UPARROW) {
      Serial.print("[Up]");
    } else if (c == PS2_DOWNARROW) {
      Serial.print("[Down]");
    } else if (c == PS2_DELETE) {
      Serial.print("[Del]");
    } else {

      
      // otherwise, just print all normal characters
/*      Serial.print(c,DEC);
      Serial.print(",0x");
      Serial.print(c,HEX);
      Serial.print("|");*/
      
        //Serial.print(c);
        str[stri++] = c;
        str[stri] = 'NULL';
        
        if(lcd_col -1 < lcd_cal_col){
          if(lcd_cal_row < lcd_low -1){
            lcd_cal_row++;
            lcd_cal_col=0;
            lcd.setCursor(0,lcd_cal_row);
          }else{
            lcd.scrollDisplayLeft();
          }
        }
        lcd.print(c);
        lcd_cal_col++;
    }
  }
  
  	if (Serial.available() > 0) { // 受信したデータが存在する
		int incomingByte = Serial.read(); // 受信データを読み込む

		//Serial.print("I received: "); // 受信データを送りかえす
		//Serial.println(incomingByte, DEC);

            lcd.print((char)incomingByte);
	}
}
