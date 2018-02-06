#pragma once

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
#include "Button.h"


class MyModel {

	public:
	
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
		std::vector<Button> buttons;
		Spaceship spaceship;
		
		bool isGame = false;
		//livello di difficolta del gioco
		double diff ;
		//punteggio del gioco
		int score ;
		float tdist;
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
		
		GLuint menuTexture[3][2];
		
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
			/*Background.clear();
			*/

			Background.clear();
			
			Background.push_back(Vertex(MIN_BACK_X / MIN_VIS_XG, MIN_BACK_Y / MIN_VIS_YG, BACK_Z, 0, 0, 1, 0, 0));
			Background.push_back(Vertex(MIN_BACK_X / MIN_VIS_XG, MAX_BACK_Y / MAX_VIS_YG, BACK_Z, 0, 0, 1, 0, 1));
			Background.push_back(Vertex(MAX_BACK_X / MAX_VIS_XG, MAX_BACK_Y / MAX_VIS_YG, BACK_Z, 0, 0, 1, 1, 1));
			Background.push_back(Vertex(MAX_BACK_X / MAX_VIS_XG, MIN_BACK_Y / MIN_VIS_YG, BACK_Z, 0, 0, 1, 1, 0));
			

			buttons.clear();
			for (int i = 0; i < 3; i++) {
				buttons.push_back(Button(i));
			}
			
			//creo una navicella
			this->spaceship = Spaceship();
			
			///TO SEE: non lo creerei nel costruttore del modello l'asteroide
			///        se c'è una funzione che chiamiamo ogni volta per la gestione
			///        del gioco probabilmente lo creerei lì insieme ai bullet etc.
			// Answer forse hai ragione potrebbe essere una cosa sensata
			//this->asteroids.push_back(Asteroid(diff));

			this->Tstart = this->Tstamp = clock();
			this->fullElapsed = 0;
			this->frameTime = 0;
			
		}

		~MyModel() {
			this->KillFont();
		}

		inline bool IsInClient(int x, int y) {

			if (x >= 0 && x < Wwidth && y >= 0 && y < Wheight) return true;
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
		Vertex Adapter(Vertex);

		
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


		void draw(Asteroid anAsteroid) {

			///TO SEE da vedere se in ogni draw dobbiamo fare la
			///glEnable(GL_TEXTURE_2D); oppure se basta farla nel model
			///quando iniziamo a disegnare la scena in generale.
			if (anAsteroid.getHitten() && !anAsteroid.getToDestroy()) {

				///TO SEE: te lo hai capito questo algoritmo?
				//Answer mi sembra sia quello per ciclare in modo ciclico su 17 immagini con l'index
				int index = (int((this->fullElapsed - anAsteroid.getHittingTime()) * 20)) % 17;
				glBindTexture(GL_TEXTURE_2D, this->asteroidExplosionTextures[index]);

				//Se abbiamo finito di disegnare l'esplosione dobbiamo eliminare l'
				//oggetto.
				if (index == 16)
					anAsteroid.setToDestroy(true);


			}
			else {

				glBindTexture(GL_TEXTURE_2D, this->asteroidTextures[anAsteroid.getTexture()]);

			}

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0);

			glBegin(GL_QUADS);
			for (int i = 0; i < 4; i++) {
				glTexCoord2f(anAsteroid.getShape()[i].getU(), anAsteroid.getShape()[i].getV());
				glVertex3f(this->Adapter(anAsteroid.getShape()[i]).getX() / MAX_VIS_XG, this->Adapter(anAsteroid.getShape()[i]).getY() / MAX_VIS_YG, anAsteroid.getShape()[i].getZ());
			}
			glEnd();
			glDisable(GL_BLEND);
			glDisable(GL_ALPHA_TEST);

		}

		void draw(Bullet aBullet) {

			///TO SEE da vedere se in ogni draw dobbiamo fare la
			///glEnable(GL_TEXTURE_2D); oppure se basta farla nel model
			///quando iniziamo a disegnare la scena in generale.
			glBindTexture(GL_TEXTURE_2D, this->bulletTexture);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0);

			glBegin(GL_QUADS);
			for (int i = 0; i < 4; i++) {
				glTexCoord2f(aBullet.getShape()[i].getU(), aBullet.getShape()[i].getV());
				glVertex3f((this->Adapter(aBullet.getShape()[i]).getX() + this->spaceship.getLength() / 2) / MAX_VIS_XG, this->Adapter(aBullet.getShape()[i]).getY() / MAX_VIS_YG, aBullet.getShape()[i].getZ());
			}
			glEnd();
			glDisable(GL_BLEND);
			glDisable(GL_ALPHA_TEST);

		}

		void draw(Spaceship aSpaceship) {

			///TO SEE da vedere se in ogni draw dobbiamo fare la
			///glEnable(GL_TEXTURE_2D); oppure se basta farla nel model
			///quando iniziamo a disegnare la scena in generale.
			if (aSpaceship.getHitten() && !aSpaceship.getToDestroy()) {

				///TO SEE: te lo hai capito questo algoritmo?
				int index = (int((this->fullElapsed - aSpaceship.getHittingTime()) * 20)) % 17;
				glBindTexture(GL_TEXTURE_2D, this->spaceshipExplosionTextures[index]);

				//Se abbiamo finito di disegnare l'esplosione dobbiamo eliminare l'
				//oggetto.
				if (index == 16)
					aSpaceship.setToDestroy(true);

			} else {

				//Modifichiamo la texture in base a se la nave si muove in una direzione o in
				//un'altra.
				if (aSpaceship.getBaseSpeedY() == 0) {
					//Tentativo: uso 2 texture per dare un impressione di movimento.
					int index = (int(this->fullElapsed * 20)) % 2;
					glBindTexture(GL_TEXTURE_2D, this->spaceshipTextures[index]);
				}
				else if (aSpaceship.getBaseSpeedY() > 0) {
					glBindTexture(GL_TEXTURE_2D, this->spaceshipTextures[3]);
				}
				else {
					glBindTexture(GL_TEXTURE_2D, this->spaceshipTextures[2]);
				}

			}

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0);

			glBegin(GL_QUADS);
			for (int i = 0; i < 4; i++) {
				glTexCoord2f(aSpaceship.getShape()[i].getU(), aSpaceship.getShape()[i].getV());
				glVertex3f(this->Adapter(aSpaceship.getShape()[i]).getX() / MAX_VIS_XG, this->Adapter(aSpaceship.getShape()[i]).getY() / MAX_VIS_YG, aSpaceship.getShape()[i].getZ());
				
			}
			glEnd();
			glDisable(GL_BLEND);
			glDisable(GL_ALPHA_TEST);

		}

		void draw(Button aButton) {

			///TO SEE da vedere se in ogni draw dobbiamo fare la
			///glEnable(GL_TEXTURE_2D); oppure se basta farla nel model
			///quando iniziamo a disegnare la scena in generale.
			glBindTexture(GL_TEXTURE_2D, this->menuTexture[aButton.getType()][aButton.getPressed()]);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0);

			glBegin(GL_QUADS);
			for (int i = 0; i < 4; i++) {
				glTexCoord2f(aButton.getShape()[i].getU(), aButton.getShape()[i].getV());
				glVertex3f(aButton.getShape()[i].getX() / MAX_VIS_XG, aButton.getShape()[i].getY() / MAX_VIS_YG, aButton.getShape()[i].getZ());
			}
			glEnd();
			glDisable(GL_BLEND);
			glDisable(GL_ALPHA_TEST);

		}

};
