#ifndef ASTEROID_H
#define ASTEROID_H

#include <vector>
#include <time.h>
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>	
#include <math.h>
#include <stdlib.h>
#include "Model.h"
#include "Constant.h"


class Asteroid {

	private:

		/*MEMBERS*/

		//Variabile che fa da moltiplicatore per la velocit�
		//di movimento dell'asteroide: andremo ad aumentarla
		//con il passare del tempo di gioco.
		float difficulty;

		//Velocit�, intese in termini vettoriali, dell'asteroide
		//lungo i due assi.
		///TO SEE PROBLEMA: se consideriamo il nostro spazio come
		///       nel disegno che ho messo in Data allora le velocit�
		///       lungo x e y rispettivamente saranno e potranno essere
		///       negative. Dici che va bene?
		float speedX;
		float speedY;

		//Dimensioni dell'asteroide
		float length;
		float width;

		//Centro dell'asteroide nel nostro spazio
		Vertex center;

		//Lista di vertici che costituiscono la nostra
		//forma geometrica sottostante l'asteroide.
		std::vector<Vertex> shape;   

		//Variabile che, qualora settata a true, indica
		//che l'oggetto non deve essere pi� disegnato e
		//va eliminato quanto prima.
		///TO SEE non so se lasciare che venga settata
		///dall'interno della classe oppure dal modello.
		///In particolare la setterei a true laddove si
		///verifichi la condizione di outOfBoundaries.
		bool toDestroy;

		//Variabile che contiene le nostre texture.
		///TO SEE In teoria potrebbe servirci pi�
		///       di una texture in modo da ciclare
		///       e rendere l'asteroide un po' pi�
		///       bello, idem per l'esplosione.
		///TO SEE a quanto ho visto le vere e proprie
		///		  texture vengono memorizzate in model.h
		///       nella classe dell'oggetto memorizzi i
		///       riferimenti alle texture di model.h.
		int texture;
		int explosionTexture;

	public:

		/*METHODS*/

		Asteroid(float x, float y, float z, float sX, float sY, float diff, float l, float w) {

			center = Vertex(x, y, z);
			difficulty = diff;

			//Computazione della velocit� lungo le x:
			//Dal costruttore viene fornita la velocit� di base lungo le x.
			//Ad essa si aggiunge una quantit� randomica in uno span di valori
			//che varia al variare della difficulty.
			//La velocit� cos� ottenuta viene ulteriormente moltiplicata per la
			//difficulty.
			//Considerando come abbiamo definito il nostro spazio la velocit�
			//lungo le x deve avere un valore negativo.
			speedX = difficulty * (sX + (rand() % int(AST_SPAN_SPEED_X * difficulty))) ;
			speedX = -speedX;

			//La velocit� lungo y pu� essere sia negativa che positiva:
			//dobbiamo randomizzare anche la scelta del segno.
			int sign;
			int auxRand = rand() % 2;
			if (auxRand)
				sign = 1;
			else
				sign = -1;
			
			speedY = sign * difficulty * (sY + (rand() % int(AST_SPAN_SPEED_Y * difficulty)));
			
			///TO SEE Invece che il raggio ho messo length e width
			///       in modo da poter mettere asteroidi non quadrati.
			length = l;
			width = w;
			toDestroy = false;

			//Definiamo i vertici dell'asteroide utilizzando
			//larghezza e lunghezza
			shape.push_back(Vertex(x + length / 2, y + width / 2, z));
			shape.push_back(Vertex(x + length / 2, y - width / 2, z));
			shape.push_back(Vertex(x - length / 2, y - width / 2, z));
			shape.push_back(Vertex(x - length / 2, y + width / 2, z));

			///TO DO dobbiamo decidere a che indice dell'array delle
			///      texture in model.h corrispondono le varie texture
			///      e quindi scegliere i giusti riferimenti per le
			///      texture della classe.

		}

