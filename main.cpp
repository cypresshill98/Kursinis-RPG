#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cwchar>
#include <functional>
using namespace std;

const char PLAYER='@';     //pagrindinis zaideajs
const char ENEMY1='&';     //priesas
const char POTION='h';     //gyvybes
const char GOLD='$';       //taskai

char Map[62][32];//pagrindinio zemelapio masyvas
const char cl='*';//vaiksciojimo lauko elementas
char key;           //vaiksciojimo ivestis
int pozx, pozy;     //zaidejo pozicija
int hp;             //gyvybes
int sc;             //taskai
string nm;          //zaidejo vardas
bool death;         //zaidejo mirciai
bool sound=true;    //garso valdymui
bool running=true;  //iseimui is programos
int winx,winy;
bool winb=false;
double tt;         //laikas
HANDLE color=GetStdHandle(STD_OUTPUT_HANDLE); //spalvos pasirinkimui


class Field{    //pagrindine zaidimo laiko klase

public:

void place(){   //nustatomi pradiniai kintamieji
Map[3][3]=PLAYER;
pozx=2;
pozy=2;
hp=100;
sc=0;
death=0;
winx=55;
winy=27;
winb=false;
}

void input_field(){         //nuskaitomas zaidimo zemelapis is failo
ifstream inputMap ("Map0.txt");
for(int j=0;j<32;j++)
        for(int i=0;i<62;i++)
        inputMap>>Map[i][j];
    place();
}

void show_field(){      //zemelapio rodymas
    for(int j=0;j<32;j++){
        for(int i=0;i<62;i++){
                if(Map[i][j]=='*'){              //Spalvinimas:
                    SetConsoleTextAttribute(color, 0x68);
                }
                else if(Map[i][j]=='#'){
                    SetConsoleTextAttribute(color, 0);    //juoda spalva
                }
                else if(Map[i][j]=='+' || Map[i][j]=='-' || Map[i][j]=='|' || Map[i][j]=='/' || Map[i][j]=='\\'){
                    SetConsoleTextAttribute(color, 0x2a);
                }
                else if(Map[i][j]=='@' || Map[i][j]=='v' || Map[i][j]=='^' || Map[i][j]=='<' || Map[i][j]=='>'){
                    SetConsoleTextAttribute(color, 0x69);   //ryskiai melyna
                }
                else if(Map[i][j]=='&'){
                    SetConsoleTextAttribute(color, 0x6c);   //ryskiai raudona
                }
                else if(Map[i][j]=='h'){
                    SetConsoleTextAttribute(color, 0x64);  //tamsiai raudona
                }
                else if(Map[i][j]=='$'){
                    SetConsoleTextAttribute(color, 0x6e); //ryskiai geltona
                }
                else if(Map[i][j]=='O'){
                    SetConsoleTextAttribute(color, 0x5b);
                }
                else if(Map[i][j]=='X'){
                    SetConsoleTextAttribute(color, 0x5f);
                }
                if(i==winx && j==winy){
                    SetConsoleTextAttribute(color, 0x69);
                }
        cout<<Map[i][j];       //zemelapio elementu isvedimas
        }cout<<"\n";
    }

}

void Move(){               //vaiksciojimas char masyve
for(int j=0;j<32;j++)
        for(int i=0;i<62;i++)
        if(Map[i][j]==PLAYER){pozx=i;pozy=j;}   //nustatoma zaidejo pozicija

key=getch();//ivestis

if(key==72 && (Map[pozx][pozy-1]=='*' || Map[pozx][pozy-1]==POTION || Map[pozx][pozy-1]==GOLD)){   //aukstyn
        if(Map[pozx][pozy-1]==POTION){      //gydymo paemimas
                if(90<=hp){hp=100-hp+hp;}
                else{hp=hp+10;}
                sc=sc+5;
                if(sound==true){
                Beep(800,80);       //gydymo garsas
                Beep(900,80);
                Beep(1000,80);
                }
        }
        if(Map[pozx][pozy-1]==GOLD){sc=sc+100;  //tasku paemimas
        if(sound==true){
        Beep(2000,100);}            //tasku garsas
        }
    Map[pozx][pozy-1]=PLAYER;      //ejimas aukstyn
    Map[pozx][pozy]=cl;            //praeitos koordinates istrinimas
    if(sound==true){Beep(146,70);}
                                       //garsas vaiksciojant
}
if(key==80 && (Map[pozx][pozy+1]=='*' || Map[pozx][pozy+1]==POTION || Map[pozx][pozy+1]==GOLD)){   //zemyn
            if(Map[pozx][pozy+1]==POTION){  //gydimo paemimas
                if(90<=hp){hp=100-hp+hp;}
                else{hp=hp+10;}
                sc=sc+5;
                if(sound==true){
                Beep(800,80);       //gydymo garsas
                Beep(900,80);
                Beep(1000,80);
                }
        }
            if(Map[pozx][pozy+1]==GOLD){sc=sc+100;  //tasku paemimas
            if(sound==true){
        Beep(2000,100);}}               //tasku garsas
        Map[pozx][pozy+1]=PLAYER;       //ejimas zemyn
        Map[pozx][pozy]=cl;
    if(sound==true){Beep(146,70);}                                          //garsas vaiksciojant
}
if(key==75 && (Map[pozx-1][pozy]=='*' || Map[pozx-1][pozy]==POTION ||  Map[pozx-1][pozy]==GOLD)){   //kaire
        if(Map[pozx-1][pozy]==POTION){
                if(90<=hp){hp=100-hp+hp;}
                else{hp=hp+10;}
                sc=sc+5;
                if(sound==true){
                Beep(800,80);       //gydymo garsas
                Beep(900,80);
                Beep(1000,80);
                }
        }
        if(Map[pozx-1][pozy]==GOLD){sc=sc+100;  //tasku paemimas
        if(sound==true){
        Beep(2000,100);}}           //tasku garsas
        Map[pozx-1][pozy]=PLAYER;   //ejimas i kaire
        Map[pozx][pozy]=cl;
    if(sound==true){Beep(146,70);}                                       //garsas vaiksciojant
}
if(key==77 && (Map[pozx+1][pozy]=='*' || Map[pozx+1][pozy]==POTION || Map[pozx+1][pozy]==GOLD)){   //desine
            if(Map[pozx+1][pozy]==POTION){
                if(90<=hp){hp=100-hp+hp;}
                else{hp=hp+10;}
                sc=sc+5;
                if(sound==true){
                Beep(800,80);       //gydymo garsas
                Beep(900,80);
                Beep(1000,80);
                }
        }
            if(Map[pozx+1][pozy]==GOLD){sc=sc+100;  //tasku paemimas
            if(sound==true){
        Beep(2000,100);}}           //tasku garsas
        Map[pozx+1][pozy]=PLAYER;   //ejimas i desine
        Map[pozx][pozy]=cl;
    if(sound==true){Beep(146,70);}                                    //garsas vaiksciojant
}
        if(pozx==winx && pozy==winy){
            winb=true;
        }
attack();  //pulame priesus
enemy();   //priesai puola mus
}


void enemy(){              //Priesu puolimas ir vaiksciojimas
    int epozx,epozy,zz=0;
for(int j=pozy-5;j<=pozy+5;j++){
        for(int i=pozx-5;i<=pozx+5;i++){
            if(Map[i][j]==ENEMY1){epozx=i;epozy=j;zz++;}    //nustatomos priesu pozicijos
        }}

        if(zz!=0){
        if(pozx<epozx && Map[epozx-1][epozy]==cl){Map[epozx-1][epozy]=ENEMY1;Map[epozx][epozy]=cl;}    //priesu ejimas i kaire
        else if(pozx>epozx && Map[epozx+1][epozy]==cl){Map[epozx+1][epozy]=ENEMY1;Map[epozx][epozy]=cl;}//priesu ejimas i desine
        else if(pozy<epozy && Map[epozx][epozy-1]==cl){Map[epozx][epozy-1]=ENEMY1;Map[epozx][epozy]=cl;}//priesu ejimas aukstyn
        else if(pozy>epozy && Map[epozx][epozy+1]==cl){Map[epozx][epozy+1]=ENEMY1;Map[epozx][epozy]=cl;}//priesu ejimas zemyn
        }
        if(Map[pozx+1][pozy]==ENEMY1){hp=hp-5;}     //priesu puolimas
        else if(Map[pozx-1][pozy]==ENEMY1){hp=hp-5;}
        else if(Map[pozx][pozy+1]==ENEMY1){hp=hp-5;}
        else if(Map[pozx][pozy-1]==ENEMY1){hp=hp-5;}
}

void attack(){          //puolam priesus
if(Map[pozx][pozy+1]=='v'){Map[pozx][pozy+1]=cl;}//puolam zemyn
if(Map[pozx][pozy-1]=='^'){Map[pozx][pozy-1]=cl;}//puolam aukstyn
if(Map[pozx-1][pozy]=='<'){Map[pozx-1][pozy]=cl;}//puolam kairen
if(Map[pozx+1][pozy]=='>'){Map[pozx+1][pozy]=cl;}//puolam desinen

if(key=='s' && (Map[pozx][pozy+1]==cl || Map[pozx][pozy+1]==ENEMY1))
                    {if(Map[pozx][pozy+1]==ENEMY1){sc=sc+50;}
                    Map[pozx][pozy+1]='v';
                    if(sound==true){
                    Beep(523,70);}}     //puolimo garsas

if(key=='w' && (Map[pozx][pozy-1]==cl || Map[pozx][pozy-1]==ENEMY1))
                    {if(Map[pozx][pozy-1]==ENEMY1){sc=sc+50;}
                    Map[pozx][pozy-1]='^';
                    if(sound==true){
                    Beep(523,70);}}     //puolimo garsas

if(key=='a' && (Map[pozx-1][pozy]==cl || Map[pozx-1][pozy]==ENEMY1))
                    {if(Map[pozx-1][pozy]==ENEMY1){sc=sc+50;}
                    Map[pozx-1][pozy]='<';
                    if(sound==true){
                    Beep(523,70);}}     //puolimo garsas

if(key=='d' && (Map[pozx+1][pozy]==cl || Map[pozx+1][pozy]==ENEMY1))
                    {if(Map[pozx+1][pozy]==ENEMY1){sc=sc+50;}
                    Map[pozx+1][pozy]='>';
                    if(sound==true){
                    Beep(523,70);}}     //puolimo garsas

                    if(hp<=0){death=1;}//jei gyvybes=0, mirstam
}

};

