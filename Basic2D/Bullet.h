#ifndef BULLET_H
#define BULLET_H

#include <vector>
#include <time.h>
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>	
#include <math.h>
#include <stdlib.h>
#include "Model.h"
#include "Constant.h"

extern class MyModel Data;

class Bullet {

	private:

		/*MEMBERS*/

		//Velocità del proiettile lungo l'asse x
		float speedX;

		//Dimensioni del proiettile
		float length;
		float width;

		//Centro del proiettile nel nostro spazio
		Vertex center;

		//Lista di vertici che costituiscono la nostra
		//forma geometrica sottostante il proiettile.
		std::vector<Vertex> shape;		

		//Variabile che, qualora settata a true, indica
		//che l'oggetto non deve essere più disegnato e
		//va eliminato quanto prima.
		///TO SEE non so se lasciare che venga settata
		///dall'interno della classe oppure dal modello.
		///In particolare la setterei a true laddove si
		///verifichi la condizione di outOfBoundaries.
		bool toDestroy;					

	public:

		/*METHODS*/

		//Concettualmente è più corretto che il costruttore del proiettile
		//permetta di costruire vari tipi di proiettile e le costanti siano
		//definite in model.h
		Bullet(float x, float y, float z, float speed, float l, float w) {
			
			center = Vertex(x, y, z);
			speedX = speed;

			///TO SEE Invece che il raggio ho messo length e width
			///       in modo da poter mettere proiettili non quadrati.
			//ANSWER complicazione che aviterei per i proiettili facciamoli quadrati che va benissimo che ne dici?
			length = l;
			width = w;
			toDestroy = false;

			//Definiamo i vertici del proiettile utilizzando
			//larghezza e lunghezza
			shape.push_back(Vertex(x + length / 2, y + width / 2, z, 0, 0, 1, 1, 1));
			shape.push_back(Vertex(x + length / 2, y - width / 2, z, 0, 0, 1, 1, 0));
			shape.push_back(Vertex(x - length / 2, y - width / 2, z, 0, 0, 1, 0, 0));
			shape.push_back(Vertex(x - length / 2, y + width / 2, z, 0, 0, 1, 0, 1));

		}

		//SET METHODS
		void setSpeedX(float speedX) {
			this->speedX = speedX;
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
			shape.push_back(Vertex(center.getX() + length / 2, center.getY() + width / 2,
				center.getZ(), 0, 0, 1, 1, 1));

			shape.push_back(Vertex(center.getX() + length / 2, center.getY() - width / 2,
				center.getZ(), 0, 0, 1, 1, 1));

			shape.push_back(Vertex(center.getX() - length / 2, center.getY() - width / 2,
				center.getZ(), 0, 0, 1, 1, 1));

			shape.push_back(Vertex(center.getX() - length / 2, center.getY() + width / 2,
				center.getZ(), 0, 0, 1, 1, 1));

		}

		void setToDestroy(bool toDestroy) {
			this->toDestroy = toDestroy;
		}

		//GET METHODS
		float getSpeedX() {
			return speedX;
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

		//Funzione per verificare se l'oggetto è fuori dalla zona
		//di visibilità.
		///TO SEE io personalmente non la userei per impedire all'oggetto
		///		  di muoversi, più che altro la userei per far scattare la
		///		  "distruzione" dell'oggetto all'interno del modello. =>
		///		  => non consideriamo il movimento ma semplicemente la
		///	      posizione (una volta che è uscito possiamo anche bloccare
		///       il movimento.
		///		  Secondo te la distruzione dell'oggetto va fatta a livello
		///       del modello o qui interna alla classe? Che non mi è molto
		///       chiaro come possiamo fare.
		bool outOfBoundaries() {

			//Bisogna aspettare che l'ultimo pezzo visibile di proiettile
			//sia uscito dalla zona di visibilità
			if (this->center.getX() - length / 2 > MAX_VIS_X)
				return true;
			else
				return false;

		}

		//Funzione che muove il proiettile lungo x.
		///TO SEE Non sono sicuro che con il modo che utilizzi
		///       per modificare i vertici sia corretto:
		///       da quello che ho visto con quelle funizioni
		///	      andresti a duplicare ogni volta i membri di shape.
		///		  Io direi di spostare anche il centro, se non è un
		///		  problema concettuale.
		bool move(double elapsed) {

			if (!this->outOfBoundaries()) {

				center.modifyP(speedX*elapsed, 0);
				for (int i = 0; i < shape.size; i++) 
					shape[i].modifyP(speedX*elapsed, 0);

			}
			return !this->outOfBoundaries();

		}

		void draw() {

			///TO SEE da vedere se in ogni draw dobbiamo fare la
			///glEnable(GL_TEXTURE_2D); oppure se basta farla nel model
			///quando iniziamo a disegnare la scena in generale.
			glBindTexture(GL_TEXTURE_2D, Data.bulletTexture);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0);

			glBegin(GL_QUADS);
			for (int i = 0; i < 4; i++) {
				glTexCoord2f(shape[i].getU(), shape[i].getV());
				glVertex3f(shape[i].getX(), shape[i].getY(), shape[i].getZ());
			}
			glEnd();
			glDisable(GL_BLEND);
			glDisable(GL_ALPHA_TEST);

		}
		
};

#endif