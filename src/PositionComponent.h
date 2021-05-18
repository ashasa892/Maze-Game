#include "ECS.h"


class PositionComponent : public Component
{
public:

	PositionComponent() {
		xpos = 0, ypos = 0;
	}

	PositionComponent(int x, int y) {
		xpos = x, ypos = y;
	}

	int x() {
		return xpos;
	}
	int y() {return ypos;}

	

	void update() override
	{
		xpos++;
		ypos++;
	}


	void setPos(int x, int y) {
		xpos = x;
		ypos = y;
	}

private:
	int xpos, ypos;

};