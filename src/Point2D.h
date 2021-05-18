#pragma once
#include <iostream>

class Point2D
{
public:
	float x, y;

	Point2D() {
		x = 0, y = 0;
	}

	Point2D(float x, float y) {
		this->x = x, this->y = y;
	}
	
	Point2D add(Point2D p2) {
		return Point2D(this->x + p2.x, this->y + p2.y);
	}
	Point2D sub(Point2D p2) {
		return Point2D(this->x - p2.x, this->y - p2.y);
	}
	Point2D mul(Point2D p2) {
		return Point2D(this->x * p2.x, this->y * p2.y);
	}
	
	Point2D scalerMul(float scale) {
		return Point2D(this->x * scale, this->y * scale);
	}

	void print() {
		std::cout << "x:" << this->x << " y:" << this->y << std::endl;
	}
	
};