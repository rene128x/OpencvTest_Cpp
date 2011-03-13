#include "../lib/utils.h"

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

	vector<Point> blobs;

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

#include <iostream>
using namespace std;

void recognizePieces(const Mat &tablero, const Rect &r, ConfigParser &config,
		const vector<RangeColor> &ranges) {
	cout << "recognizing pieces amongst " << ranges.size()
			<< " different colors." << endl;
	int boardMargin = config.getProperty("board_margin");
	int internalMargin = config.getProperty("cell_margin");

	int R = config.getProperty("grid_R");
	int G = config.getProperty("grid_G");
	int B = config.getProperty("grid_B");
	int thickness = config.getProperty("grid_thickness");

	int x = r.x + boardMargin;
	int y = r.y + boardMargin;
	int width = r.width - 2 * boardMargin;
	int height = r.height - 2 * boardMargin;

	double bw = width / 8.0;
	double bh = height / 8.0;

	Mat parsed_board = tablero.clone();

	rectangle(parsed_board, Point(x, y), Point(x + width, y + height),
			Scalar(B, G, R), thickness);
	//imshow("parsed_board center_center", resizePic(tablero, Size(320, 240)));


	// TODO implementar velocidad!
	for (int row = 0; row < 8; row++)
		for (int col = 0; col < 8; col++) {

			Rect rt((int) (x + col * bw + internalMargin),
					(int) (y + row * bh + internalMargin),
					(int) (bw - 2 * internalMargin),
					(int) (bh - 2 * internalMargin));

			Mat subCell(parsed_board, rt);
			rectangle(parsed_board, Point(rt.x, rt.y),
					Point(rt.x + rt.width, rt.y + rt.height), Scalar(B, G, R),
					thickness);
#if true
			// TODO
			int which = -1;
			for (unsigned i = 0; i < ranges.size(); i++)
				if (ranges[i].inRange(subCell)) {
					if (which == -1) {
						which = i;
						putText(parsed_board, ranges[i].getID(),
								Point(rt.x, rt.y + 10), FONT_HERSHEY_PLAIN,
								0.8, Scalar(0, 255, 0));
					} else {
						cout << "Detected again. Ranges should be exclusive."
								<< endl;
						break;
					}
					//break;
				}
			//imshow("img",  img);
			//waitKey(0);
#endif
		}

	imshow("parsed_board center_center", parsed_board);
}
