#ifndef __LINE_H__
#define __LINE_H__

class Line {
	public:
		Line(Point &P1, Point &P2);
		double length();

	private:
		Point p1;
		Point p2;
};

#endif
