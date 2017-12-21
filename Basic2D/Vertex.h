#pragma once

class Vertex {

	private:

		float x, y, z;			//Cartesian Coordinates.
		float nX, nY, nZ;		//Vertex normal.
		float u, v;				//Texture Coordinates.
		float r, g, b;			//Color.

	public:

		Vertex() {

			x = 0; y = 0; z = 0;
			nX = 0; nY = 0; nZ = 0;
			u = 0; v = 0;
			r = 0; g = 0; b = 0;

		}

		Vertex(float x, float y, float z) { 

			this->x = x;
			this->y = y;
			this->z = z;
			this->nX = 0;
			this->nY = 0;
			this->nZ = 0;
			this->u = 0;
			this->v = 0;
			this->r = 0;
			this->g = 0;
			this->b = 0;

		}

		Vertex(float x, float y, float z, float nX, float nY, float nZ) {

			this->x = x;
			this->y = y;
			this->z = z;
			this->nX = nX;
			this->nY = nY;
			this->nZ = nZ;
			this->u = 0;
			this->v = 0;
			this->r = 0;
			this->g = 0;
			this->b = 0;

		}

		Vertex(float x, float y, float z, float nX, float nY, float nZ, float u, float v) {

			this->x = x;
			this->y = y;
			this->z = z;
			this->nX = nX;
			this->nY = nY;
			this->nZ = nZ;
			this->u = u;
			this->v = v;
			this->r = 0;
			this->g = 0;
			this->b = 0;

		}

		Vertex(float x, float y, float z, float nX, float nY, float nZ,
			float u, float v, float r, float g, float b) {

			this->x = x;
			this->y = y;
			this->z = z;
			this->nX = nX;
			this->nY = nY;
			this->nZ = nZ;
			this->u = u;
			this->v = v;
			this->r = r;
			this->g = g;
			this->b = b;

		}

		void setX(float x) {
			this->x = x;
		}

		void setY(float y) {
			this->y = y;
		}
		void setZ(float z) {
			this->z = z;
		}

		void setNX(float nX) {
			this->nX = nX;
		}

		void setNY(float nY) {
			this->nY = nY;
		}

		void setNZ(float nZ) {
			this->nZ = nZ;
		}

		void setU(float u) {
			this->u = u;
		}

		void setV(float v) {
			this->v = v;
		}

		void setR(float r) {
			this->r = r;
		}

		void setG(float g) {
			this->g = g;
		}

		void setB(float b) {
			this->b = b;
		}

		float getX() {
			return x;
		}

		float getY() {
			return y;
		}
		
		float getZ() {
			return z;
		}

		float getNX() {
			return nX;
		}

		float getNY() {
			return nY;
		}

		float getNZ() {
			return nZ;
		}

		float getU() {
			return u;
		}

		float getV() {
			return v;
		}

		float getR() {
			return r;
		}

		float getG() {
			return g;
		}

		float getB() {
			return b;
		}

		inline void SetP(float x, float y, float z) {

			this->x = x;
			this->y = y;
			this->z = z;

		}

		inline void SetN(float nX, float nY, float nZ) {

			this->nX = nX;
			this->nY = nY;
			this->nZ = nZ;

		}
		
		inline void modifyP(float x1, float y1) {
			
			this->x = x + x1;
			this->y = y + y1;
			this->z = z; 

		}

};
