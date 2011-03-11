#ifndef WEBCAMIMP_H_
#define WEBCAMIMP_H_


#include <cv.h>
#include <highgui.h>
using namespace cv;

#include <iostream>
using namespace std;

#include "../lib/FloodFill.h"

// obtiene una submatriz a partir de mat
Mat getSubMat(const Mat &mat, const Rect &rect);

// construye un informe con el porcentaje mayor de color reconocido
void boardIntegrity(const Mat &rgbBoard, vector<vector<int> > &table,
		vector<vector<char> > &kind) ;

void videoRutine(int cam);

#endif /* WEBCAMIMP_H_ */
