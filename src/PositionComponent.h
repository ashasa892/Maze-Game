#pragma once
#include "ECS.h"
#include "Point2D.h"

class PositionComponent : public Component
{
public:

	Point2D pos, velocity;
	int speed = 3;

	PositionComponent() {
		pos = Point2D();
	}

	PositionComponent(int x, int y) {
		pos = Point2D(x, y);
	}

	void init() override{
		velocity = Point2D(0, 0);

	}


	

	void update() override
	{
		pos = pos.add(velocity.scalerMul(speed));
	}


	void setPos(Point2D newPos) {
		pos = newPos;
	}

private:
	

};