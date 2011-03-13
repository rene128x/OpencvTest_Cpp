/*
 * RangeColor.h
 *
 *  Created on: 11-03-2011
 *      Author: rene128x
 */

#ifndef RANGECOLOR_H_
#define RANGECOLOR_H_

#include <cv.h>
#include <highgui.h>
#include <sstream>
#include <string>
using namespace std;
using namespace cv;

class RangeColor {
public:
	RangeColor(const Scalar &min_hsv, const Scalar &max_hsv);
	/**
	 * Parsea una linea de la forma "(r1,g1,b1) to (r2,g2,b2)" (internamente se almacenan como (b,g,r))
	 */
	RangeColor(const string &configLine);
	RangeColor(const string &configLine, const string &id);
	bool inRange(const Scalar &color) const;
	bool inRange(const Mat &wholeSubCell) const;
	string getID() const;
private:
	void init(const string &configLine, const string &id);
	Scalar lowerVal;
	Scalar upperVal;
	string label;
	static stringstream stream;
};

#endif /* RANGECOLOR_H_ */
