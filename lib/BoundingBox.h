#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <cv.h>
#include <highgui.h>
using namespace cv;

/**
 Calcula el bounding box de la figura dentro de la imagen image.
 */
class BoundingBox {
public:
	BoundingBox(const Mat& image, uchar blobColor);
	Rect getRect();
protected:
private:
	Rect rect;
};

#endif // BOUNDINGBOX_H
