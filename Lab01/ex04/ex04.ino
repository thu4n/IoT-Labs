// Kịch bản: giao lộ B bên trái, giao lộ A bên phải
// Khai báo các chân led 7 đoạn
unsigned const int A = 11;
unsigned const int B = 10;
unsigned const int C = 7;
unsigned const int D = 8;
unsigned const int E = 9;
unsigned const int F = 12;
unsigned const int G = 13;
unsigned const int H = 6;
// Khai báo các chân led đèn giao thông
unsigned const int red_A = 5;
unsigned const int yellow_A = 4;
unsigned const int green_A = 3;
unsigned const int red_B = 2;
unsigned const int yellow_B = 1;
unsigned const int green_B = 0;

bool turn = 0; // 0: B, 1: A

void zero(void) {
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, HIGH);
  digitalWrite(H, LOW);
}

void one(void) {
  digitalWrite(A, HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(H, HIGH);
}

void two(void) {
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, HIGH);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, HIGH);
  digitalWrite(G, LOW);
  digitalWrite(H, HIGH);
}

void three(void) {
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, LOW);
  digitalWrite(H, LOW);
  
}

void four(void) {
  digitalWrite(A, HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
  digitalWrite(H, LOW);
}

void five(void) {
  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, HIGH);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
  digitalWrite(H, LOW);
}

void six(void) {
  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
  digitalWrite(H, LOW);
}

void seven(void) {
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(H, LOW);
}

void eight(void) {
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
  digitalWrite(H, LOW);
}

void nine(void) {
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, HIGH);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
  digitalWrite(H, LOW);
}

void traffic_light(void) {
    for (int i = 9; i >= 0; i--) { // Đếm ngược từ 9 về 0
        switch (i) {
            case 0:
                zero();
                if (turn == 0) {
                    // Giao lộ B hết lượt, giao lộ A được chạy
                    digitalWrite(red_A, LOW);
                    digitalWrite(yellow_B, LOW);
                    digitalWrite(green_A, HIGH);
                    digitalWrite(red_B, HIGH);
                    turn = 1;
                }
                else {
                    // Giao lộ A hết lượt, giao lộ B được chạy
                    digitalWrite(red_B, LOW);
                    digitalWrite(yellow_A, LOW);
                    digitalWrite(green_B, HIGH);
                    digitalWrite(red_A, HIGH);
                    turn = 0;
                }
                break;
            case 1:
                one();
                break;
            case 2:
                two();
                if (turn == 0) {
                    // Giao lộ B hết đèn xanh, chuyển sang đèn vàng
                    digitalWrite(green_B, LOW);
                    digitalWrite(yellow_B, HIGH);
                }
                else {
                    // Giao lộ A hết đèn xanh, chuyển sang đèn vàng
                    digitalWrite(green_A, LOW);
                    digitalWrite(yellow_A, HIGH);
                }
                break;
            case 3:
                three();
                break;
            case 4:
                four();
                break;
            case 5:
                five();
                break;
            case 6:
                six();
                break;
            case 7:
                seven();
                break;
            case 8:
                eight();
                break;
            case 9:
                nine();
                if (turn == 0) {
                    // Giao lộ A đang dừng, B đang chạy
                    digitalWrite(red_A, HIGH);
                    digitalWrite(green_B, HIGH);
                }
                else {
                    // Giao lộ B đang dừng, A đang chạy
                    digitalWrite(red_B, HIGH);
                    digitalWrite(green_A, HIGH);
                }
                break;
        }
        delay(1000);
    }
}

void setup(void)
{
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(H, OUTPUT);
  pinMode(red_A, OUTPUT);
  pinMode(yellow_A, OUTPUT);
  pinMode(green_A, OUTPUT);
  pinMode(red_B, OUTPUT);
  pinMode(yellow_B, OUTPUT);
  pinMode(green_B, OUTPUT);
}

void loop(void)
{
    traffic_light();
}