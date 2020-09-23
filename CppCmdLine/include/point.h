#ifndef __POINT_H__
#define __POINT_H__

class Point {

public:
	Point();
	Point(int x, int y);
	Point(Point &p);
	bool operator==(Point &p);

	int getX() {
		return X;
	}
	int getY() {
		return Y;
	}

	void move(Point &p);
	void move(int x, int y);

protected:
	int X;
	int Y;
};

#endif
