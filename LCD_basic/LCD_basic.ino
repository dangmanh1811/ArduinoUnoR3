#include <LiquidCrystal.h> // Thư viện giúp điều khiển con HD544780

// khai báo đối tượng, tên gọi trỏ tới màn hình
// khai báo biến lưu 1 value gì đó, int x = 10, int yob = 2002
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
				// đưa các chân như đã đấu


//đa phần NN lập trình đếm từ 0
//LCD có 2 dòng: dòng 0, dòng 1
//		16 kí tự: vị trí 0, 1, 2 ...
void setup()
{
  lcd.begin(16, 2); // báo rằng tao mún chơi cả 2 dòng x 16 kí tự
  lcd.setCursor(0, 0);
  lcd.print("Hello ");
     
}

// void loop()
// {
//   lcd.setCursor(4, 1); // nhảy đến vị trí 4 ở dòng 1
//   lcd.print("Ho Dang Manh");
  
//   // nhấp nháy, lúc tắt mở màn hình
//   lcd.noDisplay();
//   delay(500);
//   lcd.display();
//   delay(500);
// }
void loop()
{}