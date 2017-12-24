#pragma once

///TO SEE I valori delle costanti al momento sono sensati
///       ma non definitivi: io direi di fare tuning una
///       volta che abbiamo generato qualcosa di visibile.

//Space Limit Constant Definition

#define MAX_VIS_X 960				//Massima punto visibile lungo le x
#define MAX_VIS_Y 540				//Massimo punto visibile lungo le y

#define MIN_VIS_X -960				//Minimo punto visibile lungo le x
#define MIN_VIS_Y -540				//Minimo punto visibile lungo le y

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


//Bullet Constant Definition

#define BULLET_SPEED 10				    //Velocità del proiettile lungo le x
#define BULLET_LENGTH 10				//Lunghezza del proiettile (x)
#define BULLET_WIDTH 5				    //Larghezza del proiettile (y)
#define BULLET_HEIGHT -4				//Altezza del proiettile (z)

//Asteroid Constant Definition

#define AST_BASE_SPEED_X 5
#define AST_SPAN_SPEED_X 5
#define AST_BASE_SPEED_Y 0
#define AST_SPAN_SPEED_Y 2
#define AST_MAX_LENGTH 30
#define AST_MAX_WIDTH 30
#define AST_MIN_LENGTH 15
#define AST_MIN_WIDTH 15
#define AST_HEIGHT -4

//Spaceship Constant Definition

#define SS_BASE_SPEED 10
#define SS_LENGTH 30
#define SS_WIDTH 30
#define SS_HEIGHT -4

//Latency before firts asteroid
#define START_GAME 10
//Scalability constant about asteroid creation time
#define TIME_SCALE 100
