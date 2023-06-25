# include "iGraphics.h"
#include<string.h>
#include<math.h>
#define numberobs 10
#define obsspeed 10
#define jumplimit 50
#define indexhigh 10

int timer=50;
int x=300,y=300;
	///creating the background

char bc[10][20]={"background.bmp"};

///creating the obstacle

char go_obs[10][20]={"obstacle.bmp","obstacle1.bmp", "obstacle3.bmp", "obstacle2.bmp","obstacle4.bmp","obstacle5.bmp","obstacle6.bmp"};

///creating the obstacle

char up_obs[10][20]={"obstacle.bmp","obstacle1.bmp", "obstacle2.bmp", "obstacle3.bmp","obstacle4.bmp","obstacle5.bmp","obstacle6.bmp"};

///creating the bird

char bird[10][20]={"bird.bmp","bird.bmp","bird1.bmp" ,"bird2.bmp","bird3.bmp","bird4.bmp","bird5.bmp","bird6.bmp","bird7.bmp"};

///creating bird obstacle
char obs_bird[10][20]={"birdobs1.bmp", "birdobs2.bmp","birdobs3.bmp","birdobs4.bmp","birdobs5.bmp","birdobs6.bmp","birdobs7.bmp","birdobs8.bmp"};

char birdStand[10]={"bird.bmp"};
char over[10][20]={"gameover.bmp"};

char hightab[10][20]={"hightab.bmp"};
///creating main menu
int highscore=0;
char home[10][20]={"homepage.bmp"};
char start[10][20]={"startbutton.bmp"};
char high[10][20]={"highscore.bmp"};
char us[10][20]={"us.bmp"};
char quit[10][20]={"quit.bmp"};
char more[10][20]={"more.bmp"};
char word[10][20]={"words.bmp"};
char aboutus[10][20]={"usvaius.bmp"};
char button[10][20]={"button.bmp"};
int phase=0;
char scoreboard[10][20]={"score.bmp"};
char score1[10];
char score2[10];
int score=0;
bool stop=false;

bool jump=false;

char str[200];
int indexstr=0;

struct obs{
int obs_x;
int obs_y;
};

struct birds{
int bird_x;
int bird_y;
int bird_index=0;
bool bird_show;
};
obs go[numberobs];
obs goup[numberobs];
birds birdobs;

bool ready=false;

bool birdstand=true;
int birdcounter=0;

int  birdx=0;
int  birdy=300;
int birdIndex=0;
int bg=0;

void Score(){
         if(stop==false){
                if(ready==true){
    score+=1;
    if(score>=10&&score<=50){
        timer=30;
    }
    if(score>50){
        timer=20;
    }
    itoa(score,score1,10);
    iText(1087,575,score1,GLUT_BITMAP_HELVETICA_18);
 }}
if(stop==true&&phase==1){

   score=score;
      if(score>highscore){
  highscore=score;
   FILE *fp=fopen("highscores.txt","w");
    fprintf(fp,"%d",highscore);
    fclose(fp);
      }
    itoa(score,score1,10);
    iText(1090,525,score1,GLUT_BITMAP_HELVETICA_18 );
   birdobs.bird_x=1400;
//system("Cla");
}}
int highscoress(){

FILE *fp =fopen("highscores.txt","r");
   fscanf(fp,"%d",&highscore);
       itoa(highscore,score2,10);
       fclose(fp);
      iText(670,400,score2,GLUT_BITMAP_TIMES_ROMAN_24 );
}

void collisoncheck(){
    for(int i=0;i<6;i++){
if((birdx+50>=go[i].obs_x&&birdx<=go[i].obs_x)&&birdy<=226){

stop=true;

}
 else  if((birdx+50>=goup[i].obs_x&&birdx<=goup[i].obs_x)&&birdy>=342){

stop=true;
}


    }
    if((birdx+50>=birdobs.bird_x&&birdx<=birdobs.bird_x)&&birdy+65>=300&&birdy<=365){
        stop=true;
        birdobs.bird_x=1500;
    }
    }

void iDraw() {
	iClear();
	if(phase==0){
        iShowBMP(0,0,home[bg]);
        iShowBMP2(400,70,us[bg],0);
        iShowBMP2(600,70,high[bg],0);
        iShowBMP2(600,150,start[bg],0);
        iShowBMP2(800,70,word[bg],0);

	}
	if(phase==1){
iShowBMP(0,0,bc[bg]);

if(stop==false){
        iShowBMP2(1000,540,scoreboard[bg],0);
        Score();
        if(jump){
         iShowBMP2(birdx,birdy,bird[birdIndex],16777215);
    birdcounter++;
    if(birdcounter>=20){
        birdcounter=0;
        birdIndex=0;
        birdstand=true;
    }
           }
            else{
    if(!birdstand){
    iShowBMP2(birdx,birdy,bird[birdIndex],16777215);
    birdcounter++;
    if(birdcounter>=20){
        birdcounter=0;
        birdIndex=0;
        birdstand=true;
    }
}
else{
      iShowBMP2(birdx,birdy,birdStand,16777215);
}
}

for(int i=0;i<6;i++){
        int x=rand()%6;
    iShowBMP2(go[i].obs_x, go[i].obs_y,go_obs[x],0);
    iShowBMP2(goup[i].obs_x, goup[i].obs_y,up_obs[x],0);
}

for(int i=0;i<8;i++){
    iShowBMP2(birdobs.bird_x, birdobs.bird_y,obs_bird[birdobs.bird_index],16777215);
}
}
else{
iShowBMP2(80,200,over[bg],0);
iShowBMP2(1120,50,quit[bg],16777215);
iShowBMP2(1000,490,scoreboard[bg],0);
Score();
}
}

if(phase==4){
  iShowBMP(0,0,more[bg]);
  iShowBMP2(1100,500,quit[bg],0);
}
if(phase==3){
    iShowBMP(35,0,aboutus[bg]);
    iShowBMP2(100,500,button[bg],16777215);
}

if(phase==2){
      iShowBMP(100,0,hightab[bg]);
iText(400,400,"YOUR HIGHSCORE IS:",GLUT_BITMAP_TIMES_ROMAN_24);
    highscoress();
 iShowBMP2(1100,500,button [bg],0);
}
}