class Inventory{    //zaidejo informacijos klase
    string hud;
    public:

void time(){
string timeR= "TT.tt";
stringstream ss;
ss <<fixed<<setprecision(2)<< tt;
string timestr(ss.str());
for(int i=(timestr.length());i<=4;i++)
    timestr=timestr+" ";
hud.replace(hud.find(timeR),timeR.length(),timestr);
}

void health(){      //zaidejo gyvybiu rodymas

string healt= "999";
stringstream ss;
ss << hp;
string hps(ss.str());
if(hps.length()==2){hps=hps+" ";}
if(hps.length()==1){hps=hps+"  ";}
hud.replace(hud.find(healt),healt.length(),hps); //keiciame "999" i zaidejo gyvybes
}

void score(){       //zaidejo tasku rodymas
string scor= "$$$$$$$";
stringstream ss;
ss << sc;
string scs(ss.str());
for(int i=(scs.length());i<=6;i++)
    scs="0"+scs;
hud.replace(hud.find(scor),scor.length(),scs);//is "$$$$$$$" i taskus
}

void name(){        //zaidejo vardo rodymas
string snm= "PPPPPPPP";
for(int i=(nm.length());i<=7;i++)
    nm=nm+" ";
hud.replace(hud.find(snm),snm.length(),nm);
}

void input_inventory(){
    ifstream inputHud ("Hud.txt");
getline(inputHud, hud,'\r');
}

void show_inventory(){

    SetConsoleTextAttribute(color, 0x4e);//nustatoma spalva
    input_inventory();
    name();
    score();
    health();
    time();
cout<<hud;
}
};

