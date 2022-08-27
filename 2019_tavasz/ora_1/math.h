#ifndef MATH_H
#define MATH_H

static const float PI = 3.1415;

namespace Geometry {

	struct Point {
		int x;
		int y;
	};

	struct Line {
		Point p1;
		Point p2;
	};
}

#endif