		//Costruttore che genera un asteroide con dimensioni, posizione e velocit�
		//randomiche.
		Asteroid(float diff) {
			
			difficulty = diff;
			length = AST_MIN_LENGTH + (rand() % (AST_MAX_LENGTH - AST_MIN_LENGTH));
			width = AST_MIN_WIDTH + (rand() % (AST_MAX_WIDTH - AST_MIN_WIDTH));

			float x, y, z;
			
			//Non randomizzo la posizione della coordinata x del centro in quanto
			//vogliamo che l'asteroide venga generato in fondo alla mappa fuori
			//dalla zona di visibilit�.
			x = MAX_VIS_X + length / 2;
			
			//Il calcolo della coordinata y � randomizzato in modo tale che l'asteroide
			//venga generato completamente all'interno della zona di visibilit� della Y.
			y = (MIN_VIS_Y + width / 2) + (rand() % int(MAX_VIS_Y - MIN_VIS_Y - width));
			z = AST_HEIGHT;

			center = Vertex(x, y, z);

			//Computazione della velocit� lungo le x:
			//In questo caso non abbiamo una velocit� di base fornita dall'esterno. =>
			//=> Usiamo la velocit� di base fornita come costante del modello.
			//Ad essa si aggiunge una quantit� randomica in uno span di valori
			//che varia al variare della difficulty.
			//La velocit� cos� ottenuta viene ulteriormente moltiplicata per la
			//difficulty.
			//Considerando come abbiamo definito il nostro spazio la velocit�
			//lungo le x deve avere un valore negativo.
			speedX = difficulty * (AST_BASE_SPEED_X + (rand() % int(AST_SPAN_SPEED_X * difficulty)));
			speedX = -speedX;

			//La velocit� lungo y pu� essere sia negativa che positiva:
			//dobbiamo randomizzare anche la scelta del segno.
			//Anche in questo caso usiamo la velocit� base fornita come
			//costante al modello.
			int sign;
			int auxRand = rand() % 2;
			if (auxRand)
				sign = 1;
			else
				sign = -1;

			speedY = sign * difficulty * (AST_BASE_SPEED_Y + (rand() % int(AST_SPAN_SPEED_Y * difficulty)));

			toDestroy = false;

			//Definiamo i vertici dell'asteroide utilizzando
			//larghezza e lunghezza
			shape.push_back(Vertex(x + length / 2, y + width / 2, z));
			shape.push_back(Vertex(x + length / 2, y - width / 2, z));
			shape.push_back(Vertex(x - length / 2, y - width / 2, z));
			shape.push_back(Vertex(x - length / 2, y + width / 2, z));

			///TO DO dobbiamo decidere a che indice dell'array delle
			///      texture in model.h corrispondono le varie texture
			///      e quindi scegliere i giusti riferimenti per le
			///      texture della classe.
			
		}

		//SET METHODS
		void setDifficulty(float difficulty) {
			this->difficulty = difficulty;
		}

		void setSpeedX(float speedX) {
			this->speedX = speedX;
		}

		void setSpeedY(float speedY) {
			this->speedY = speedY;
		}

		void setLength(float length) {
			this->length = length;
		}

		void setWidth(float width) {
			this->width = width;
		}

		void setCenter(Vertex center) {

			this->center = center;

			shape.clear();
			shape.push_back(Vertex(center.getX() + length / 2, center.getY() + width / 2, center.getZ()));
			shape.push_back(Vertex(center.getX() + length / 2, center.getY() - width / 2, center.getZ()));
			shape.push_back(Vertex(center.getX() - length / 2, center.getY() - width / 2, center.getZ()));
			shape.push_back(Vertex(center.getX() - length / 2, center.getY() + width / 2, center.getZ()));

		}

		void setToDestroy(bool toDestroy) {
			this->toDestroy = toDestroy;
		}

		void setTexture(int texture) {
			this->texture = texture;
		}
		
		//GET METHODS
		float getDifficulty() {
			return difficulty;
		}

		float getSpeedX() {
			return speedX;
		}

		float getSpeedY() {
			return speedY;
		}

		float getLength() {
			return length;
		}

		float getWidth() {
			return width;
		}

		Vertex getCenter() {
			return center;
		}

		std::vector<Vertex> getShape() {
			return shape;
		}

		bool getToDestroy() {
			return toDestroy;
		}

		int getTexture() {
			return texture;
		}

		//Funzione per verificare se l'oggetto � fuori dalla zona
		//di visibilit�.
		///TO SEE io personalmente non la userei per impedire all'oggetto
		///		  di muoversi, pi� che altro la userei per far scattare la
		///		  "distruzione" dell'oggetto all'interno del modello. =>
		///		  => non consideriamo il movimento ma semplicemente la
		///	      posizione (una volta che � uscito possiamo anche bloccare
		///       il movimento.
		///		  Secondo te la distruzione dell'oggetto va fatta a livello
		///       del modello o qui interna alla classe? Che non mi � molto
		///       chiaro come possiamo fare.
		bool outOfBoundaries() {

			//Bisogna aspettare che l'ultimo pezzo visibile di asteroide
			//sia uscito dalla zona di visibilit�
			if (this->center.getX() - length / 2 > MAX_VIS_X)
				return true;
			else if (speedY < 0 && this->center.getY() + width / 2 < MIN_VIS_Y)
				return true;
			else if (speedY > 0 && this->center.getY() - width / 2 > MAX_VIS_Y)
				return true;
			else
				return false;

		}

		//Funzione che muove l'asteroide nello spazio bidimensionale.
		///TO SEE Non sono sicuro che con il modo che utilizzi
		///       per modificare i vertici sia corretto:
		///       da quello che ho visto con quelle funizioni
		///	      andresti a duplicare ogni volta i membri di shape.
		///		  Io direi di spostare anche il centro, se non � un
		///		  problema concettuale.
		void move() {

			if (!this->outOfBoundaries()) {

				center.modifyP(speedX, speedY);
				for (int i = 0; i < shape.size; i++)
					shape[i].modifyP(speedX, speedY);

			}

		}

};

#endif