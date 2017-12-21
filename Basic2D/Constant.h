#pragma once

///TO SEE I valori delle costanti al momento sono sensati
///       ma non definitivi: io direi di fare tuning una
///       volta che abbiamo generato qualcosa di visibile.

//Space Limit Constant Definition

#define MAX_VIS_X 1980				//Massima punto visibile lungo le x
#define MAX_X 2040					//Massimo punto spaziale lungo le x
#define MAX_VIS_Y 1140				//Massimo punto visibile lungo le y
#define MAX_Y 1200					//Massimo punto spaziale lungo le y

#define MIN_VIS_X 60				//Minimo punto visibile lungo le x
#define MIN_X 0						//Minimo punto spaziale lungo le x
#define MIN_VIS_Y 60				//Minimo punto visibile lungo le y
#define MIN_Y 0						//Minimo punto spaziale lungo le y

//Bullet Constant Definition

#define BULLET_SPEED 10				//Velocità del proiettile lungo le x
#define BULLET_LENGTH 2				//Lunghezza del proiettile (x)
#define BULLET_WIDTH 1				//Larghezza del proiettile (y)

//TOO SEE perche altezza del proiettile?
///ANSWER così manteniamo tutto parametrizzabile,
///       anche l'altezza lungo la z.
#define BULLET_HEIGHT 2				//Altezza del proiettile (z)

//Asteroid Constant Definition

#define AST_BASE_SPEED_X 5
#define AST_SPAN_SPEED_X 5
#define AST_BASE_SPEED_Y 0
#define AST_SPAN_SPEED_Y 2
#define AST_MAX_LENGTH 10
#define AST_MAX_WIDTH 10
#define AST_MIN_LENGTH 5
#define AST_MIN_WIDTH 5
#define AST_HEIGHT 2

//Spaceship Constant Definition

#define SS_BASE_SPEED 10
#define SS_LENGTH 5
#define SS_WIDTH 5
#define SS_HEIGHT 2

//Latency before firts asteroid
#define START_GAME 10
//Scalability constant about asteroid creation time
#define TIME_SCALE 100
