#include <iostream>
#include <conio.h>
#include <windows.h>
#include <thread>               //nhạc
using namespace std;
void musicStart(){
    PlaySound(TEXT("C:\\Users\\PC\\Downloads\\GAME\\sound\\StartScreen.wav"), NULL, SND_FILENAME);}
void battle() {
    PlaySound(TEXT("C:\\Users\\PC\\Downloads\\GAME\\sound\\bossFightsirkoto51.wav"), NULL, SND_FILENAME);
}
 void stopMusic() {
   PlaySound(NULL, NULL, 0);}
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); COORD CursorPosition; //Khai báo dùng cho việc ẩn con trỏ
const int WIDTH = 100;
const int HEIGHT = 25;
bool inChallenge = false; //Trong game
bool inInfo = false;       //Trong about game

int posY=9;                 //Vi trí người chơi
int enemyY[3];
int enemyX[3];
int enemyFlag[3];           //tạo cờ để xuất hiện enemy

char player[3][4]={ char(201),char(205),char(187),
                    char(186),char(15),char(186),
                    char(186),char(15),char(186),
                    char(200),char(205),char(188) };

void gotoxy(int x, int y) {       //dùng để di chuyển đến vị trí nào đó có tọa độ x,y
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void drawFrame() {  //vẽ khung giới hạn
    Sleep(500);
    system("cls");  //xóa màn hình console
    gotoxy(0,0);
    cout<<char(218);
    gotoxy(99,0);
    cout<<char(191);
    gotoxy(0,25);
    cout<<char(192);
    gotoxy(99,25);
    cout<<char(217);
    for (int i = 1; i < WIDTH-1 ; i++) {
        gotoxy(i,0);
        cout << char(196);// khung trên
    }
    cout << endl;
    for (int i = 0; i < HEIGHT-1; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0 || j == WIDTH - 1) {
                cout << char(179);  //khung bên trái và phải
            } else {
                cout << " ";  //phần bên trong khung
            }
        }
        cout << endl;
    }
    for (int i = 1; i < WIDTH-1 ; i++) {
    gotoxy(i,25);
    cout << char(196);//khung dưới
    }
    cout << endl;
}
void setcursor(bool visible, DWORD size) {  //Ẩn con trỏ
	if(size == 0)
		size = 20;
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.dwSize = size;
	lpCursor.bVisible = visible;
	SetConsoleCursorInfo(console,&lpCursor);}

void drawPlayer(){
	for(int i=0; i<3; i++){
		for(int j=0; j<4; j++){
			gotoxy(i+2, j+posY); cout<<player[i][j];}
    }
}
void erasePlayer(){
	for(int i=0; i<3; i++){
		for(int j=0; j<4; j++){
			gotoxy(i+2, j+posY); cout<<" ";}
	}
}
void genEnemy(int ind){                 //tạo enemy nằm random trong khoảng từ 9 đến 21
	enemyY[ind] = 9 + rand()%(13);
}
void drawEnemy(int ind){
	if( enemyFlag[ind] == true ){
		gotoxy(enemyX[ind], enemyY[ind]);   cout<<" \\\\____//";
		gotoxy(enemyX[ind], enemyY[ind]+1); cout<<" /  OO  \\ ";
		gotoxy(enemyX[ind], enemyY[ind]+2); cout<<"|_ |__| _| ";
		gotoxy(enemyX[ind], enemyY[ind]+3); cout<<" //____\\\\";
	}
}
void eraseEnemy(int ind){
	if( enemyFlag[ind] == true ){
		gotoxy(enemyX[ind], enemyY[ind]);   cout<<"           ";
		gotoxy(enemyX[ind], enemyY[ind]+1); cout<<"           ";
		gotoxy(enemyX[ind], enemyY[ind]+2); cout<<"           ";
		gotoxy(enemyX[ind], enemyY[ind]+3); cout<<"           ";
	}
}
void resetEnemy(int ind){           //reset lại enemy khi nó đi đến cuối đường
	eraseEnemy(ind);
	enemyX[ind] =88;
	genEnemy(ind);
}
int collision() {               //xử lí va chạm
    return (enemyX[0] <= 5 && enemyX[0] + 4 >= 1 && posY >= enemyY[0] && posY < enemyY[0] + 4);
}

void lose(){
    system("cls");
    drawFrame();
    Sleep(50);
    gotoxy(34,10);  cout<<char(201);
    gotoxy(60,10);  cout<<char(187);
    gotoxy(34,13);  cout<<char(200);
    gotoxy(60,13);  cout<<char(188);
    for (int i = 1; i < 26; i++) {
        gotoxy(34+i,10);
        cout << char(205);// khung trên
    }
    for (int i = 0; i < 2; i++) {
    gotoxy(34,11+i);
        for (int j = 0; j < 27; j++) {
            if (j == 0 || j == 26) {
                cout << char(186);  //khung bên trái và phải
            } else {
                cout << " ";  //phần bên trong khung
            }
        }
        cout << endl;
    }
    for (int i = 1; i < 26 ; i++) {
    gotoxy(34+i,13);
    cout << char(205);//khung dưới
    }
    gotoxy(42,11);  cout<<"  YOU LOSE";
    gotoxy(35,12);  cout<<"    press 'U' to return";
    stopMusic();            //Đợi hết nhạc mới chạy tiếp
}

