#include "../lib/BoundingBox.h"

// TODO reimplementar para que funcione eficientemente
BoundingBox::BoundingBox(const Mat &image, uchar blobColor) {
	int width = image.size().width;
	int height = image.size().height;

	int _left = 0, _top = 0, _right = width - 1, _bottom = height - 1;

	// variables temporales
	int x, y;

	// lado izquierdo
	for (x = _left; x < _right; x++)
		for (y = _top; y <= _bottom; y++)
			if (image.at<uchar> (y, x) == blobColor) {
				_left = x;
				x = _right + 1;
				break;
			}

	//lado derecho
	for (x = _right; x >= _left; x--)
		for (y = _top; y <= _bottom; y++)
			if (image.at<uchar> (y, x) == blobColor) {
				_right = x;
				x = _left - 1;
				break;
			}

	// lado superior
	for (y = _top; y < _bottom; y++)
		for (x = _left; x <= _right; x++)
			if (image.at<uchar> (y, x) == blobColor) {
				_top = y;
				y = _bottom + 1;
				break;
			}

	// lado inferior
	for (y = _bottom; y >= _top; y--)
		for (x = _left; x <= _right; x++)
			if (image.at<uchar> (y, x) == blobColor) {
				_bottom = y;
				y = _top - 1;
				break;
			}

	rect = Rect(Point(_left, _top), Point(_right, _bottom));
}

Rect BoundingBox::getRect() {
	return rect;
}
