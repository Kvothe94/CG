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

class Button {

	private:

		std::vector<Vertex> shape;
		bool pressed;
		int type;


	public:

		Button(int type) {

			float x, y, z;
			this->type = type;

			switch (type) {

				case 0:
					x = 0 - BUTTON_LENGTH - BUTTON_DISTANCE;
					y = 0;
					z = BUTTON_HEIGHT;
					break;

				case 1:
					x = 0;
					y = 0;
					z = BUTTON_HEIGHT;
					break;

				case 2:
					x = 0 + BUTTON_LENGTH + BUTTON_DISTANCE;
					y = 0;
					z = BUTTON_HEIGHT;
					break;

			}

			shape.clear();

			shape.push_back(Vertex(x - BUTTON_LENGTH / 2, y - BUTTON_WIDTH / 2, BUTTON_HEIGHT, 0, 0, 1, 0, 0));
			shape.push_back(Vertex(x - BUTTON_LENGTH / 2, y + BUTTON_WIDTH / 2, BUTTON_HEIGHT, 0, 0, 1, 0, 1));
			shape.push_back(Vertex(x + BUTTON_LENGTH / 2, y + BUTTON_WIDTH / 2, BUTTON_HEIGHT, 0, 0, 1, 1, 1));
			shape.push_back(Vertex(x + BUTTON_LENGTH / 2, y - BUTTON_WIDTH / 2, BUTTON_HEIGHT, 0, 0, 1, 1, 0));

			pressed = false;

		}

		int getType() {
			return type;
		}

		std::vector<Vertex> getShape(){
			return shape;
		}

		bool getPressed() {
			return pressed;
		}

		void setPressed(bool pressed) {
			this->pressed = pressed;
		}

};