void rikiavimas(){ //tasku rikiavimas didejimo tvarka
fstream outputScore;//failas kuriame skaitomi ir irasomi taskai

string score[100];
int z=0;
outputScore.open("Scores.txt",ios::in);//failas kuriame skaitomi ir irasomi taskai
while(outputScore.good()){
getline(outputScore,score[z],'\n');
z++;
}
z--;

outputScore.close();
sort(score, score + z, greater<string>());
//outputScore.open("Scores.txt", ios::out);//failas kuriame skaitomi ir irasomi taskai
ofstream outputScore1 ("Scores.txt");//failas kuriame skaitomi ir irasomi taskai
for(int i=0;i<z;i++)
outputScore1<<score[i]<<endl;
}

class MenuClass{    //meniu klase
    char inputKeyMenu;
public:
void start(){       //1 pasirinkimas, zaidimo pradzia
    system("cls");
cout<<"Iveskite zaidejo varda: \n";
cin>>setw(8)>>nm;       //leidziama ivesti varda iki 8 elementu
}

void scores(){  //2 pasirinkimas, taskai
    ifstream input ("Scores.txt");
        system("cls");
            cout<<"         SCORES \n\n\n";
            cout<<"Score"<<"\t"<<"Name"<<"\t"<<"Time\n\n";
        rikiavimas();
        string score;
        getline(input,score,'\r');
        cout<<score<<endl;
cout<<"\n\n";
cout<<"     [1] Exit";
inputKeyMenu=getch();
switch(inputKeyMenu){//gryzimas i pagrindini meniu
     case '1':
         Menu();
         break;
        default :
            scores();
}
}

void settings(){      //zaidimo nustatymai
    system("cls");
    cout<<"     SETTINGS ";
cout<<"\n\n";
cout<<"     [1] Sound: ";
if(sound==true){cout<<"On";}    //garso isjungimas
else{cout<<"Off";}
cout<<"\n\n";
cout<<"     [2] Exit";
inputKeyMenu=getch();
switch(inputKeyMenu){       //settings meniu pasirinkimas
     case '1':
         if(sound==true){sound=false;}
         else{sound=true;}
        settings();
         break;
     case '2':
         Menu();
         break;
        default :
            settings();
}
}

void Menu(){        //meniu
    SetConsoleTextAttribute(color, 0x0f);//meniu spalva

    system("cls");
    string smenu;
     ifstream inputMenu ("Menu.txt");
getline(inputMenu, smenu,'\r');         //meniu elementu nuskaitymas is failo
cout<<smenu;
inputKeyMenu=getch();

switch(inputKeyMenu){       //meniu pasirinkimai
     case '1':
         start();
         break;
     case '2':
         scores();
         break;
    case '3':
         settings();
         break;
    case '4':
        running=false;
         break;
        default :
            Menu();
}
}
};