void play(){
    enemyFlag[0] = 1;               // Để enemy 1 xuất hiện trước
	enemyFlag[1] = 0;
	enemyX[0] = enemyX[1] = 88;        //Vị trí enemy 1 và 2 là x=88
    genEnemy(0);
	genEnemy(1);
    while(1){
    if(kbhit()){
        char ch = getch();
			if( ch=='W' || ch=='w' ){
				if( posY > 9 )
					posY -= 1;
			}
			if( ch=='S' || ch=='s' ){
				if( posY < 21 )
					posY += 1;
			}
		}
    drawPlayer();
    drawEnemy(0);
    drawEnemy(1);
    if( collision() == 1  ){
        lose();
        return ;}
    Sleep(50);
    erasePlayer();
    eraseEnemy(0);
    eraseEnemy(1);
    if(enemyX[0] == 69 )                //Kiểm tra xem enemy 1 đã đi đến vị trí x=69 chưa
       if(enemyFlag[1] == 0)             //Nếu đã đến thì sẽ bật cờ lên để enemy 2 xuất hiện
          enemyFlag[1] = 1;

    if(enemyFlag[0] == 1 )               //Kiểm tra enemy 1 đã xuất hiện
       enemyX[0] -= 1;                  //Cho enemy di chuyển

    if(enemyFlag[1] == 1)
       enemyX[1] -= 1;

    if(enemyX[0] < 2 ){                 //Kiểm tra enemy đến giới hạn khung chưa
       resetEnemy(0);}                  //Xóa khi đã đến vào tạo enemy mới

    if(enemyX[1] < 2 ){
        resetEnemy(1);}
    }
}
void mainScreen(int selection) {
    system("cls");// Xóa màn hình console
    gotoxy(35,5); cout << "    GGGGG    OOOOO   DDDDD   "<<"\n";
    gotoxy(35,6); cout << "   G        O     O  D    D  "<<"\n";
    gotoxy(35,7); cout << "   G    GG  O     O  D    D  "<<"\n";
    gotoxy(35,8); cout << "   G     G  O     O  D    D  "<<"\n";
    gotoxy(35,9); cout << "    GGGGG    OOOOO   DDDDD   "<<"\n";
    gotoxy(36,12);cout << "=============================";
    gotoxy(37,13);cout << "         AND UNKNOWN";
    gotoxy(36,14);cout << "=============================";
    gotoxy(40,17);cout << (selection == 1 ? " > " : "  ") << "Start Game\n";
    gotoxy(40,18);cout << (selection == 2 ? " > " : "  ") << "About game\n";
    gotoxy(40,19);cout << (selection == 3 ? " > " : "  ") << "Exit\n";
    gotoxy(70,14);cout << " === HOW TO PLAY! === ";
    gotoxy(70,15);cout << "    = JUST DODGE =    ";
    gotoxy(70,16);cout << " +PRESS 'W' : UP " ;
    gotoxy(70,17);cout << " +PRESS 'S' : DOWN ";
    gotoxy(70,18);cout << " +PRESS 'J' : PRESS ";
    gotoxy(70,19);cout << " +PRESS 'U' : RETURN \r\r";
}

void clearchat(){
    char input=_getch();
    if (input == 'J' || input == 'j'){
    for (int i= 1; i < 7;i++){
    for (int j=1; j < WIDTH-1;j++){
      gotoxy(j,19);
      cout<<" ";}
    cout<<endl;}
    gotoxy(1,19);}
}

