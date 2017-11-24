
#pragma warning(disable: 4996)

#include <vector>
#include <time.h>
#include <GL/gl.h>
#include <math.h>
#include "Model.h"
#include <stdlib.h>
class Navicella {

public:
	
	float velx;
	float r = 5;
	Vertex center;
	std::vector<Vertex> shape;   //vertici

	
	GLuint	texture;				// Base Display List For The Font Set
public:
	Navicella()  {
		center = Vertex(50, r, 0);
		shape.clear;
		//qui ho definito i vertici del asteroide come un punto centrale con poi spiazzamento
		shape.push_back(Vertex(50+r,  2*r, 0));
		shape.push_back(Vertex(50 + r, 0, 0));
		shape.push_back(Vertex(50-r, 0, 0));
		shape.push_back(Vertex(50- r, 2*r, 0));
		

	}
	//controlla se non siamo fuori dalla griglia
	//TO SEE Stessa cosa di prima: se facciamo come abbiamo detto
	//a grattarola la nave si muove lungo le y, non le x
	//come per altro mi sembra faccia dato la vely
	bool limitOk(Vertex v,float x){
		if (v.getX()+x > 100 || v.getX+x < 0){
			return false;
		}
		return true;

	}
	//muove la navicella lungo x
	void Move(){
		if (limitOk(center,velx)){
			for (int i = 0; i < shape.size; i++){
				Vertex v = shape.front;
				v.modifieP(velx, 0);
				shape.push_back(v);
				
			}
		}
		

		
	}

};