#include "../lib/WebcamImp.h"

// obtiene una submatriz a partir de mat (solo para matrices de 1 solo canal)
Mat getSubMat(const Mat &mat, const Rect &rect) {
	Mat temp(Size(rect.width, rect.height), mat.type());
	for (int x = 0; x < rect.width; x++)
		for (int y = 0; y < rect.height; y++)
			temp.at<uchar> (y, x) = mat.at<uchar> (rect.y + y, rect.x + x);
	return temp;
}

// construye un informe con el porcentaje mayor de color reconocido
//void boardIntegrity(const Mat &rgbBoard, vector<vector<int> > &table,
//		vector<vector<char> > &kind) {
//	const int side = 8;
//	const int cellMargin = 4;
//
//	table.resize(side);
//	kind.resize(side);
//
//	int width = rgbBoard.size().width / side;
//	int height = rgbBoard.size().height / side;
//	for (int r = 0; r < side; r++) {
//		table[r].resize(side);
//		kind[r].resize(side);
//		for (int c = 0; c < side; c++) {
//			Mat sub = getSubMat(
//					rgbBoard,
//					Rect(c * width + cellMargin, r * height + cellMargin,
//							width - 2 * cellMargin, height - 2 * cellMargin));
//
//			imshow("subpart", sub);
//			waitKey(0);
//		}
//	}
//}

void videoRutine(int cam) {
	cout << "using camera: " << cam << endl;

	Mat tablero = imread("../images/tablero4.jpg", 1);
	Mat grayscale(tablero.size(), CV_8UC1);
	Mat threshed = grayscale.clone();
	Mat floodfilled = grayscale.clone();

	cvtColor(tablero, grayscale, CV_BGR2GRAY);

	GaussianBlur(grayscale, grayscale, Size(11, 11), 0);

	//adaptiveThreshold(grayscale, threshed, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 5, 2);

	threshold(grayscale, threshed, 128, 255, THRESH_BINARY);

	// for(int x=0; x<threshed.size().width; x++)
	// for(int y=0; y<threshed.size().height; y++){
	// uchar color = threshed.at<uchar>(Point(x,y));
	// if(color == 255)
	//;
	// }

	FloodFillBoundingBox ff(threshed, floodfilled, Point(0, 0), 255);
	Rect r;
	int area = -1;

	for (int x = 0; x < threshed.size().width; x++)
		for (int y = 0; y < threshed.size().height; y++) {
			uchar color = threshed.at<uchar> (Point(x, y));
			if (color == 0) {
				FloodFillBoundingBox temp(floodfilled, floodfilled,
						Point(x, y), 128);
				if(temp.getArea() > area){
					area = temp.getArea();
					r = temp.getRect();
				}
			}
		}

	int margin = 10;
	r.x += margin;
	r.y += margin;

	r.width -= 2 * margin;
	r.height -= 2 * margin;

	rectangle(tablero, Point(r.x, r.y), Point(r.x + r.width, r.y + r.height),
			Scalar(0, 255, 0), 2);

	imshow("tablero", tablero);
	imshow("grayscale bottom_left", grayscale);
	imshow("threshed bottom_right", threshed);
	imshow("floodfilled top_right", floodfilled);
	waitKey(0);

	//	Mat board = getSubMat<uchar> (tablero, r);
	//	imshow("board", board);

	//	vector<vector<int> > tabla;
	//	vector<vector<char> > kind;
	//	boardIntegrity(board, tabla, kind);
	//
	//	for (unsigned i = 0; i < tabla.size(); i++) {
	//		for (unsigned j = 0; j < tabla[i].size(); j++)
	//			cout << tabla[i][j] << " ";
	//		cout << "  |  ";
	//		for (unsigned j = 0; j < kind[i].size(); j++)
	//			cout << kind[i][j] << " ";
	//		cout << endl;
	//	}
}

