///////////////////////////////////////////////////////////////////
//  A basic skeleton for 2D like game developpers.
//
//  model data
///////////////////////////////////////////////////////////////////

#include <windows.h>		// Header File For Windows
#include <stdio.h>			// Header File For Standard Input/Output
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library

#include "Model.h"
#include "SOIL.h"
#include "audiere.h"
using namespace audiere;

// All Setup For OpenGL Goes Here
bool MyModel::InitGL(void){

	if (!this->LoadGLTextures()) {				// Jump To Texture Loading Routine
		return false; 							// If Texture Didn't Load Return FALSE
	}


	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	this->BuildFont();

	gluLookAt(EYE_X, EYE_Y, EYE_Z, CENTER_X, CENTER_Y, CENTER_Z, UP_X, UP_Y, UP_Z);

	return true;										// Initialization Went OK
}


void MyModel::ReSizeGLScene(int width, int height){

	if (height == 0) 
		height = 1;							// Prevent A Divide By Zero By
	
	if (width == 0) 
		width = 1;							// Prevent A Divide By Zero By

	glViewport(0, 0, width, height);		// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);			// Select The Projection Matrix
	glLoadIdentity();						// Reset The Projection Matrix

	/* orthographic projection
	   background in [-1, 1] on both x and y
	   fill th background according to the window aspect ratio
	   void WINAPI glOrtho( GLdouble left,   GLdouble right,
	                        GLdouble bottom, GLdouble top,
	                        GLdouble zNear,  GLdouble zFar );*/

	if( width >= height ) {
		this->plx = 1.0;
		this->ply = (double) height /(double) width;
	} else {
		this->plx = (double) width /(double) height;
		this->ply = 1.0;
	}

	glOrtho(-this->plx, this->plx, -this->ply, this->ply, 1, 5.1);
  
	//  saving the window width and height in pixels
	this->Wheight = height;
	this->Wwidth = width;

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix

}



