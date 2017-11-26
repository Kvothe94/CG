
#ifndef VERTEX_H
#define VERTEX_H

class Vertex {

	private:

		float x, y, z;
		float nX, nY, nZ;

	public:

		Vertex() {

			x = 0; y = 0; z = 0;
			nX = 0; nY = 0; nZ = 0;

		}

		Vertex(float x, float y, float z) { 

			this->x = x;
			this->y = y;
			this->z = z;

		}

		Vertex(float x, float y, float z, float nX, float nY, float nZ) {

			this->x = x;
			this->y = y;
			this->z = z;
			this->nX = nX;
			this->nY = nY;
			this->nZ = nZ;

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

#endif