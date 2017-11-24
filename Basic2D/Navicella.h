
#pragma warning(disable: 4996)

#include <vector>
#include <time.h>
#include <GL/gl.h>
#include <math.h>
#include "Model.h"
#include <stdlib.h>
class Navicella {

public:
	
	float vely;
	float r = 5;
	Vertex center;
	std::vector<Vertex> shape;   //vertici

	//TO SEE non so come mai non riconosca questo elemento		
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
	bool limitOk(Vertex v,float x){
		if (v.getX()+x > 100 || v.getX+x < 0){
			return false;
		}
		return true;

	}
	//muove la navicella lungo x
	void Move(float x){
		if (limitOk(center,x)){
			for (int i = 0; i < shape.size; i++){
				Vertex v = shape.front;
				v.modifieP(x, 0);
				shape.push_back(v);
				
			}
		}
		

		
	}

};