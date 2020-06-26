#ifndef POSITION_H
#define POSITION_H

namespace Utility
{
	class Position
	{
	public:
		Position(float X, float Y,float Z = 0) : x(X), y(Y),z(Z) {}
	
		float x;
		float y;
		float z;
	};
}

#endif
