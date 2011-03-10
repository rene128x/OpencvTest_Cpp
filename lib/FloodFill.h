#ifndef FLOODFILL_H_
#define FLOODFILL_H_
#include <highgui.h>
#include <cv.h>
using namespace cv;

class FloodFillBoundingBox {
public:
	FloodFillBoundingBox(const Mat &source, Mat &dest, const Point &where, uchar color);
	int getArea();
	Rect getRect();
private:
	int area;
	Rect rect;
	uchar initialColor;
};

#endif // FLOODFILL_H_
