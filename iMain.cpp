#include "iGraphics.h"
#include <string.h>



int screen_width=1100;
int screen_height=596;




int x = 0, y = 0, r = 0;
int cr=0;
int g=0;
int b=0;
int dx=10;
int dy=10;
int speed=0;
int bgspeed=speed;
#define basespeed 10
bool game_check=false;

int sum=0;
int score=0;
int point=0;
bool isscore=false;
int set_timer_change_3=95;

/* char up_bg[10][20]={"pic\\slice_1.bmp","pic\\slice_2.bmp","pic\\slice_3.bmp","pic\\slice_4.bmp","pic\\slice_5.bmp","pic\\slice_6.bmp","pic\\slice_7.bmp","pic\\slice_8.bmp","pic\\slice_9.bmp","pic\\slice_10.bmp"};
char base[10][30]={

     "pic\\vertical_slice_1.bmp",
	 "pic\\vertical_slice_2.bmp",
	 "pic\\vertical_slice_3.bmp",
	 "pic\\vertical_slice_4.bmp",
	 "pic\\vertical_slice_5.bmp",
	 "pic\\vertical_slice_6.bmp",
	 "pic\\vertical_slice_7.bmp",
	 "pic\\vertical_slice_8.bmp",
	 "pic\\vertical_slice_9.bmp",
	 "pic\\vertical_slice_10.bmp"

}; */
char bg[11][30]={

     "pic\\bi1.bmp",
	 "pic\\bi2.bmp",
	 "pic\\bi3.bmp",
	 "pic\\bi4.bmp",
	 "pic\\bi5.bmp",
	 "pic\\bi6.bmp",
	 "pic\\bi7.bmp",
	 "pic\\bi8.bmp",
	 "pic\\bi9.bmp",
	 "pic\\bi10.bmp",
	 "pic\\bi11.bmp",

}; 

char chr_run[6][20]={
         "pic\\r1.bmp",
		 "pic\\r2.bmp",
		 "pic\\r3.bmp",
		 "pic\\r4.bmp",
		 "pic\\r5.bmp",
		 "pic\\r6.bmp"
};

int chr_run_idx=0;

/* char chr_jump[8][20]={
	"pic\\jump1.bmp",
	"pic\\jump2.bmp",
	"pic\\jump3.bmp",
	"pic\\jump4.bmp",
	"pic\\jump5.bmp",
	"pic\\jump6.bmp",
	"pic\\jump7.bmp",
	"pic\\jump8.bmp",

};
      int jump_idx=0; */
 char bg_cactus[8][20]={"pic\\ct1.bmp","pic\\ct2.bmp",
        "pic\\ob3.bmp",
		"pic\\ob1.bmp",
		"pic\\ct7+.bmp",
		"pic\\nc2.bmp",
		"pic\\ob2.bmp",
		"pic\\ob3.bmp"
 
 
 
 };


struct background
{
	int x;
	int y;
};
background upper_background[11];
background cactus[8];


typedef struct         //structure for leaderboard
{
	char name[20];
	int score;

}player;

player arr[100];
int line=0;





 char player_name[20];
 int name_length=0;
 int input=0;
 

int idx=0;

//
 bool isjumping=false;
int jumpheight=0;
int v=43;
int jumpvelocity=v;
int gravity=-5; 
//int jump_idx=0;
int sum2=1000;
/* 
bool isjumping=false;
int jumpY=20;
int baseY=20;
int maxheight=230;
int jumpspeed=25; */

int game_state=0;
// int arr[100];
int top_scorer[5];

FILE *fp=fopen("score.txt","a");           //openning append or write file
FILE *fr=fopen("score.txt","r");
FILE *fp_w=fopen("score_leader.txt","w");
FILE *fr_w=fopen("score_leader.txt","r");