void drawInfoScreen() {
    drawFrame();
    gotoxy(40, 2);
    cout << " INFO\n";
    gotoxy(31,3);
    cout << " THIS GAME IS NEVER-ENDING ";
    gotoxy(2, 5);
    cout << " DEVELOPED BY NGUYEN HOANG KHIEM ";
    gotoxy(2, 7);
    cout << " SOUND CREATED BY SIRKOTO51(freesound.org) ";
}
void god(){
    Sleep(3000);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 14);           //Đổi màu chữ 14 là màu vàng
    gotoxy(40,11);cout << "  O==O==O   " << endl;
    gotoxy(40,12);cout << "  /_   _ \\  " << endl;
    gotoxy(40,13);cout << " ( o   o  )   " << endl;
    gotoxy(40,14);cout << "  \\ <    /    " << endl;
    gotoxy(40,15);cout << "   \\ U  /     " << endl;
    gotoxy(40,16);cout << "   //  \\\\     " << endl;
    gotoxy(40,17);cout << "  //    \\\\    " << endl;
    SetConsoleTextAttribute(hConsole, 7);              //Trả về màu ban đầu
}
void challenge(){
    system("cls");
    drawFrame();
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 14);
    gotoxy(55,1);cout << " Are you ready?";
    thread musicB(battle);
    do{
    gotoxy(40,1);cout << "  O==O==O   " << endl;
    gotoxy(40,2);cout << "  /\\   / \\  " << endl;
    gotoxy(40,3);cout << " ( o   o  )   " << endl;
    gotoxy(40,4);cout << "  \\ <    /    " << endl;
    gotoxy(40,5);cout << "   \\ U  /     " << endl;
    gotoxy(40,6);cout << "   //  \\\\     " << endl;
    gotoxy(40,7);cout << "  //    \\\\    " << endl;
    SetConsoleTextAttribute(hConsole, 7);
    gotoxy(20,3); cout<<"  \\\\____//";
    gotoxy(20,4); cout<<"  /  OO  \\ ";
    gotoxy(20,5); cout<<" |_ |__| _| ";
    gotoxy(20,6); cout<<"  //____\\\\";
    gotoxy(57,3); cout<< "  \\\\____//  ";
    gotoxy(57,4); cout<<"  /  OO  \\  ";
    gotoxy(57,5); cout<<" |_ |__| _|  ";
    gotoxy(57,6); cout<<"  //____\\\\ ";
    gotoxy(0,8);cout << char(195);
    gotoxy(99,8);cout << char(180);
for (int i = 1; i < WIDTH-1 ; i++) {
    gotoxy(i,8); cout << char(196);}
    _getch();
    gotoxy(55,1); cout << "                ";
    play();
    }while(collision() == 0 );
    musicB.detach();
}
void intro(){
    Sleep(500);
    cout << "Starting game...";
    stopMusic();
    drawFrame();
    gotoxy(0,18);cout << char(195);
    gotoxy(99,18);cout << char(180);
for (int i = 1; i < WIDTH-1 ; i++) { //khung tro chuyen
    gotoxy(i,18);
    cout << char(196);}
    cout << endl;
    god();
    gotoxy(1,19); Sleep(3000); cout<<"???: Hello human, Did you wake up?";  clearchat();
    Sleep(500); cout<<"YOU: Who are you? ";  clearchat();
    Sleep(500); cout<<"???: I am GOD. Do you wanna be a GOD? ";  clearchat();
    Sleep(500);  cout<<"YOU: How?";  clearchat();
    Sleep(500);  cout<<"GOD: Beat me!";
    gotoxy(20,9); cout<< "  \\\\____//  ";
    gotoxy(20,10); cout<<"  /  OO  \\  ";
    gotoxy(20,11); cout<<" |_ |__| _|  ";
    gotoxy(20,12); cout<<"  //____\\\\ ";
    gotoxy(57,9); cout<< "  \\\\____//  ";
    gotoxy(57,10); cout<<"  /  OO  \\  ";
    gotoxy(57,11); cout<<" |_ |__| _|  ";
    gotoxy(57,12); cout<<"  //____\\\\ ";
    _getch(); clearchat();
    for (int i = 1; i < HEIGHT; i++) {
        for (int j = 1; j < WIDTH-1; j++) {
                gotoxy(j,i);
                cout << char(178);}
        cout << endl;}
    challenge();
}
void starScreen(){
setcursor(0,0);
srand( (unsigned)time(NULL));  // Khởi tạo bộ sinh số ngẫu nhiên.
int selection = 1;
bool exitMenu = false;         //Đặt cờ để ấn nút thoát game
do {
    if (!inChallenge && !inInfo) {// Chỉ hiển thị màn hình chính nếu không ở trong game hoặc about game
    mainScreen(selection);
    }
    char input = _getch();
    switch (input) {
      case 'W':
      case 'w':
      if (!inChallenge && selection > 1) {
      selection--;
      }
      break;
      case 'S':
      case 's':
      if (!inChallenge && selection < 3 ) {
      selection++;
      }
      break;
      case 'J':
      case 'j':
      if (!inChallenge && !inInfo) { // Chỉ xử lý 'J' nếu chưa ở trong thử thách hoặc About game
      system("cls");
      switch (selection) {
      case 1:
      intro();
      inChallenge = true; // Đặt cờ để chỉ ra rằng chúng ta đang ở trong thử thách
      break;
      case 2:
      inInfo = true; // Đặt cờ để chỉ ra rằng chúng ta đang ở About game
      drawInfoScreen();
      break;
      case 3:
      exitMenu = true;
      break;
                    }
                }
                break;
        }

if (inChallenge && input == 'U'|| inChallenge && input == 'u' ) { //Trở về menu
system("cls");
inChallenge = false;
}
if (inInfo && input == 'U'|| inInfo && input == 'u' ) { //Trở về menu
system("cls");
inInfo = false;
}
} while (!exitMenu);}
int main() {
thread musicA(musicStart);
starScreen();
musicA.detach();
    return 0;
}
