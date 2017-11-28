#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <vector>
#include <time.h>
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>	
#include <math.h>
#include <stdlib.h>
#include "Model.h"
#include "Constant.h"

class Spaceship {

	private:

		/*MEMBERS*/

		//Velocità della navicella lungo l'asse y.
		float baseSpeedY;

		//Dimensioni della navicella.
		float length;
		float width;

		//Centro della navicella nel nostro spazio
		Vertex center;

		//Lista di vertici che costituiscono la nostra
		//forma geometrica sottostante la navicella.
		//TO SEE forse meglio toglierli?
		std::vector<Vertex> shape;

		//Variabile che, qualora settata a true, indica
		//che l'oggetto non deve essere più disegnato e
		//va eliminato quanto prima.
		///TO SEE non so se lasciare che venga settata
		///dall'interno della classe oppure dal modello.
		///In particolare la setterei a true laddove si
		///verifichi la condizione di outOfBoundaries.
		//ANSEWR se semplicemente facessico if(outofboundaries()) remove from list; ? Non capisco perche mettere
		//questa variabile? Stessa cosa anche per proiettili e asteroidi
		bool toDestroy;

		//Variabile che contiene le nostre texture.
		///TO SEE In teoria potrebbe servirci più
		///       di una texture in modo da ciclare
		///       e rendere l'asteroide un po' più
		///       bello, idem per l'esplosione.
		///TO SEE a quanto ho visto le vere e proprie
		///		  texture vengono memorizzate in model.h
		///       nella classe dell'oggetto memorizzi i
		///       riferimenti alle texture di model.h.
		int texture;
		int explosionTexture;

	public:

		/*METHODS*/

		Spaceship() {

			float x, y, z;
			x = MIN_VIS_X + length / 2;
			y = (MAX_VIS_Y - MIN_VIS_Y) / 2;
			//TO SEE perche laltezza?
			z = SS_HEIGHT;

			center = Vertex(x, y, z);
			baseSpeedY = SS_BASE_SPEED;

			///TO SEE Invece che il raggio ho messo length e width
			///       in modo da poter mettere astronavi non quadrate.
			length = SS_LENGTH;
			width = SS_WIDTH;
			toDestroy = false;

			//Definiamo i vertici dell'astronave utilizzando
			//larghezza e lunghezza
			shape.push_back(Vertex(x + length / 2, y + width / 2, z));
			shape.push_back(Vertex(x + length / 2, y - width / 2, z));
			shape.push_back(Vertex(x - length / 2, y - width / 2, z));
			shape.push_back(Vertex(x - length / 2, y + width / 2, z));

			///TO DO dobbiamo decidere a che indice dell'array delle
			///      texture in model.h corrispondono le varie texture
			///      e quindi scegliere i giusti riferimenti per le
			///      texture della classe.
			//ANSWER di nuovo da chiedere a grattarola audio 3

		}

		//SET METHODS

		void setBaseSpeedY(float baseSpeedY) {
			this->baseSpeedY = baseSpeedY;
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

		float getBaseSpeedY() {
			return baseSpeedY;
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

		//Funzione per verificare se la navicella esce dalla zona di visibilità
		//se si effettua il movimento richiesto.
		///TO SEE in questo caso la utilizziamo per impedire il movimento al
		///di fuori dei limiti.
		//ANSWER ok concordo anche sulle funzionalità della f sottostante
		bool outOfBoundaries(bool up) {

			//Supponendo che il proiettile esca da metà della larghezza
			//dell'astronave, affinchè sia possibile distruggere qualsiasi
			//asteroide ancora nella zona visibile, permettiamo all'astronave
			//di essere fuori dalla zona visibile al massimo per metà.
			//up ci indica se il movimento è positivo lungo le y o negativo.
			if (up && this->center.getY() + baseSpeedY > MAX_VIS_Y)
				return true;
			else if (!up && this->center.getY() - baseSpeedY < MIN_VIS_Y)
				return true;
			else
				return false;

		}

		//Funzione che muove l'astronave lungo l'asse y.
		///TO SEE a cosa serve up? se riusciamo a toglierlo verrebbe meglio
		void move(bool up,double elapsed) {

			if (!this->outOfBoundaries(up)) {

				center.modifyP(0, baseSpeedY*elapsed);
				for (int i = 0; i < shape.size; i++)
					center.modifyP(0, baseSpeedY*elapsed);

			}

		}

};

#endif