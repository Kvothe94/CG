#pragma once

#include <vector>
#include <time.h>
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>	
#include <math.h>
#include <stdlib.h>
#include "Model.h"
#include "Constant.h"
#include "Vertex.h"

class Asteroid {

	private:

		/*MEMBERS*/

		//Variabile che fa da moltiplicatore per la velocità
		//di movimento dell'asteroide: andremo ad aumentarla
		//con il passare del tempo di gioco.
		float difficulty;

		//Velocità, intese in termini vettoriali, dell'asteroide
		//lungo i due assi.
		///TO SEE PROBLEMA: se consideriamo il nostro spazio come
		///       nel disegno che ho messo in Data allora le velocità
		///       lungo x e y rispettivamente saranno e potranno essere
		///       negative. Dici che va bene?
		//ANSWER si lungo y positive e negstive mentre lungo x direi solo negative
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

		

		//Variabile che memorizza il tempo a cui il 
		//Aanswer per cosa la vuoi usare io forse la terrei per far si che 
		//l'esplosione sia visibile per qualche ciclo tipo 1 o 2 e poi eliminerei il tutto?? 
		//che ne dici?
		double hittingTime;

		//Variabile che, qualora settata a true, indica
		//che l'oggetto non deve essere più disegnato e
		//va eliminato quanto prima.
		///TO SEE non so se lasciare che venga settata
		///dall'interno della classe oppure dal modello.
		///In particolare la setterei a true laddove si
		///verifichi la condizione di outOfBoundaries.
		//Answer io come concordato con gratta non la userei perche distruggiamo togliendo direttamente dal array
		bool toDestroy;
		///TO SEE: guarda queste due variabili, dobbiamo
		///considerarle se vogliamo fare gli effetti di esplosione.
		//Variabile che, qualora settata a true, indica
		//che l'oggetto è stato colpito e pertanto deve
		//essere disegnato in fase di esplosione.
		//Se tale variabile è a true l'oggetto deve
		//smettere di muoversi (l'esplosione non si muove).
		bool hitten;

		//Variabile che contiene le nostre texture.
		///TO SEE In teoria potrebbe servirci più
		///       di una texture in modo da ciclare
		///       e rendere l'asteroide un po' più
		///       bello, idem per l'esplosione.
		///TO SEE a quanto ho visto le vere e proprie
		///		  texture vengono memorizzate in model.h
		///       nella classe dell'oggetto memorizzi i
		///       riferimenti alle texture di model.h.
		// ANSWER penso sia una specifica da chiedere a grattarola domani
		int texture;
		int explosionTexture;

	public:
		
		/*METHODS*/

		Asteroid(float x, float y, float z, float sX, float sY, float diff, float l, float w) {

			center = Vertex(x, y, z);
			difficulty = diff;

			//Computazione della velocità lungo le x:
			//Dal costruttore viene fornita la velocità di base lungo le x.
			//Ad essa si aggiunge una quantità randomica in uno span di valori
			//che varia al variare della difficulty.
			//La velocità così ottenuta viene ulteriormente moltiplicata per la
			//difficulty.
			//Considerando come abbiamo definito il nostro spazio la velocità
			//lungo le x deve avere un valore negativo.
			speedX = difficulty * (sX + (rand() % int(AST_SPAN_SPEED_X * difficulty))) ;
			speedX = -speedX;

			//La velocità lungo y può essere sia negativa che positiva:
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
			//ANSWER io direi che basta il raggio per il motivo che ti pecifico nell'audio numero 1
			length = l;
			width = w;
			toDestroy = false;

			//Definiamo i vertici dell'asteroide utilizzando
			//larghezza e lunghezza
			shape.push_back(Vertex(x + length / 2, y + width / 2, z, 0, 0, 1, 1, 1));
			shape.push_back(Vertex(x + length / 2, y - width / 2, z, 0, 0, 1, 1, 0));
			shape.push_back(Vertex(x - length / 2, y - width / 2, z, 0, 0, 1, 0, 0));
			shape.push_back(Vertex(x - length / 2, y + width / 2, z, 0, 0, 1, 0, 1));

			//Scegliamo quale delle 4 texture usare randomicamente,
			//in modo da dare varianza all'aspetto degli asteroidi.
			texture = rand() % 4;

		}

