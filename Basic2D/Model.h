#ifndef MODEL_H
#define MODEL_H

///////////////////////////////////////////////////////////////////
//  A basic skeleton for 2D like game developpers.
//
//  model data
///////////////////////////////////////////////////////////////////

//  world geometry
// eye    (0,0,0)
// center (0,0,-1)
// up     (0,1,0)
// left -1, right 1
//  top & bottom centered on Y to match the window aspect ratio
// clipping planes: 1, 5.1

#pragma warning(disable: 4996)

#include <vector>
#include <time.h>
#include <math.h>
#include "Asteroid.h"
#include "Spaceship.h"
#include "Bullet.h"
#include "Vertex.h"
#include "Constant.h"



class MyModel {

	public:
	//  general data for window and input controls
		HDC			hDC;		        // Private GDI Device Context
		HGLRC		hRC;		        // Permanent Rendering Context
		HWND		hWnd;		        // Holds Our Window Handle
		HINSTANCE	hInstance;		// Holds The Instance Of The Application

		bool	keys[256];			// Array Used For The Keyboard Routine
		bool	active;		      // Window Active Flag Set To TRUE By Default
		bool cursor;          // true if visible
		bool captured;        // true if the mouse is captured
		int cx, cy;           // client position of the cursor
		bool	fullscreen;	    // Fullscreen Flag 
		////////////////////////////
	
		GLuint	base;						// Base Display List For The Font Set
		std::vector<Vertex> Background;     // background				
		
		std::vector<Asteroid> asteroids;
		std::vector<Bullet> bullets;
		Spaceship spaceship;
		
		bool isGame = false;
		//livello di difficolta del gioco
		double diff ;
		//punteggio del gioco
		int score ;
		//tempo dopo il quale creo un nuovo asteroide
		double astnew;
		//tempo dopo il quale sparo di nuovo
		double lastbullet;

		///TO SEE: elimino il private in modo da poter prendere i dati da dentro le
		///classi degli oggetti al fine di disegnarli.
	//private:
	//  projection limits in X and Y: x in [-plx, plx], y in [-ply, ply]
		double plx, ply;
		int Wheight, Wwidth;  // window dimensions in pixels

		int frames;           // n. of frames
		double frameTime;     // for fps computation
		double fps;

		//  model data
		
		clock_t Tstamp, Tstart;
		double fullElapsed;  // elapsed time in seconds from the beginning of the program

		GLuint backgroundTexture;
		GLuint bulletTexture;
		
		GLuint spaceshipTextures[5];
		GLuint asteroidTextures[4];

		GLuint spaceshipExplosionTextures[17];
		GLuint asteroidExplosionTextures[17];
		
		GLuint menuCreditsTexture[2];
		GLuint menuOptionsTexture[2];
		GLuint menuPlayTexture[2];
		GLuint menuExitTexture[2];
		
	public:
	//  methods
		//costruttore
		MyModel(): hDC(NULL), hRC (NULL), hWnd (NULL), active (true),
			fullscreen(true), frames(0), fps(0), cursor(true), captured(false) {
			
			this->score = 0;
			this->diff = 1;
			this->astnew = START_GAME;
			//TO DO
			//TO ASK PROF
			//queste sono le stesse del prof non le ho toccate poi andranno gestite meglio per questione resize
			Background.clear();
			Background.push_back(Vertex(60,     60, 0,   0, 0, 1,   0, 0));
			Background.push_back(Vertex(60,   1140, 0,   0, 0, 1,   0, 4));
			Background.push_back(Vertex(1980, 1140, 0,   0, 0, 1,   4, 4));
			Background.push_back(Vertex(1980,   60, 0,   0, 0, 1,   4, 0));
			
			//creo una navicella
			this->spaceship = Spaceship();
			
			///TO SEE: non lo creerei nel costruttore del modello l'asteroide
			///        se c'è una funzione che chiamiamo ogni volta per la gestione
			///        del gioco probabilmente lo creerei lì insieme ai bullet etc.
			// Answer forse hai ragione potrebbe essere una cosa sensata
			this->asteroids.push_back(Asteroid(diff));

			this->Tstart = this->Tstamp = clock();
			this->fullElapsed = 0;
			this->frameTime = 0;
			
		}

		~MyModel() {
			this->KillFont();
		}

		inline bool IsInClient(int x, int y) {
		
			if( x >= 0 && x < Wwidth && y >= 0 && y < Wheight ) return true;
			return false;
		
		}
		//le due funzioni di draw in base a in quale modalità sono: game o schermata iniziale
		bool DrawGLSceneGame(void);
		bool DrawGLSceneInit(void);
		//funzione nella quale scelgo cosa fare in base al flag isGame che seleziona la modalita
		bool Run();
		//funzione gioco al suo interno richiama 
		bool Play(double elapsed);
		//calcola la distanza tra due vertici utile per la hit
		float Distance(Vertex a, Vertex b);
		//controllo imput tastiera ed eventuali azioni seguenti come modifiche di velocita e creazione nuovi bullet
		bool KeyCheck();
		//sposto le cose in base alla equa spazio=velocita*tempo cioè s=vel*elapsed
		bool ComputeMovements(double elapsed);
		//funzione che fa tutti i check per quanto riguarda scontri esplosioni morti punteggi etc
		bool CheckGame();
		//funzione che crea asteroidi
		bool DoGame(double elapsed);
		bool Hit(Vertex a, float al, float aw, Vertex b, float bl, float bw);
		bool InitGL(void);
		void ReSizeGLScene(int width, int height);
		void glPrint(const char *fmt, ...);			// Custom GL "Print" Routine

	private:
		
		bool LoadGLTextures(void);
		void BuildFont(void);
		void KillFont(void);
		
		//  Conversion from pixel distance to float X and Y distance questa si adatta alla dim della finestra 
		//TO SEE gestione diensione finestra tagliata è nel 3d labirinto 
		inline float PixToCoord_X(int pix){
			return ( 2.0f * (float) pix * (float) plx ) / (float) Wwidth; 
		}

		inline float PixToCoord_Y(int pix){
			return ( 2.0f * (float) pix * (float) ply ) / (float) Wheight; 
		}
		
		//  conversion from client coordinates to 3d world coordinates
		inline float ClientX2World(int x) {
			return ( (2.0f * float(plx) * float(x) / float(Wwidth)) - float(plx));
		}

		inline float ClientY2World(int y) {
			return ( float(ply) - (2.0f * float(ply) * float(y) / float(Wheight)));
		}

};

#endif