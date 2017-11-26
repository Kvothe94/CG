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

		//Variabile che contiene le nostre texture.
		///TO SEE In teoria potrebbe servirci più
		///       di una texture in modo da ciclare
		///       e rendere il proiettile un po' più
		///       bello.
		///TO SEE a quanto ho visto le vere e proprie
		///		  texture vengono memorizzate in model.h
		///       nella classe dell'oggetto memorizzi i
		///       riferimenti alle texture di model.h.
		int texture;					

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
			length = l;
			width = w;
			toDestroy = false;

			//Definiamo i vertici del proiettile utilizzando
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

		int getTexture() {
			return texture;
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
		void move() {

			if (!this->outOfBoundaries()) {

				center.modifyP(speedX, 0);
				for (int i = 0; i < shape.size; i++) 
					shape[i].modifyP(speedX, 0);

			}

		}

		/*
		//muove il proiettile lungo y
		void Move() {
			if (limitOk(center)) {
				for (int i = 0; i < shape.size; i++) {
					Vertex v = shape.front;
					v.modifieP(0, vely);
					shape.push_back(v);

				}
			}
		}
		*/

};

#endif