///idraw function end


void iMouseMove(int mx, int my) {
	printf("x = %d, y= %d\n",mx,my);
	//place your codes here
}

void iMouse(int button, int state, int mx, int my) {
    if((mx>=600 &&mx<=746)&&(my>=150 && my<=210)){
        phase=1;
              birdx=0;
        birdy=300;
    }
     if((mx>=600 && mx<=749)&&(my>=70 &&my<=130)){
        phase=2;
    }
    if((mx>=400 && mx<=549)&&(my>=70 &&my<=130)){
        phase=3;
    }
        if((mx>=800 && mx<=947)&&(my>=70 &&my<=130)){
        phase=4;
    }
    if(phase==3){
        if((mx>=100&&mx<=160)&&(my>=500&&my<=560)){
            phase=0;
        }
    }
/*    if((mx>=1020 && mx<=1167)&&(my>=70&&my<=130)){
        phase=4;
    }*/
     if(phase==4) {
            if((mx>=1000 && mx<=1147)&&(my>=500&&my<=560)){
        phase=0;

    }
    }

    if(phase==2){
              if((mx>=1100 && mx<=1247)&&(my>=500&&my<=560)){
        phase=0;

    }}
    if(stop==true){
       if((mx>=1120 && mx<=1266)&&(my>=50 &&my<=110)){
        phase=0;
        stop=false;
        ready=false;
        score=0;

    }
    }

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		//place your codes here
		//	printf("x = %d, y= %d\n",mx,my);
		x += 10;
		y += 10;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		//place your codes here
		x -= 10;
		y -= 10;
	}
}


void iKeyboard(unsigned char key) {

   if(key==13){
    str[indexstr]='\0';
   }
else if(key !='\b'){
    str[indexstr]=key;
      indexstr++;
    str[indexstr]='\0';
}
else{
    if(indexstr<=0){
        indexstr=0;
    }
   else{
    indexstr--;
   }
   }
   }
void iSpecialKeyboard(unsigned char key) {

	if (key == GLUT_KEY_UP) {
           jump=true;
           birdy+=10;
           birdIndex++;
  if(birdIndex>=8){
        birdIndex=0;
    }
    if(birdy>535){
        birdy=535;
    }
    collisoncheck();
   birdstand=false;
    ready=true;
	}
else if(key==GLUT_KEY_DOWN){
birdy-=10;
    birdIndex++;
    if(birdIndex>=8){
        birdIndex=0;
    }
    if(birdy<0){
        birdy=0;
    }
collisoncheck();
   birdstand=false;
 ready=true;
}
else if(key==GLUT_KEY_LEFT){
    birdx-=10;
    birdIndex++;
    if(birdIndex>=8){
        birdIndex=0;
    }
    if(birdx<0){
        birdx=0;
    }
    collisoncheck();
   birdstand=false;
   ready=true;
}
else if(key==GLUT_KEY_RIGHT){
    birdx+=10;
    birdIndex++;
    if(birdIndex>=8){
        birdIndex=0;
    }
    if(birdx>1220){
        birdx=1220;
    }
    collisoncheck();
     birdstand=false;
    ready=true;
}
}
void change(){
if(ready==true){
 for(int i=0;i<6;i++){
    go[i].obs_x-=obsspeed;
    goup[i].obs_x-=obsspeed;
    if(go[i].obs_x<=0){
        go[i].obs_x=1300;
    }
     if(goup[i].obs_x<=0){
        goup[i].obs_x=1300;
    }
 }
 collisoncheck();
 }
 }
void change1(){
if(ready){
birdobs.bird_x-=10;
 if(birdobs.bird_x<0){
    birdobs.bird_x=1300;
 }
 birdobs.bird_index++;
 if(birdobs.bird_index>=8){
    birdobs.bird_index=0;
 }
 collisoncheck();
}
}

 void changejump(){
    if(jump){
            birdy-=5;
            if(birdy<=0){
                jump=false;
          birdy=0;
            }

            }
collisoncheck();
    }
void setAll(){
int sum=0;
for(int i=0;i<6;i++){
    go[i].obs_y=0;
    go[i].obs_x=sum+600;
  goup[i].obs_y=374;
    goup[i].obs_x=400+sum;
     sum=sum+800;
   if(sum>1300){
        sum=0;
     }
}
birdobs.bird_x=1400+rand()%100;
birdobs.bird_y=300;
birdobs.bird_index=rand()%10;
birdobs.bird_show=true;
collisoncheck();
}
int main() {
 setAll();
     iSetTimer(70,change);
     iSetTimer(10,change1);
     iSetTimer(05,changejump);
	iInitialize(1300, 600, "Flappy Birds");
	return 0;
}
