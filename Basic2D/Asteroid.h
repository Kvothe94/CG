#ifndef ASTEROID_H
#define ASTEROID_H

#include <vector>
#include <time.h>
#include <GL/gl.h>
#include <math.h>
#include "Model.h"
#include <stdlib.h>

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
		float speedX;
		float speedY;

		//Dimensioni dell'asteroide
		float length;
		float width;

		//Centro dell'asteroide nel nostro spazio
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
		GLuint texture;

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
			speedX = difficulty * (sX + (rand() % (AST_SPAN_SPEED_X * difficulty))) ;
			speedX = -speedX;

			//La velocità lungo y può essere sia negativa che positiva:
			//dobbiamo randomizzare anche la scelta del segno.
			int sign;
			int auxRand = rand() % 2;
			if (auxRand)
				sign = 1;
			else
				sign = -1;
			
			speedY = sign * difficulty * (sY + (rand() % (AST_SPAN_SPEED_Y * difficulty)));
			
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

		}

		///TO SEE Da qui in poi non ho ancora toccato, domani vado avanti

		//Creo asteroide completamente random
		Asteroide(float l) {
			level = l;
			//dimensione cioè raggio dell'asteroide
			r = rand();
			//considero griglia di 100 posizione rand lungo x e y che invece è max cioè 100
			//TO SEE come mai mi trova ma mi da errore sulle costanti definite in model.h?

			//Secondo me è perché in asteroide.h includi model.h e viceversa, non mi sembra
			//una buona idea.

			//TO SEE Dobbiamo definire un'attimo bene la terna ortonormale:
			//	y
			//	|
			//	|				z uscente.
			//	|
			//	|
			//	------------x
			//se lo mettiamo che gli asteroidi arrivano da il fondo della x e vengono verso
			//l'origine allora dobbiamo randomizzare sulle y e non sulle x
			//inoltre la creazione dell'asteroide deve avvenire fuori dall'area visibile e poi
			//deve procedere verso l'asse y.
			float x = rand() * Xmax;
			float y = Ymax - r;
			float z = 0;
			center = Vertex(x, y, z);

			//qui ho definito i vertici del asteroide come un punto centrale con poi spiazzamento
			shape.clear;
			shape.push_back(Vertex(x + r, y + r, z));
			shape.push_back(Vertex(x + r, y - r, z));
			shape.push_back(Vertex(x - r, y - r, z));
			shape.push_back(Vertex(x - r, y + r, z));
			vely = -(1 + rand()*level);
			velx = rand()*level;

		}
		//muovo lasteroide torno true se colpisco il fondo

		// TO SEE io personalmente chiamerei in modo diverso da hit la funzione:
		// conviene usare hit per quando l'asteroide viene colpito da un proiettile
		// e un altro nome per quando va perso: tipo passed o altro.
		bool move() {
			if (hit()) {
				return true;
			}
			else {
				center.modifieP(velx, vely);
				for (int i = 0; i < shape.size; i++) {
					Vertex v = shape.front;
					v.modifieP(velx, vely);
					shape.push_back(v);

				}
				return false;
			}

		}
		//cotrollo se colpisco il fondo 
		bool hit() {
			if (center.getY + vely <= 0) {
				return true;
			}
			return false;
		}




	};

	extern class MyModel Data;











#endif