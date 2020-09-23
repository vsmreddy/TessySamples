#include <math.h>

#include "point.h"
#include "line.h"

extern int absolute(int v);

Line::Line(Point &P1, Point &P2) :
		p1(P1), p2(P2) {
}

double Line::length() {
	// Check for horizontal or vertical lines
	if (p1.getX() == p2.getX()) {
		return absolute(p1.getY() - p2.getY());
	}
	if (p1.getY() == p2.getY()) {
		return absolute(p1.getX() - p2.getX());
	}

	// All other line directions
	int a = p2.getX() - p1.getX();
	int b = p2.getY() - p1.getY();

	return sqrt((a * a) + (b * b));
}

