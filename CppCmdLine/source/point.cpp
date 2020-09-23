#include "point.h"

Point::Point() :
		X(0), Y(0) {
}

Point::Point(int x, int y) :
		X(x), Y(y) {
}

Point::Point(Point &p) :
		X(p.X), Y(p.Y) {
}

bool Point::operator==(Point &p) {
	return (X == p.X && Y == p.Y);
}

void Point::move(Point &p) {
	X += p.X;
	Y += p.Y;
}

void Point::move(int x, int y) {
	X += x;
	Y += y;
}
