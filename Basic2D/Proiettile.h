#pragma warning(disable: 4996)

#include <vector>
#include <time.h>
#include <GL/gl.h>
#include <math.h>
#include "Model.h"
#include <stdlib.h>
class Proiettile {

public:

	// TO SEE sempre secondo il piano cartesiano disegnato in asteroide.h
	// il proiettile si muove lungo le x => velx
	float vely;
	float r = 2;
	Vertex center;
	std::vector<Vertex> shape;   //vertici

	//TO SEE non so come mai non riconosca questo elemento		
	GLuint	texture;				// Base Display List For The Font Set
public:
	Proiettile(float x, float y, float z, float u, float v, float l)  {
		center = Vertex(x, y, 0);

		vely = 5;
		
		//qui ho definito i vertici del proiettile come un punto centrale con poi spiazzamento
		shape.push_back(Vertex(x + r, y + r, z));
		shape.push_back(Vertex(x + r, y - r, z));
		shape.push_back(Vertex(x - r, y - r, z));
		shape.push_back(Vertex(x - r, y + r, z));
		

	}
	//controllo se sono arrivato in cima
	//TO SEE anche qui bisogna prima farlo uscire dalla zona visibile e poi
	//distruggerlo.

	bool limitOk(Vertex v){
		
		if (v.getY + vely>100){
			return false;
		}
		return true;

	}
	
	//muove il proiettile lungo y
	void Move(){
		if (limitOk(center)){
			for (int i = 0; i < shape.size; i++){
				Vertex v = shape.front;
				v.modifieP(0,vely);
				shape.push_back(v);

			}
		}



	}

};