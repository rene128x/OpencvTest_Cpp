#include "../lib/FloodFill.h"
#include <queue>
using namespace std;

// solo propaga el color a los 4-neighbors de cada pixel
FloodFillBoundingBox::FloodFillBoundingBox(const Mat &source, Mat &dest,
		const Point &where, uchar color) {
	area = 0;
	uchar initial = source.at<uchar> (where);

	int width = source.size().width;
	int height = source.size().height;

	Mat used(source.size(), source.type(), Scalar(0, 0, 0));

	queue<Point> cola;
	cola.push(where);

	int L = width, R = -1, T = -1, B = height;

	while (cola.size()) {
		Point p = cola.front();
		cola.pop();

		if (p.x < 0 || p.x >= width || p.y < 0 || p.y >= height)
			continue;

		if (!used.at<uchar> (p) && source.at<uchar> (p) == initial) {

			// almacenar la medida del mayor boundingbox
			L = min(L, p.x);
			R = max(R, p.x);
			T = max(T, p.y);
			B = min(B, p.y);

			used.at<uchar> (p) = 255;
			dest.at<uchar> (p) = color;
			area++;
			cola.push(Point(p.x + 1, p.y));
			cola.push(Point(p.x - 1, p.y));
			cola.push(Point(p.x, p.y + 1));
			cola.push(Point(p.x, p.y - 1));
		}
	}

	rect = Rect(Point(L, T), Point(R, B));
}

int FloodFillBoundingBox::getArea() {
	return area;
}

Rect FloodFillBoundingBox::getRect() {
	return rect;
}
