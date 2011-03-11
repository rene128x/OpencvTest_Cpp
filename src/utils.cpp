#include "../lib/utils.h"

// obtiene una submatriz a partir de mat (solo para matrices de 1 solo canal)
Mat getSubMat1C(const Mat &mat, const Rect &rect) {
	Mat temp(Size(rect.width, rect.height), mat.type());
	for (int x = 0; x < rect.width; x++)
		for (int y = 0; y < rect.height; y++)
			temp.at<uchar> (y, x) = mat.at<uchar> (rect.y + y, rect.x + x);
	return temp;
}

// obtiene una submatriz a partir de mat (solo para matrices de 1 solo canal)
Mat getSubMat3C(const Mat &mat, const Rect &rect) {
	Mat temp(Size(rect.width, rect.height), mat.type());
	for (int x = 0; x < rect.width; x++)
		for (int y = 0; y < rect.height; y++)
			temp.at<float> (y, x) = mat.at<float> (rect.y + y, rect.x + x);
	return temp;
}

Mat resizePic(const Mat &source, Size size) {
	Mat destination;
	resize(source, destination, size);
	return destination;
}

// img debe contener solo pixeles 0 y 255 (totalmente b/n)
void keepBiggestBlob(Mat &img, uchar color) {
	uchar complement = (color == 0 ? 255 : 0);
	int w = img.size().width;
	int h = img.size().height;

	vector < Point > blobs;

	int area = -1;
	Point where;
	for (int x = 0; x < w; x++)
		for (int y = 0; y < h; y++) {
			Point p(x, y);
			if (img.at<uchar> (p) == color) {
				int a = floodFill(img, p, Scalar(128));
				blobs.push_back(p);
				if (a > area) {
					area = a;
					where = p;
				}
			}
		}

	floodFill(img, where, Scalar(color));
	for (unsigned i = 0; i < blobs.size(); i++) {
		Point &p = blobs[i];
		if (img.at<uchar> (p) == 128)
			floodFill(img, p, Scalar(complement));
	}
}

void recognizePieces(const Mat &tablero, const Rect &rect){
	int x = rect.x;
	int y = rect.y;
	int width = rect.width;
	int height = rect.height;

//	for(int x=0; x<width; x++)
//		for(int y=0; y<height; y++);
	for(int row =0 ; row<8; row++)
		for(int col= 0; col<8; col++);
}
