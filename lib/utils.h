/*
 * utils.h
 *
 *  Created on: 11-03-2011
 *      Author: rene128x
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <cv.h>
#include <highgui.h>
#include "ConfigParser.h"
#include "RangeColor.h"
using namespace cv;

// obtiene una submatriz a partir de mat (solo para matrices de 1 solo canal)
//Mat getSubMat1C(const Mat &mat, const Rect &rect);

// obtiene una submatriz a partir de mat (solo para matrices de 1 solo canal)
Mat getSubMat3C(const Mat &mat, const Rect &rect);

// devuelve una copia redimensionada
Mat resizePic(const Mat &source, Size size);

// img debe contener solo pixeles 0 y 255 (totalmente b/n)
void keepBiggestBlob(Mat &img, uchar color);

// indentifica las piezas que hay dibujas sobre el tablero
void recognizePieces(const Mat &tablero, const Rect &rect,
		ConfigParser &config, const vector<RangeColor> &ranges);

#endif /* UTILS_H_ */