void show_leaderboard()
{

    if(line<5)
	{
         for(int i=0;i<line;i++)
		 {

		   iText(500,450-i*50,arr[i].name,GLUT_BITMAP_TIMES_ROMAN_24);

		   char score_shown_string[10];
		   sprintf(score_shown_string,"%d",arr[i].score);
		   iText(600,450-i*50,score_shown_string,GLUT_BITMAP_TIMES_ROMAN_24);
		 }
	}
    
	else
	{
		for(int i=0;i<5;i++)
	{
		
			  
		iText(500,450-i*50,arr[i].name,GLUT_BITMAP_TIMES_ROMAN_24);

		char score_shown_string[10];
		sprintf(score_shown_string,"%d",arr[i].score);
		iText(600,450-i*50,score_shown_string,GLUT_BITMAP_TIMES_ROMAN_24);
	}
	}
	// int taken_score;
	// int i=0;
	// while(fscanf(fr_w,"%d",&taken_score)!=EOF)
	// {
		
	// 	char score_shown_string[10];
	//     sprintf(score_shown_string,"%d",taken_score);
			  
	// 	iText(500,450-i*50,score_shown_string,GLUT_BITMAP_TIMES_ROMAN_24);
	// 	i++;
		
	// }
}

bool Music=true;

void iDraw()
{
	// place your drawing codes here
	iClear();
	if(game_state==1)
	{
        
		iShowBMP(0,0,"pic\\bi.bmp");
	
	for(int i=0;i<11;i++){
		iShowBMP(upper_background[i].x,upper_background[i].y,bg[i]);
		
		
	} 

    char score_string[10];
	sprintf(score_string,"%d",score);
	iText(545,475,score_string,GLUT_BITMAP_HELVETICA_18);
   
	


	for(int i=0;i<8;i++){
		iShowBMP2(cactus[i].x,cactus[i].y,bg_cactus[i],0);
	}

	   if(isjumping){
         iShowBMP2(100,80+jumpheight,"pic\\aj.bmp",0);
	}
	else{
		iShowBMP2(100,80,chr_run[chr_run_idx],0);
	} 
	
	iShowBMP(0,0,"pic\\bi1.bmp");


	iText(500,540,"Your Score",GLUT_BITMAP_TIMES_ROMAN_24);
	
	    
		iEllipse(560,480,80,40);
		
		iSetColor(0,255,0);

	if(game_check==true){
		//iRectangle(500,450,150,50);
		iSetColor(255,0,0);
		
		//iFilledRectangle(500,450,100,50);
		iText(480,400,"GAME OVER",GLUT_BITMAP_TIMES_ROMAN_24);

		//iShowBMP2(480,330,"pic\\pa.bmp",0);
		
		iShowBMP2(500,260,"pic\\exit.bmp",0);
		iSetColor(255,255,0);
		iRectangle(698,270,183,35);
		iFilledRectangle(698,270,183,35);
		iSetColor(0,0,204);
		iText(700,280,"LEADERBOARD",GLUT_BITMAP_TIMES_ROMAN_24);
		
	}
	
	}

	else if(game_state==0)
	{
		
		
		iSetColor(255,0,0);
		iShowBMP(0,0,"pic\\home4.bmp");
		iShowBMP2(700,150,"pic\\play.bmp",0);

		iText(350,500,"WELCOME TO MY GAME",GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(255,255,0);
		iSetColor(255,255,102);
		iFilledRectangle(200,150,200,40);
		iSetColor(0,255,0);
		iText(200,200,"Input Your Name:",GLUT_BITMAP_TIMES_ROMAN_24);
		
		if(input)
		{
			iText(205,155,player_name,GLUT_BITMAP_TIMES_ROMAN_24);
		}
		else
		{
			iText(205,155,player_name,GLUT_BITMAP_TIMES_ROMAN_24);
		}


		
		
		
		
	}
	else if(game_state==-1){
		  
		  

		  iSetColor(153,255,255);
          iFilledRectangle(0,0,1100,596); 
		  iSetColor(0,0,204);
		  iLine(440,510,610,510);
		  iText(440,520,"TOP 5 SCORES",GLUT_BITMAP_TIMES_ROMAN_24);

		  iSetColor(0,255,0);
		  iRectangle(428,10,150,40);
		  iFilledRectangle(428,10,150,40);
		  iSetColor(255,0,0);
		  iText(430,20,"QUIT GAME",GLUT_BITMAP_TIMES_ROMAN_24);
          
		  show_leaderboard();
		  

		  

		     
		  
	}


	
	
	
	
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my)
{
	/*  printf("x = %d, y= %d\n", mx, my);
	x=mx-200;
	y=my+10; 
	// place your codes here
} */
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouse(int button, int state, int mx, int my)
{

	 if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		// place your codes here
		//	printf("x = %d, y= %d\n",mx,my);
		if(mx>=700 && mx <=810 && my>=150 && my<=205 && game_state!=1)
		{
			bgspeed=10;
			game_state=1;
			isscore=true;
		}
		/* if(mx>=480 && mx<=615 && my>=330 && my<=362)
		{
			
			
			game_state=1;
			game_check=false;
			
			
			
			
		} */
		if(mx>=510 && mx<=597 && my>=260 && my<=297)
		{
			exit(0);
		}

		if(mx>=698 && mx<=881 && my >=270 && my<=305)
		{
			game_state=-1;
		}

		if(mx>=428 && mx<=578 && my >=10 && my <=50)
		{
			exit(0);
		}

		
		
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		// place your codes here
		
		
	}  
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key)
{
	if(!input)
	{
	   if(key=='\r')       //\r indicates the end of taking input
	   {
		  input=1;
		  fprintf(fp,"%s ",player_name);
	   }
	   else if(key=='\b')      //used to delete character
	   {
		  if(name_length>0)
		  {
			 name_length--;
			 player_name[name_length]='\0';
		  }
	   }

	   else
	   {
		  if(name_length<19)
		  {
			player_name[name_length]=key;
			name_length++;
			player_name[name_length]='\0';
		  }
	   }
	}


	   if(key==' '){
		  if(!isjumping){
			isjumping=true;
			jumpvelocity=v;
			
		  }
	   }
	   
	   //if(key=='n')iShowBMP(0,0,"D:\\BUET 1-1 Project\\images.bmp");
		/* if (key == GLUT_KEY_UP)
		{
			y+=10;
		}
		if(key==GLUT_KEY_RIGHT)x+=10;
		if(key=='c')y-=10;
		if(key=='a')x-=10;
		if(key=='r'){
			cr=255;
			g=0;
			b=0;
		}
		if(key=='g'){
			cr=0;
			g=255;
			b=0;
		}
		if(key=='b'){
			cr=0;
			g=0;
			b=255;
		} */

	// place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
	*/
void iSpecialKeyboard(unsigned char key)
{

	if(key==GLUT_KEY_UP)y+=10;
	if(key==GLUT_KEY_DOWN)y-=10;
	/* if(key==GLUT_KEY_RIGHT){
		//img_x+=10;
		idx++;
		if(img_x>=5)idx=0;
		standposition=0;
	}
	if(key==GLUT_KEY_LEFT){
		img_x-=10;
		idx--;
		if(img_x<=0)idx=4;
		standposition=0;
	} */
	if(key=GLUT_KEY_HOME){
		cr=0;
		g=255;
		b=0;
	}
	if(key==GLUT_KEY_INSERT){
		cr=0;
		g=0;
		b=255;
	}
	// place your codes for other keys here
}
bool musicOn=true;

/* void change(){
	/* x+=dx;
	y+=dy;
	if(x>=800 || x<=0)dx*=(-1);
	if(y>=600 || y<=0)dy*=(-1); */
	/* img_x++;
	idx++;
	
	if(idx>=5)idx=0; */


 void setAll(){
	
	for(int i=0;i<11;i++){
         upper_background[i].y=0;
		
		 upper_background[i].x=sum;
		 
		 sum+=100;
		 
	}
	
	for(int i=0;i<8;i++){
		if(i==1)
		{
			sum2+=50;
		}
		if(i==2){
			sum2+=300;
		}
		if(i==3){
			sum2+=100;
		}
		if(i==4){
			sum2+=150;
		}
		if(i==5){
		   sum2+=100;
		}
		if(i==6)
		{
			sum2+=100;
		}
		if(i==7){
			sum2+=200;
		}
		cactus[i].y=80;
		cactus[i].x=sum2;
		sum2+=400;
	}
}
int count=0;
int sp=50;

bool fo=false;

 void score_calc(){
	
	if(isscore)score++;
	if(score>=50 && score<=99)
	{
		bgspeed=11;
	}
	else if(score>=100 && score<=149)
	{
		bgspeed=12;
		gravity=-6;
	}
	else if(score>=150 && score<=199)
	{
		bgspeed=13;
		gravity=-6;
		set_timer_change_3=110;
	}
	else if(score>=200 && score<=249)
	{
		bgspeed=14;
		gravity=-6;
		set_timer_change_3=110;
		
	}
	if(score>=250 && score <=299)
	{
		bgspeed=15;
		gravity=-7;
		set_timer_change_3=110;
	}
	if(score>=300 && score<=400)
	{
		bgspeed=17;
		gravity=-7;
		set_timer_change_3=120;
	}
	else if(score>=401 && score<=500){
		bgspeed=20;
		gravity=-8;
		set_timer_change_3=125;
	}
} 

void score_leader()
{

      
     





    
   

   

   
   
   char string[100];
   
   while(fgets(string, sizeof(string), fr)!=NULL){
	    if(strlen(string)<=1)continue;
        int count=0;
        int k=0;
        
	   
	   for(int j=0;j<=strlen(string);j++){
		   if(string[j]==' ' || string[j]=='\0'|| string[j]=='\n'){
              count++;
              if(count==1)
               {
                 
                 char temp[20];
                 int y=0;
                 for(int x=k;x<j;x++)
                 {
                   temp[y++]=string[x];
                 }
                 temp[y]='\0';
                 strcpy(arr[line].name,temp);
                 k=j+1;
               }
               if(count==2)
               {
                   int num=0;
                   for(int x=k;x<j;x++)
                   {
                       num=num*10+(string[x]-'0');
                   }
                   arr[line].score=num;
                   line++;
                   k=j+1;
                   
                   

               }
           }
	   }
	   
   }
   
   for(int i=0;i<line-1;i++){
      int flag=0;
      for(int j=0;j<line-i-1;j++){
         if(arr[j].score<arr[j+1].score){
            int temp=arr[j].score;
            char s[20];
            strcpy(s,arr[j].name);
            arr[j].score=arr[j+1].score;
            strcpy(arr[j].name,arr[j+1].name);
            arr[j+1].score=temp;
            strcpy(arr[j+1].name,s);
            flag=1;
         }

      }
      if(flag==0)break;
   }
   
//    for(int i=0;i<line;i++){
//       fprintf(fp)
//    }
   

   fclose(fr);













	// int score_read;
		
	// 	int x=0;
		
	// 	  while(fscanf(fr,"%d",&score_read)!=EOF){
			  
	// 		  arr[x++]=score_read;
	// 	  }
	// 	  for(int i=0;i<x-1;i++)
	// 	  {
	// 		 int flag=0;
	// 		 for(int j=0;j<x-1-i;j++)
	// 		 {
	// 			if(arr[j]<arr[j+1])
	// 			{
	// 				int temp=arr[j];
	// 				arr[j]=arr[j+1];
	// 				arr[j+1]=temp;
	// 				flag=1;
	// 			}
	// 		 }
	// 		 if(flag==0)break;
	// 	  }
	// 	  for(int i=0;i<x;i++)
	// 	  {
			  
	// 		  fprintf(fp_w,"%d\n",arr[i]);
	// 	  }
	// 	  fclose(fp_w);
		  
}



 void stack()
{
	fprintf(fp,"%d\n",score);
	
	
	fclose(fp);
	score_leader();
	
} 


void gameover(){
	
	 iPauseTimer(0);
	iPauseTimer(1);
	iPauseTimer(2); 
	iPauseTimer(3);
	// fprintf(fp,"%d",score);
	game_check=true;
	
	stack(); 
	
	/* game_state=-1;
	bgspeed=0; */
}



void change(){
    

        /* for(int i=0;i<11;i++)
		{   if(upper_background[i].x)
		         upper_background[i].x=upper_background[i].x-100;
            else 
			    upper_background[i].x=1000;

		} */

	for(int i=0;i<11;i++){
		upper_background[i].x-=bgspeed;
		
	 	if(upper_background[i].x<=0)upper_background[i].x=1100-12;
	 	//if(lower_background[i].x<=0)lower_background[i].x=screen_width-10;

		
	}
	for(int i=0;i<8;i++){
		
		  if((cactus[0].x<=210 &&cactus[0].x>=103 && jumpheight<=95))
		{
			gameover();

		}	
		 
		
         if(cactus[1].x<=210 && cactus[1].x>=102)//210
		{
			//if(cactus[1].x<=210 && cactus[1].x>=190 && jumpheight<=20)gameover();
			
             if(jumpheight<=83-10)gameover();
		} 

		 if(cactus[2].x<=210 && cactus[2].x>=103)//210
		{
			if(jumpheight<=100)gameover();
		} 

		if(cactus[3].x<=210 && cactus[3].x>=103)//210
		{
			
            if(jumpheight<=110-10)gameover();
		} 
		if(cactus[4].x<=215 && cactus[4].x>=103)//215
		{
             if(jumpheight<=68-10)gameover();
		}
		//start
		if(cactus[5].x<=200 && cactus[5].x>=103)//200
		{
             if(jumpheight<=135)gameover();
		}
		if(cactus[6].x<=210 && cactus[6].x>=103)//200
		{
             if(jumpheight<=140)gameover();
		}
		if(cactus[7].x<=210 && cactus[7].x>=103)
		{
             if(jumpheight<=95)gameover();
		} 
        cactus[i].x-=bgspeed;
		if(cactus[i].x<=0)cactus[i].x=4600;
		
		
        
	}
	
}
 void change2(){
	chr_run_idx++;
		if(chr_run_idx>=6)
		chr_run_idx=0;

} 
void change3(){
	/* if(isjumping){
		jumpY+=jumpspeed;
		if(jumpY>=baseY+maxheight){
			jumpspeed=-jumpspeed;
		}
		if(jumpY<=baseY){
            jumpY=baseY;
			isjumping=false;
			jumpspeed=abs(jumpspeed);
			
		}
	} */
    if(isjumping)
	{
		jumpheight+=jumpvelocity;
		jumpvelocity+=gravity;
		if(jumpheight<=0)
		{
			jumpheight=0;
			jumpvelocity=v;
			isjumping=false;
		}
	}
}




int main()
{
	
	if(fp==NULL || fr==NULL || fp_w==NULL){
	exit(1);
    }
    
	player_name[0]='\0';
	// if(Music)
	// 	PlaySound("ms1.wav", NULL, SND_FILENAME | SND_ASYNC);
    
	setAll();
	// place your own initialization codes here.
	
		iSetTimer(50,change);
		
			iSetTimer(set_timer_change_3,change3);
		
			iSetTimer(100,change2);
			
				iSetTimer(250,score_calc);
			
		
	
	
	//iSetTimer(100,change2);
	
	
	    // if(Music)
		// PlaySound(TEXT("music\\ms1.wav"), NULL, SND_ASYNC);
	
	iInitialize(screen_width, screen_height, "Game Project");
	return 0;
}