void DeathFunc(){       //mirties funkcija
    ofstream outputScore ("Scores.txt", ios::app);//failas kuriame skaitomi ir irasomi taskai
    ifstream outputScore1 ("Scores.txt");//failas kuriame skaitomi ir irasomi taskai
    if(sound==true){
    Beep(300,400);      //mirties garsas
   Beep(250,400);
   Beep(200,400);}
     system("cls");
     cout<<"        YOU DIED!\n\n\n";
        cout<<"Player: "<<nm<<"\n\n"<<"Score: "<<sc<<"\n\n"<<"Time: "<<fixed<<setprecision(2)<<tt;
        cout<<"\n\n\n";

        stringstream ss;
        ss << sc;
        string scs(ss.str());
        for(int i=(scs.length());i<=6;i++)
        scs="0"+scs;

        outputScore<<scs<<" "<<nm<<" "<<fixed<<setprecision(2)<<tt<<endl;
        rikiavimas();

        _getch();
        cout<<"Score"<<"\t"<<"Name"<<"\t"<<"Time\n\n";
        string score;
        getline(outputScore1,score,'\r');
        cout<<score<<"\n\n";
        system("pause");
}

void win(){
    fstream outputScore ("Scores.txt", ios::app | ios::in | ios::out);//failas kuriame skaitomi ir irasomi taskai
    ifstream outputScore1 ("Scores.txt");//failas kuriame skaitomi ir irasomi taskai
    system("cls");
cout<<"          YOU WIN!!!\n\n\n";
cout<<"Player: "<<nm<<"\n\n"<<"Score: "<<sc<<"\n\n"<<"Time: "<<fixed<<setprecision(2)<<tt;
cout<<"\n\n\n";

        stringstream ss;
        ss << sc;
        string scs(ss.str());
        for(int i=(scs.length());i<=6;i++)
        scs="0"+scs;

        outputScore<<scs<<" "<<nm<<" "<<fixed<<setprecision(2)<<tt<<endl;

rikiavimas();
_getch();

cout<<"Score"<<"\t"<<"Name"<<"\t"<<"Time\n\n";
        string score;
        getline(outputScore1,score,'\r');
        cout<<score<<"\n\n";

system("pause");
}

