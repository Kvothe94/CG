#pragma once

///TO SEE I valori delle costanti al momento sono sensati
///       ma non definitivi: io direi di fare tuning una
///       volta che abbiamo generato qualcosa di visibile.

//Space Limit Constant Definition

#define MAX_VIS_XG 960				//Massima punto visibile lungo le x
#define MAX_VIS_YG 540				//Massimo punto visibile lungo le y

#define MIN_VIS_XG -960			//Minimo punto visibile lungo le x
#define MIN_VIS_YG -540			//Minimo punto visibile lungo le y

//Costanti realta logica
#define MAX_VIS_X 1920			//Massima punto visibile lungo le x
#define MAX_VIS_Y 1080				//Massimo punto visibile lungo le y

#define MIN_VIS_X 0			//Minimo punto visibile lungo le x
#define MIN_VIS_Y 0	
//Camera Constant Definition
#define EYE_X 0
#define EYE_Y 0
#define EYE_Z 0

#define CENTER_X 0
#define CENTER_Y 0
#define CENTER_Z -10

#define UP_X 0
#define UP_Y 1
#define UP_Z 0

//Background Constant Definition
#define MAX_BACK_X 960				//Massima punto visibile lungo le x
#define MAX_BACK_Y 540				//Massimo punto visibile lungo le y

#define MIN_BACK_X 960				//Minimo punto visibile lungo le x
#define MIN_BACK_Y 540				//Minimo punto visibile lungo le y

#define BACK_Z -5

//Men� Constant Definition
#define BUTTON_LENGTH 16*25
#define BUTTON_WIDTH 9*20
#define BUTTON_HEIGHT -4
#define BUTTON_DISTANCE ((MAX_VIS_X - MIN_VIS_X) - BUTTON_LENGTH * 3) / 4
#define BUTTON_PLAY 0
#define BUTTON_OPTIONS 1
#define BUTTON_EXIT 2

//Bullet Constant Definition

#define BULLET_SPEED 50			    //Velocit� del proiettile lungo le x
#define BULLET_LENGTH 16 * 10				//Lunghezza del proiettile (x)
#define BULLET_WIDTH 9 * 10					//Larghezza del proiettile (y)
#define BULLET_HEIGHT -4							//Altezza del proiettile (z)

//Asteroid Constant Definition

#define AST_BASE_SPEED_X 5
#define AST_SPAN_SPEED_X 5
#define AST_BASE_SPEED_Y 0
#define AST_SPAN_SPEED_Y 2
#define AST_MAX_LENGTH 50*5
#define AST_MAX_WIDTH 30*5
#define AST_MIN_LENGTH 50*2
#define AST_MIN_WIDTH 30*2
#define AST_HEIGHT -4

//Spaceship Constant Definition

#define SS_BASE_SPEED 20
#define SS_LENGTH 16*15
#define SS_WIDTH 9*15
#define SS_HEIGHT -4

//Latency before firts asteroid
#define START_GAME 10
//Scalability constant about asteroid creation time
#define TIME_SCALE 10

// tempo dopo il quale passo da hit a destroy
#define HT 1.5

// Costanti barre:
#define BAR_Z -3
#define R_BAR_X MAX_BACK_X - 280
#define R_BAR_Y MAX_BACK_Y - 100
#define G_BAR_X MAX_BACK_X - 280
#define G_BAR_Y MAX_BACK_Y - 50
#define R_BAR_LENGTH 450
#define R_BAR_WIDTH 40
#define G_BAR_LENGTH 150
#define G_BAR_WIDTH 50