// Load Bitmaps And Convert To Textures
bool MyModel::LoadGLTextures(void) {

	backgroundTexture = SOIL_load_OGL_texture("../Data/Backgrounds/background.jpg",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	if (backgroundTexture == 0)
		return false;

	backgroundTextureMenu = SOIL_load_OGL_texture("../Data/Backgrounds/background-modified.jpg",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	if (backgroundTextureMenu == 0)
		return false;

	bulletTexture = SOIL_load_OGL_texture("../Data/Spaceship/bullet.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	if (bulletTexture == 0)
		return false;

	char auxString[200];

	for (int i = 1; i <= 5; i++) {

		sprintf(auxString, "../Data/Spaceship/spaceship%d.png", i);
		spaceshipTextures[i - 1] = SOIL_load_OGL_texture(
			auxString, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
		if (spaceshipTextures[i - 1] == 0)
			return false;

	}

	for (int i = 1; i <= 4; i++) {

		sprintf(auxString, "../Data/Asteroids/asteroid%d.png", i);
		asteroidTextures[i - 1] = SOIL_load_OGL_texture(
			auxString, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
		if (asteroidTextures[i - 1] == 0)
			return false;

	}

	for (int i = 0; i < 17; i++) {

		sprintf(auxString, "../Data/Spaceship_Explosion/1_%d.png", i);
		spaceshipExplosionTextures[i] = SOIL_load_OGL_texture(
			auxString, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
		if (spaceshipExplosionTextures[i] == 0)
			return false;

		sprintf(auxString, "../Data/Asteroids_Explosion/1_%d.png", i);
		asteroidExplosionTextures[i] = SOIL_load_OGL_texture(
			auxString, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
		if (asteroidExplosionTextures[i] == 0)
			return false;

	}

	menuTexture[1][0] = SOIL_load_OGL_texture("../Data/Menu_Screen/options.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (menuTexture[1][0] == 0)
		return false;

	menuTexture[1][1] = SOIL_load_OGL_texture("../Data/Menu_Screen/options_pressed.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (menuTexture[1][1] == 0)
		return false;

	menuTexture[0][0] = SOIL_load_OGL_texture("../Data/Menu_Screen/play.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (menuTexture[0][0] == 0)
		return false;

	menuTexture[0][1] = SOIL_load_OGL_texture("../Data/Menu_Screen/play_pressed.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (menuTexture[0][1] == 0)
		return false;

	menuTexture[2][0] = SOIL_load_OGL_texture("../Data/Menu_Screen/exit.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (menuTexture[2][0] == 0)
		return false;

	menuTexture[2][1] = SOIL_load_OGL_texture("../Data/Menu_Screen/exit_pressed.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (menuTexture[2][1] == 0)
		return false;
	
	return true;										// Return Success
}


bool MyModel::Run(OutputStreamPtr shoot, OutputStreamPtr explode){
	//  TIMING - start
	clock_t t = clock();

	// elapsed time in seconds from the last draw
	double elapsed = double(t - Tstamp) / (double)CLOCKS_PER_SEC;

	// elapsed time in milliseconds from the last draw

	int ms_elapsed = (int)(t - Tstamp);
	if (ms_elapsed < 10) {
		 return true;
	}

	// elapsed time in seconds from the beginning of the program
	this->fullElapsed = double(t - Tstart) / (double)CLOCKS_PER_SEC;
	this->frameTime += double(t - Tstamp) / (double)CLOCKS_PER_SEC;

	this->Tstamp = t;
	//  TIMING - end
	//controllo sul flag
	if (this->isGame){
		this->Play(ms_elapsed,shoot, explode);
		this->DrawGLSceneGame();
	}
	else{
		this->DrawGLSceneInit();
		this->KeyCheck(shoot, explode);
		this->CheckGame(explode);
	}

	return true;

}

float MyModel::Distance(Vertex a, Vertex b){

	float dist = sqrt(pow(abs(a.getX()) - abs(b.getX()), 2) + pow(abs(a.getY()) - abs(b.getY()), 2));
	return dist;
}
bool MyModel::Hit(Vertex a, float al, float aw, Vertex b, float bl, float bw){
	//considero un raggio medio per fare la hit mi sembra la cosa più sensata 
	//divido per 4 per avere una cosa più sensata dal punto di vista grafico cioè
	//sottopeso un po i colpi cosi non rischio di avere sateroidi che esplodono senza tocare
	float ra = (al + aw) / 13;
	float rb = (bl + bw) / 13;
	float dist = Distance(a, b);
	
	if (ra + rb >= dist){
		return true;
	}
	else{
		return false;
	}

}

bool MyModel::CheckGame(OutputStreamPtr explode){
	//qui bisogna controllare:
	//1 Proiettili che colpiscono asteroidi nel caso elimono asteroide e proiettile
	for (int i = 0; i < this->asteroids.size(); i++){
		
		for (int k = 0; k < this->bullets.size(); k++){
			
			if (!this->asteroids[i].getHitten()) {
				if (Hit(this->asteroids[i].getCenter(), this->asteroids[i].getLength(), this->asteroids[i].getWidth(), this->bullets[k].getCenter(), this->bullets[k].getLength(), this->bullets[k].getWidth())) {
					//qui vanno messe le azioni da fare nel caso di colpito asteroide proiettile
					this->asteroids[i].setHitten(true);
					this->asteroids[i].setHittingTime(this->fullElapsed);
					this->bullets.erase(bullets.begin() + k);
					//this->asteroids[i].setToDestroy(true);
					if (explode->isPlaying()) {
						explode->reset();
					}
					else explode->play();

				}
			}
			
		}
	}
	//2 Asteroidi che colpiscono navetta
	for (int j = 0; j < this->asteroids.size(); j++){
		
		if (!(this->asteroids[j].getHitten() || this->spaceship.getHitten())) {
			
			if (Hit(this->spaceship.getCenter(), this->spaceship.getLength(), this->spaceship.getWidth(), this->asteroids[j].getCenter(), this->asteroids[j].getLength(), this->asteroids[j].getWidth()
			)) {
				//Cosa da fare nel caso di colpito navicella con asteroide
				//this->spaceship.setToDestroy(true);
				//this->asteroids[j].setToDestroy(true);

				this->spaceship.setHitten(true);
				this->spaceship.setHittingTime(this->fullElapsed);
				this->asteroids[j].setHitten(true);
				this->asteroids[j].setHittingTime(this->fullElapsed);
				if (explode->isPlaying()) {
					explode->reset();
				}
				else explode->play();


			}

		}

	}
	//controllo gli outofboundaries
	
	//3 Asteroide che va fuori
	for (int j = 0; j < this->asteroids.size(); j++){
		
		if (this->asteroids[j].getHitten()) {
			if (this->fullElapsed - this->asteroids[j].getHittingTime() >= HT) {
				this->asteroids[j].setToDestroy(true);
			}
		}
		

		if (this->asteroids[j].getToDestroy()){
			this->asteroids.erase(asteroids.begin() + j);
		}

	}

	//4 Proiettile che va fuori
	for (int j = 0; j < this->bullets.size(); j++){
		if (this->bullets[j].getToDestroy()){
			this->bullets.erase(bullets.begin() + j);
		}
	}

	if (this->spaceship.getHitten()) {
		if (this->fullElapsed - this->spaceship.getHittingTime() >= HT) {
			this->spaceship.setToDestroy(true);
		}
	}
	
	
	if (this->spaceship.getToDestroy()) {
		this->isGame = false;
		if (this->spaceship.getToDestroy()) {
			this->spaceship = Spaceship();
			this->asteroids.clear();
			this->bullets.clear();
		}
	}

	return true;

}


bool MyModel::KeyCheck(OutputStreamPtr shoot, OutputStreamPtr explode){
	if (Data.keys[VK_SPACE]){

		Bullet auxBullet = Bullet(this->spaceship.getCenter().getX(), this->spaceship.getCenter().getY(), BULLET_HEIGHT, BULLET_SPEED, BULLET_LENGTH, BULLET_WIDTH);
		this->bullets.push_back(auxBullet);
		
		//TOO see guido non capisco xke ho fatto come il prof pero qui mi non funziona perche shoot risulta essere un puntatore vuoto a null

		if (shoot->isPlaying()){
			shoot->reset();
		}
		else shoot->play();

		Data.keys[VK_SPACE] = false;

	}
	if (Data.keys[VK_UP]){
		this->spaceship.setBaseSpeedY(+SS_BASE_SPEED);
		//Data.keys[VK_UP] = false;
	}
	if (Data.keys[VK_DOWN]){
		this->spaceship.setBaseSpeedY(-SS_BASE_SPEED);
		//Data.keys[VK_DOWN] = false;
	}
	if (Data.keys[VK_RETURN]) {
		if (this->isGame == false)
			this->isGame = true;
		Data.keys[VK_RETURN] = false;
	}


	if (Data.keys[VK_TAB]) {
		if (this->isGame)
			this->isGame = false;
		Data.keys[VK_TAB] = false;
	}

	if (Data.keys[0x31]){
		if (!this->isGame){
			this->diff = 1;
		}
		Data.keys[0x31] = false;
	}

	if (Data.keys[0x32]){
		if (!this->isGame){
			this->diff = 2;
		}
		Data.keys[0x32] = false;
	}

	if (Data.keys[0x33]){
		if (!this->isGame){
			this->diff = 3;
		}
		Data.keys[0x33] = false;
	}
	
	

	//da inserire eventuali altri comandi 
	//ricorda di mettere a false i tasti
	return true;

}
bool MyModel::ComputeMovements(double elapsed){
	//muovo la navicella
	elapsed = elapsed / 100;
	this->spaceship.move(elapsed);
	//muovo gli asteroidi
	for (int i = 0; i < this->asteroids.size(); i++){
		if (!this->asteroids.at(i).move(elapsed)){
			//setto la variabile to destroy poiche move ha ritornato false cioè sono outfoboundaries
			this->asteroids.at(i).setToDestroy(true);
		}
	}
	//muovo i bullet
	for (int i = 0; i < this->bullets.size(); i++){
		if (!this->bullets.at(i).move(elapsed)){
			//setto la variabile to destroy poiche move ha ritornato false cioè sono outfoboundaries
			this->bullets.at(i).setToDestroy(true);
		}
	}

	return true;
}

bool MyModel::Play(double elapsed, OutputStreamPtr shoot, OutputStreamPtr explode){
	this->KeyCheck(shoot, explode);
	this->ComputeMovements(elapsed);
	this->CheckGame(explode);
	this->DoGame(elapsed);
	return true;

}

bool MyModel::DoGame(double elapsed){
	this->astnew= this->astnew - elapsed;
	if (this->astnew <= 0){
		this->asteroids.push_back(Asteroid(this->diff));
		this->astnew = (rand()%1000)*(TIME_SCALE/ diff);
	}
	return true;

}
Vertex MyModel::Adapter(Vertex v){
	Vertex aux;
	aux.setX(v.getX() - 960);
	aux.setY(v.getY() - 540);
	aux.setZ(v.getZ());
	return aux;

}
bool MyModel::DrawGLSceneInit(void)									
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear The Screen And The Depth Buffer
	glMatrixMode(GL_MODELVIEW);								// Select The Modelview Matrix
	glLoadIdentity();										// Reset The View

															//  TIMING - start
	clock_t t = clock();

	// elapsed time in seconds from the last draw
	double elapsed = double(t - Tstamp) / (double)CLOCKS_PER_SEC;

	// elapsed time in milliseconds from the last draw
	int ms_elapsed = (int)(t - Tstamp);

	// elapsed time in seconds from the beginning of the program
	this->fullElapsed = double(t - Tstart) / (double)CLOCKS_PER_SEC;
	this->frameTime += double(t - Tstamp) / (double)CLOCKS_PER_SEC;

	this->Tstamp = t;
	//  TIMING - end

	//  Background
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, backgroundTextureMenu);

	glBegin(GL_QUADS);
	for (int i = 0; i < 4; i++) {
		glTexCoord2f(Background[i].getU(), Background[i].getV());
		glVertex3f(Background[i].getX(), Background[i].getY(), Background[i].getZ());
	}
	glEnd();

	//Buttons
	for each (Button aButton in buttons){
		draw(aButton);
	}

	return true;

}

bool MyModel::DrawGLSceneGame(void){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear The Screen And The Depth Buffer
	glMatrixMode(GL_MODELVIEW);								// Select The Modelview Matrix
	glLoadIdentity();										// Reset The View
	//TO SEE questo lo ho commentato non so xke lo avessi lasciato guido non serve a niente
	////  TIMING - start
	//clock_t t = clock();

	//// elapsed time in seconds from the last draw
	//double elapsed = double(t - Tstamp) / (double)CLOCKS_PER_SEC;

	//// elapsed time in milliseconds from the last draw
	//int ms_elapsed = (int)(t - Tstamp);

	//// elapsed time in seconds from the beginning of the program
	//this->fullElapsed = double(t - Tstart) / (double)CLOCKS_PER_SEC;
	//this->frameTime += double(t - Tstamp) / (double)CLOCKS_PER_SEC;

	//this->Tstamp = t;
	////  TIMING - end

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, backgroundTexture);

	//  Background
	glBegin(GL_QUADS);
	for (int i = 0; i < 4; i++) {
		glTexCoord2f(Background[i].getU(), Background[i].getV());
		glVertex3f(Background[i].getX(), Background[i].getY(), Background[i].getZ());
	}
	glEnd();

	
	//Ora dobbiamo disegnare tutti i nostri oggetti:
	for each (Bullet myBull in bullets){
		draw(myBull);
	}

	for each (Asteroid myAst in asteroids) {
		draw(myAst);
	}

	draw(this->spaceship);
	
	
	/*//  Some text
	glMatrixMode(GL_MODELVIEW);				// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Current Modelview Matrix
	glDisable(GL_TEXTURE_2D);

	// Color
	glColor3f(1.0f, 1.0f, 1.0f);

	// Position The Text On The Screen
	glRasterPos3f(-(float)plx + PixToCoord_X(10), (float)ply - PixToCoord_Y(21),
	-4);

	// compute fps and write text
	this->frames++;
	if (this->frames > 18) {
	this->fps = frames / frameTime;
	this->frames = 0; this->frameTime = 0;
	}
	this->glPrint("Elapsed time: %6.2f sec.  -  Fps %6.2f",
	fullElapsed, fps);

	if (this->fullElapsed < 6) {
	glRasterPos3f(-(float)plx + PixToCoord_X(10), (float)-ply + PixToCoord_Y(21),
	-4);
	this->glPrint("...F2/F3/F4 for sounds");
	}

	{
	glRasterPos3f(-(float)plx + PixToCoord_X(10), (float)-ply + PixToCoord_Y(61),
	-4);
	this->glPrint("%1d %1d  %s", cx, cy, captured ? "captured" : "Not captured");
	}

	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	return true;*/

	return true;
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//  bitmap fonts
void MyModel::BuildFont(void)							// Build Our Bitmap Font
{
	HFONT	font;										// Windows Font ID
	HFONT	oldfont;									// Used For Good House Keeping

	base = glGenLists(96);								// Storage For 96 Characters

	font = CreateFont(	-20,							// Height Of Font
						0,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						FW_BOLD,						// Font Weight
						FALSE,							// Italic
						FALSE,							// Underline
						FALSE,							// Strikeout
						ANSI_CHARSET,					// Character Set Identifier
						OUT_TT_PRECIS,					// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						ANTIALIASED_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						"Courier New");					// Font Name

	oldfont = (HFONT)SelectObject(hDC, font);           // Selects The Font We Want
	wglUseFontBitmaps(hDC, 32, 96, base);				// Builds 96 Characters Starting At Character 32
	SelectObject(hDC, oldfont);							// Selects The Font We Want
	DeleteObject(font);									// Delete The Font
}

void MyModel::KillFont(void)									// Delete The Font List
{
	glDeleteLists(base, 96);							// Delete All 96 Characters
}

void MyModel::glPrint(const char *fmt, ...)					// Custom GL "Print" Routine
{
	char		text[256];								// Holds Our String
	va_list		ap;										// Pointer To List Of Arguments

	if (fmt == NULL)									// If There's No Text
		return;											// Do Nothing

	va_start(ap, fmt);									// Parses The String For Variables
	    vsprintf(text, fmt, ap);						// And Converts Symbols To Actual Numbers
	va_end(ap);											// Results Are Stored In Text

	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(base - 32);								// Sets The Base Character to 32
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits
}