		//Costruttore che genera un asteroide con dimensioni, posizione e velocità
		//randomiche.
		Asteroid(float diff) {
			
			difficulty = diff;
			length = AST_MIN_LENGTH + (rand() % (AST_MAX_LENGTH - AST_MIN_LENGTH));
			width = AST_MIN_WIDTH + (rand() % (AST_MAX_WIDTH - AST_MIN_WIDTH));

			float x, y, z;
			
			//Non randomizzo la posizione della coordinata x del centro in quanto
			//vogliamo che l'asteroide venga generato in fondo alla mappa fuori
			//dalla zona di visibilità.
			x = MAX_VIS_X + length / 2;
			
			//Il calcolo della coordinata y è randomizzato in modo tale che l'asteroide
			//venga generato completamente all'interno della zona di visibilità della Y.
			y = (MIN_VIS_Y + width / 2) + (rand() % int(MAX_VIS_Y - MIN_VIS_Y - width));
			z = AST_HEIGHT;

			center = Vertex(x, y, z);

			//Computazione della velocità lungo le x:
			//In questo caso non abbiamo una velocità di base fornita dall'esterno. =>
			//=> Usiamo la velocità di base fornita come costante del modello.
			//Ad essa si aggiunge una quantità randomica in uno span di valori
			//che varia al variare della difficulty.
			//La velocità così ottenuta viene ulteriormente moltiplicata per la
			//difficulty.
			//Considerando come abbiamo definito il nostro spazio la velocità
			//lungo le x deve avere un valore negativo.
			speedX = difficulty * (AST_BASE_SPEED_X + (rand() % int(AST_SPAN_SPEED_X * difficulty)));
			speedX = -speedX;

			//La velocità lungo y può essere sia negativa che positiva:
			//dobbiamo randomizzare anche la scelta del segno.
			//Anche in questo caso usiamo la velocità base fornita come
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
			shape.push_back(Vertex(x + length / 2, y + width / 2, z, 0, 0, 1, 1, 1));
			shape.push_back(Vertex(x + length / 2, y - width / 2, z, 0, 0, 1, 1, 0));
			shape.push_back(Vertex(x - length / 2, y - width / 2, z, 0, 0, 1, 0, 0));
			shape.push_back(Vertex(x - length / 2, y + width / 2, z, 0, 0, 1, 0, 1));

			//Scegliamo quale delle 4 texture usare randomicamente,
			//in modo da dare varianza all'aspetto degli asteroidi.
			texture = rand() % 4;
			
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
			shape.push_back(Vertex(center.getX() + length / 2, center.getY() + width / 2,
				center.getZ(), 0, 0, 1, 1, 1));

			shape.push_back(Vertex(center.getX() + length / 2, center.getY() - width / 2,
				center.getZ(), 0, 0, 1, 1, 1));

			shape.push_back(Vertex(center.getX() - length / 2, center.getY() - width / 2,
				center.getZ(), 0, 0, 1, 1, 1));

			shape.push_back(Vertex(center.getX() - length / 2, center.getY() + width / 2,
				center.getZ(), 0, 0, 1, 1, 1));

		}

		void setHitten(bool hitten) {
			this->hitten = hitten;
		}

		void setHittingTime(double hittingTime) {
			this->hittingTime = hittingTime;
		}

		void setToDestroy(bool toDestroy) {
			this->toDestroy = toDestroy;
		}

		void setTexture(int texture) {
			this->texture = texture;
		}

		void setExplosionTexture(int explosionTexture) {
			this->explosionTexture = explosionTexture;
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

		bool getHitten() {
			return hitten;
		}

		double getHittingTime() {
			return hittingTime;
		}

		bool getToDestroy() {
			return toDestroy;
		}

		int getTexture() {
			return texture;
		}

		int setExplosionTexture() {
			return explosionTexture;
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
		//ANSWER io con distruzione dell'asteroide semplicemente lo rimuoverei dalla lista di asteroidi del model.h
		bool outOfBoundaries() {

			//Bisogna aspettare che l'ultimo pezzo visibile di asteroide
			//sia uscito dalla zona di visibilità
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
		///		  Io direi di spostare anche il centro, se non è un
		///		  problema concettuale.
		//ANSWER ci avevo pensato a spostare il centro anzi che i vertici, io spostavo entrambi se non ricordo male vedi audio2
		bool move(double elapsed) {

			if (!this->outOfBoundaries()) {

				center.modifyP(speedX*elapsed, speedY*elapsed);
				for (int i = 0; i < shape.size(); i++)
					shape[i].modifyP(speedX*elapsed, speedY*elapsed);

			}
			return !this->outOfBoundaries();


		}

};