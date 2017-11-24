#pragma warning(disable: 4996)

#include <vector>
#include <time.h>
#include <GL/gl.h>
#include <math.h>
#include "Model.h"
#include <stdlib.h>




class Asteroide {

public:
	float level;//livello di difficoltà esso va a moltiplicare sia la velocita che la dimensione
	float velx;
	float vely;
	float r;//dimensione
	Vertex center;
	std::vector<Vertex> shape;   //vertici
	
		//TO SEE non so come mai non riconosca questo elemento		
	GLuint	texture;				// Base Display List For The Font Set
public:
	Asteroide(float x, float y, float z, float u, float v,float l)  {
		center = Vertex(x, y, 0);

		level = l;
		r = rand()*level;
		//qui ho definito i vertici del asteroide come un punto centrale con poi spiazzamento
		shape.push_back(Vertex(x + r, y + r, z));
		shape.push_back(Vertex(x + r, y - r, z));
		shape.push_back(Vertex(x - r, y - r, z));
		shape.push_back(Vertex(x - r, y + r, z));
		velx = 1 + rand()*level;
		vely = rand()*level;

	}
	//Creo asteroide completamente random
	Asteroide(float l)  {
		level = l;
		//dimensione cioè raggio dell'asteroide
		r = rand();
		//considero griglia di 100 posizione rand lungo x e y che invece è max cioè 100
		//TO SEE come mai mi trova ma mi da errore sulle costanti definite in model.h?
		float x = rand() * Xmax;
		float y = Ymax-r;
		float z = 0;
		center = Vertex(x, y, z);
		
		//qui ho definito i vertici del asteroide come un punto centrale con poi spiazzamento
		shape.clear;
		shape.push_back(Vertex(x + r, y + r, z));
		shape.push_back(Vertex(x + r, y - r, z));
		shape.push_back(Vertex(x - r, y - r, z));
		shape.push_back(Vertex(x - r, y + r, z));
		vely =-( 1 + rand()*level);
		velx = rand()*level;

	}
	//muovo lasteroide torno true se colpisco il fondo
	bool move(){
		if (hit()){
			return true;
		}
		else{
			center.modifieP(velx, vely);
			for (int i = 0; i < shape.size; i++){
				Vertex v = shape.front;
				v.modifieP(velx, vely);
				shape.push_back(v);

			}
			return false;
		}
		
	}
	//cotrollo se colpisco il fondo 
	bool hit(){
		if (center.getY + vely <= 0){
			return true;
		}
		return false;
	}
	

	

};

extern class MyModel Data;