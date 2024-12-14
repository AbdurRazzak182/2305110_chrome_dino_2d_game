#include "iGraphics.h"
#include <string.h>

int screen_width = 1100;
int screen_height = 596;
int speed = 0;
int bgspeed = speed;
bool game_check = false;
int sum = 0;
int score = 0;
int point = 0;
bool isscore = false;
int set_timer_change_3 = 85;

char bg[11][30] = {

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

char chr_run[6][20] = {
	"pic\\r1.bmp",
	"pic\\r2.bmp",
	"pic\\r3.bmp",
	"pic\\r4.bmp",
	"pic\\r5.bmp",
	"pic\\r6.bmp"};

int chr_run_idx = 0;

char bg_cactus[8][20] = {"pic\\ct1.bmp",
						 "pic\\ct2.bmp",
						 "pic\\ob3.bmp",
						 "pic\\ob1.bmp",
						 "pic\\ct7+.bmp",
						 "pic\\nc2.bmp",
						 "pic\\ob2.bmp",
						 "pic\\ob3.bmp"

};

struct background      //structure for background images and obstacles images
{
	int x;
	int y;
};
background upper_background[11];
background cactus[8];

typedef struct // structure for leaderboard
{
	char name[20];
	int score;

} player;

player arr[100];      //structural array where player name and their score is added and sorted and shown screen
int line = 0;

char player_name[20];
int name_length = 0;
int input = 0;

int idx = 0;

bool isjumping = false;
int jumpheight = 0;
int v = 43;
int jumpvelocity = v;
int gravity = -5;
int sum2 = 1000;

int game_state = 0;

int top_scorer[5];

FILE *fp = fopen("score.txt", "a"); // openning append or write file
FILE *fr = fopen("score.txt", "r");

void show_leaderboard()
{

	if (line < 5)
	{
		for (int i = 0; i < line; i++)
		{

			iText(460, 450 - i * 50, arr[i].name, GLUT_BITMAP_TIMES_ROMAN_24);

			char score_shown_string[10];
			sprintf(score_shown_string, "%d", arr[i].score);
			iText(600, 450 - i * 50, score_shown_string, GLUT_BITMAP_TIMES_ROMAN_24);
		}
	}

	else
	{
		for (int i = 0; i < 5; i++)
		{

			iText(460, 450 - i * 50, arr[i].name, GLUT_BITMAP_TIMES_ROMAN_24);

			char score_shown_string[10];
			sprintf(score_shown_string, "%d", arr[i].score);
			iText(600, 450 - i * 50, score_shown_string, GLUT_BITMAP_TIMES_ROMAN_24);
		}
	}
}

bool Music = true;
bool Jump_music = true;
bool collision_music = true;

void iDraw()
{

	iClear();
	if (game_state == 1)//main playing state where jump ,run , backgronund rendering and cactus rendering ,start from mouse condition 1
	{

		iShowBMP(0, 0, "pic\\bi.bmp");

		for (int i = 0; i < 11; i++)
		{
			iShowBMP(upper_background[i].x, upper_background[i].y, bg[i]);
		}

		char score_string[10];
		sprintf(score_string, "%d", score);
		iText(545, 475, score_string, GLUT_BITMAP_HELVETICA_18);

		for (int i = 0; i < 8; i++)
		{
			iShowBMP2(cactus[i].x, cactus[i].y, bg_cactus[i], 0);
		}

		if (isjumping)
		{

			iShowBMP2(100, 80 + jumpheight, "pic\\aj.bmp", 0);
		}
		else
		{
			iShowBMP2(100, 80, chr_run[chr_run_idx], 0);
		}

		iShowBMP(0, 0, "pic\\bi1.bmp");

		iText(500, 540, "Your Score", GLUT_BITMAP_TIMES_ROMAN_24);

		iEllipse(560, 480, 80, 40);

		iSetColor(0, 255, 0);

		if (game_check == true)
		{
			Music = true;

			PlaySound("sound\\ms1.wav", NULL, SND_LOOP | SND_ASYNC);

			iSetColor(255, 0, 0);

			iText(480, 400, "GAME OVER", GLUT_BITMAP_TIMES_ROMAN_24);

			iShowBMP2(500, 260, "pic\\exit.bmp", 0);
			iSetColor(255, 255, 0);
			iRectangle(698, 270, 183, 35);
			iFilledRectangle(698, 270, 183, 35);
			iSetColor(0, 0, 204);
			iText(700, 280, "LEADERBOARD", GLUT_BITMAP_TIMES_ROMAN_24);
		}
	}

	else if (game_state == 0)  //home menu 
	{

		iSetColor(0, 255, 255);
		iFilledRectangle(0, 593, 1100, 3);
		iSetColor(255, 0, 0);
		iShowBMP(0, 0, "pic\\home4.bmp");
        iSetColor(255,0,0);
		iText(400, 520, "WELCOME  TO  MY  GAME", GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(0,0,255);
		iText(450, 480, "CHROME__CAT", GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(255, 255, 0);
		iSetColor(255, 255, 255);
		iFilledRectangle(200, 150, 200, 40);
		iSetColor(0, 255, 0);
		iText(200, 200, "Input Your Name:", GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(0, 0, 0);
		if (input)
		{
			iText(205, 165, player_name, GLUT_BITMAP_TIMES_ROMAN_24);
		}
		else
		{
			iText(205, 165, player_name, GLUT_BITMAP_TIMES_ROMAN_24);
		}

		iSetColor(255, 255, 153);
		iFilledRectangle(200, 50, 200, 40);
		iSetColor(0, 0, 255);
		iText(220, 63, "INSTRUCTIONS", GLUT_BITMAP_HELVETICA_18);

		iSetColor(255, 255, 153);
		iFilledRectangle(700, 50, 200, 40);
		iSetColor(0, 0, 255);
		iText(750, 63, "ABOUT ME", GLUT_BITMAP_HELVETICA_18);

		iSetColor(255, 255, 153);
		iFilledRectangle(470, 100, 150, 40);
		iSetColor(0, 0, 255);
		iText(490, 113, "QUIT GAME", GLUT_BITMAP_HELVETICA_18);

		iSetColor(255, 255, 153);
		iFilledRectangle(700, 150, 100, 40);
		iSetColor(0, 0, 255);
		iText(720, 163, "PLAY", GLUT_BITMAP_HELVETICA_18);
	}
	else if (game_state == -1)  //leaderboard show
	{

		iSetColor(153, 255, 255);
		iFilledRectangle(0, 0, 1100, 596);
		iSetColor(0, 0, 204);
		iLine(440, 510, 610, 510);
		iText(440, 520, "TOP 5 SCORES", GLUT_BITMAP_TIMES_ROMAN_24);

		iSetColor(0, 255, 0);
		iFilledRectangle(470, 100, 150, 40);
		iSetColor(0, 0, 255);
		iText(490, 113, "QUIT GAME", GLUT_BITMAP_HELVETICA_18);
		iSetColor(255, 0, 255);
		show_leaderboard();
	}

	else if (game_state == 5) // instruction page
	{
		iSetColor(255, 255, 204);
		iFilledRectangle(0, 0, 1100, 596);
		iSetColor(255, 0, 0);
		iRectangle(480, 10, 150, 40);
		iSetColor(255, 0, 255);
		iText(495, 23, "BACK HOME", GLUT_BITMAP_HELVETICA_18);
		iSetColor(0, 0, 255);
		iText(100, 520, "Some  Rules  For  Playing -", GLUT_BITMAP_HELVETICA_18);
		iText(100, 470, "1. Firstly,  you  have  to  sign  up  your name  without  space  and  press  \"ENTER\"  at  the  end.", GLUT_BITMAP_HELVETICA_18);
		iText(100, 440, "2. Then  you  can  visit  \"ABOUT ME\"  to  know  about  the  game  maker.", GLUT_BITMAP_HELVETICA_18);
		iText(100, 410, "3. After  that,  you  can  go  playing  pressing  \"PLAY\"  button.", GLUT_BITMAP_HELVETICA_18);
		iText(100, 380, "4. During  the  time  of  playing  if  you  can  see  obstacle   as  cactus  or  stone  or  something  then  press  \"SPACE\"", GLUT_BITMAP_HELVETICA_18);
		iText(100, 350, "   button  to  give  proper  jump.", GLUT_BITMAP_HELVETICA_18);
		iText(100, 320, "5. When  the  cat  collides  with  the  obstacles  then  the  game  will  be  ended  and  you  can  show  then  your  score.", GLUT_BITMAP_HELVETICA_18);
		iText(100, 290, "6. If  you  can  do  a  score  among  top  5  scorer  then  you  can  show  your  position  in  leaderboard.", GLUT_BITMAP_HELVETICA_18);
	}

	else if (game_state == 6)   //about me page
	{
		iSetColor(153, 255, 204);
		iFilledRectangle(0, 0, 1100, 596);
		iSetColor(255, 0, 0);
		iRectangle(480, 10, 150, 40);
		iSetColor(255, 0, 255);
		iText(495, 23, "BACK HOME", GLUT_BITMAP_HELVETICA_18);
		iSetColor(0, 0, 255);
		iShowBMP(430, 250, "pic\\ar.bmp");
		iText(450, 220, "MD  ABDUR  RAZZAK", GLUT_BITMAP_HELVETICA_18);
		iText(470, 180, "LEVEL-1, TERM-1", GLUT_BITMAP_HELVETICA_18);
		iText(445, 140, "DEPARTMENT  OF  CSE", GLUT_BITMAP_HELVETICA_18);
		iText(300, 100, "BANGLADESH  UNIVERSITY  OF  ENGINEERING  AND  TECHNOLOGY", GLUT_BITMAP_HELVETICA_18);
	}
}

void iMouseMove(int mx, int my)
{
}

void iMouse(int button, int state, int mx, int my)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

		if (mx >= 700 && mx <= 800 && my >= 150 && my <= 190)//starting main game from this condition here
		{
			Music = false;
			PlaySound(0, 0, 0);

			bgspeed = 10;
			game_state = 1;
			isscore = true;
		}

		if (mx >= 510 && mx <= 597 && my >= 260 && my <= 297)
		{
			exit(0);
		}

		if (mx >= 698 && mx <= 881 && my >= 270 && my <= 305)
		{

			game_state = -1;
		}

		if (mx >= 470 && mx <= 620 && my >= 100 && my <= 140)
		{
			exit(0);
		}

		if (mx >= 200 && mx <= 400 && my >= 50 && my <= 90)//show instruction page
		{
			game_state = 5;
		}

		if (mx >= 700 && mx <= 900 && my >= 50 && my <= 90)//show about me page
		{
			game_state = 6;
		}

		if (mx >= 480 && mx <= 630 && my >= 10 && my <= 50)//home menu
		{
			game_state = 0;
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
	}
}

void iKeyboard(unsigned char key)
{
	if (!input)
	{
		if (key == '\r' || key == ' ') //\r indicates the end of taking input
		{
			input = 1;
			fprintf(fp, "%s ", player_name);
		}
		else if (key == '\b') // used to delete character
		{
			if (name_length > 0)
			{
				name_length--;
				player_name[name_length] = '\0';
			}
		}

		else
		{
			if (name_length < 19)//used to insert character
			{

				player_name[name_length] = key;
				name_length++;
				player_name[name_length] = '\0';
			}
		}
	}

	if (key == ' ')
	{

		if (!isjumping)
		{

			collision_music = false;
			PlaySound("sound\\jump_sound.wav", NULL, SND_ASYNC);
			isjumping = true;
			jumpvelocity = v;
		}
	}
}

void iSpecialKeyboard(unsigned char key)
{
}

void setAll()   //background rendering,obstacle rendering
{

	for (int i = 0; i < 11; i++)
	{
		upper_background[i].y = 0;

		upper_background[i].x = sum;

		sum += 100;
	}

	for (int i = 0; i < 8; i++)
	{
		if (i == 1)
		{
			sum2 += 50;
		}
		if (i == 2)
		{
			sum2 += 300;
		}
		if (i == 3)
		{
			sum2 += 100;
		}
		if (i == 4)
		{
			sum2 += 150;
		}
		if (i == 5)
		{
			sum2 += 100;
		}
		if (i == 6)
		{
			sum2 += 100;
		}
		if (i == 7)
		{
			sum2 += 200;
		}
		cactus[i].y = 80;
		cactus[i].x = sum2;
		sum2 += 400;
	}
}


void score_calc()
{

	if (isscore)//true from mouse condition 1 to start not counting from run
		score++;
	if (score >= 50 && score <= 99)
	{
		bgspeed = 11;
	}
	if (score >= 100 && score <= 149)//else if
	{
		bgspeed = 12;
		gravity = -6;
	}
	if (score >= 150 && score <= 199)//else if
	{
		bgspeed = 13;
		gravity = -6;
		set_timer_change_3 = 110;
	}
	if (score >= 200 && score <= 249)//else if
	{
		bgspeed = 14;
		gravity = -6;
		set_timer_change_3 = 110;
	}
	if (score >= 250 && score <= 299)
	{
		bgspeed = 15;
		gravity = -7;
		set_timer_change_3 = 110;
	}
	if (score >= 300 && score <= 400)
	{
		bgspeed = 17;
		gravity = -7;
		set_timer_change_3 = 120;
	}
	if (score >= 401 && score <= 500)//else if
	{
		bgspeed = 20;
		gravity = -8;
		set_timer_change_3 = 125;
	}
	if(score>=501 && score<=700)
	{
		bgspeed=22;
		gravity=-8;
		set_timer_change_3=130;
	}
	if(score>=701 && score<=1000)
	{
		bgspeed=25;
		gravity=-9;
		set_timer_change_3=140;
	}
	if(score>1000)
	{
		bgspeed=28;
		gravity=-10;
		set_timer_change_3=145;
	}
}

void score_leader()//taking name and score to array from score.txt file and sorting here
{

	char string[100];

	while (fgets(string, sizeof(string), fr) != NULL)
	{
		if (strlen(string) <= 1)
			continue;
		int count = 0;
		int k = 0;

		for (int j = 0; j <= strlen(string); j++)
		{
			if (string[j] == ' ' || string[j] == '\0' || string[j] == '\n')
			{
				count++;
				if (count == 1)
				{

					char temp[20];
					int y = 0;
					for (int x = k; x < j; x++)
					{
						temp[y++] = string[x];
					}
					temp[y] = '\0';
					strcpy(arr[line].name, temp);
					k = j + 1;
				}
				if (count == 2)
				{
					int num = 0;
					for (int x = k; x < j; x++)
					{
						num = num * 10 + (string[x] - '0');
					}
					arr[line].score = num;
					line++;
					k = j + 1;
				}
			}
		}
	}

	for (int i = 0; i < line - 1; i++)
	{
		int flag = 0;
		for (int j = 0; j < line - i - 1; j++)
		{
			if (arr[j].score < arr[j + 1].score)
			{
				int temp = arr[j].score;
				char s[20];
				strcpy(s, arr[j].name);
				arr[j].score = arr[j + 1].score;
				strcpy(arr[j].name, arr[j + 1].name);
				arr[j + 1].score = temp;
				strcpy(arr[j + 1].name, s);
				flag = 1;
			}
		}
		if (flag == 0)
			break;
	}

	//fclose(fr);
}

void stack() //to store score into score.txt file and call score_leader function
{
	fprintf(fp, "%d\n", score);

	fclose(fp);
	score_leader();
}

void gameover()
{

	iPauseTimer(0);
	iPauseTimer(1);
	iPauseTimer(2);
	iPauseTimer(3);

	PlaySound("sound\\catsound.wav", NULL, SND_ASYNC);

	game_check = true;

	stack();
}

void change() //background rendering from isettimer and collition conditions and call gameover()
{

	for (int i = 0; i < 11; i++)
	{
		upper_background[i].x -= bgspeed;

		if (upper_background[i].x <= 0)
			upper_background[i].x = 1100 - 12;
	}
	for (int i = 0; i < 8; i++)
	{

		if ((cactus[0].x <= 210 && cactus[0].x >= 103 && jumpheight <= 95))
		{

			gameover();
		}

		if (cactus[1].x <= 210 && cactus[1].x >= 102)
		{

			if (jumpheight <= 83 - 10)
				gameover();
		}

		if (cactus[2].x <= 210 && cactus[2].x >= 103)
		{
			if (jumpheight <= 100)
				gameover();
		}

		if (cactus[3].x <= 210 && cactus[3].x >= 103)
		{

			if (jumpheight <= 110 - 10)
				gameover();
		}
		if (cactus[4].x <= 215 && cactus[4].x >= 103)
		{
			if (jumpheight <= 68 - 10)
				gameover();
		}

		if (cactus[5].x <= 200 && cactus[5].x >= 103)
		{
			if (jumpheight <= 135)
				gameover();
		}
		if (cactus[6].x <= 210 && cactus[6].x >= 103)
		{
			if (jumpheight <= 140)
				gameover();
		}
		if (cactus[7].x <= 220 && cactus[7].x >= 103)
		{
			if (jumpheight <= 100)
				gameover();
		}
		cactus[i].x -= bgspeed;
		if (cactus[i].x <= 0)
			cactus[i].x = 4600;
	}
}
void change2()//character running function from calling isettimer()
{
	chr_run_idx++;
	if (chr_run_idx >= 6)
		chr_run_idx = 0;
}
void change3() //for applying jumping calculation
{

	if (isjumping)
	{

		jumpheight += jumpvelocity;
		jumpvelocity += gravity;
		if (jumpheight <= 0)
		{
			jumpheight = 0;
			jumpvelocity = v;
			isjumping = false;
		}
	}
}

int main()
{

	if (fp == NULL || fr == NULL)
	{
		exit(1);
	}

	player_name[0] = '\0';

	setAll();

	iSetTimer(50, change);

	iSetTimer(set_timer_change_3, change3);

	iSetTimer(100, change2);

	iSetTimer(250, score_calc);

	if (Music)
	{
		Jump_music = false;
		collision_music = false;
		PlaySound("sound\\ms1.wav", NULL, SND_LOOP | SND_ASYNC);
	}

	iInitialize(screen_width, screen_height, "Game Project");
	return 0;
}