typedef struct _CONSOLE_FONT_INFOEX
{
    ULONG cbSize;
    DWORD nFont;
    COORD dwFontSize;
    UINT  FontFamily;
    UINT  FontWeight;
    WCHAR FaceName[LF_FACESIZE];
}CONSOLE_FONT_INFOEX, *PCONSOLE_FONT_INFOEX;
//the function declaration begins
#ifdef __cplusplus
extern "C" {
#endif
BOOL WINAPI SetCurrentConsoleFontEx(HANDLE hConsoleOutput, BOOL bMaximumWindow, PCONSOLE_FONT_INFOEX
lpConsoleCurrentFontEx);
#ifdef __cplusplus
}
#endif
//the function declaration ends

void sriftas(){  //konsoles srifto keitimas
int
    newWidth=12,
    newHeight=16;
    CONSOLE_FONT_INFOEX fontStructure={0};
    fontStructure.cbSize=sizeof(fontStructure);
    fontStructure.dwFontSize.X=newWidth;
    fontStructure.dwFontSize.Y=newHeight;
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    SetCurrentConsoleFontEx(hConsole, true, &fontStructure);
}

void slepti(bool showFlag)              //kursoriaus slepimo funkcija
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}

void clearScreen()          //ekrano valymo funkcija, uzrasant ant virsaus
{
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}

void Maximise()         //lango didinimo funkcija
{
  HWND hWnd;
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD NewSBSize = GetLargestConsoleWindowSize(hOut);
  SMALL_RECT DisplayArea = {0, 0, 0, 0};

  SetConsoleScreenBufferSize(hOut, NewSBSize);

  DisplayArea.Right = NewSBSize.X - 1;
  DisplayArea.Bottom = NewSBSize.Y - 1;

  SetConsoleWindowInfo(hOut, TRUE, &DisplayArea);

  ShowWindow(hWnd, SW_MAXIMIZE);
}

int main()
{

    slepti(false);      //kursoriaus slepimas
Maximise();             //lango padidinimas
sriftas();
        char introS;              //intro ASCI-RPG
    ifstream intro ("Intro.txt");
    int xx=0;
    while(intro.good()){
        intro>>noskipws>>introS;
        if(introS=='$'){              //Spalvinimas:
                    SetConsoleTextAttribute(color, 0x6e);
                }
                else{SetConsoleTextAttribute(color, 0x0a);}
                cout<<introS;
    }
          //getline(intro,introS,'\r');

        _getch();

MenuClass menu;
Field player, npc, secret;
Inventory hud;
while(1==1){

system("cls");
menu.Menu();
if(running==false){return 0;}   //pasirinktinas isejimas is programos
player.input_field();
system("cls");

const clock_t begin_time = clock();//pradedamas laiko skaiciavimas

while(2==2){   //zaidimo ciklas
clearScreen();
player.show_field();//zaidimo laukas
hud.show_inventory();//zaidejo informacija
player.Move();      //zaidejo judejimas

tt=int( clock () - begin_time ) /  CLOCKS_PER_SEC;
tt=tt/60;

if (hp<=0){
        DeathFunc();
        break;}//zaidejo mirtis
if (winb==true){
        win();
        break;}
}
}
    return 0;
};
