/*
 * RangeColor.cpp
 *
 *  Created on: 11-03-2011
 *      Author: rene128x
 */
#include "../lib/RangeColor.h"

stringstream RangeColor::stream(stringstream::in | stringstream::out);

RangeColor::RangeColor(const Scalar &min_hsv, const Scalar &max_hsv) {
	lowerVal = min_hsv;
	upperVal = max_hsv;
}
RangeColor::RangeColor(const string &configLine) {
	init(configLine, "n/a");
}
RangeColor::RangeColor(const string &configLine, const string &id) {
	init(configLine, id);
}

// TODO implementar
bool RangeColor::inRange(const Scalar &color) const {
	for (unsigned i = 0; i < 3; i++)
		if (lowerVal[i] > color[i] || color[i] > upperVal[i])
			return false;
	return true;
}

// TODO temporalmente, se considera en rango si al menos la mitad de los pixeles estan en rango
bool RangeColor::inRange(const Mat &whole) const {
	unsigned width = whole.size().width;
	unsigned height = whole.size().height;
	unsigned total = width * height;
	unsigned cuenta = 0;

	vector<Mat> canales;
	split(whole, canales);
	for (unsigned x = 0; x < width; x++)
		for (unsigned y = 0; y < height; y++) {
			Point p(x, y);
			Scalar sp(canales[0].at<uchar> (p), canales[1].at<uchar> (p),
					canales[2].at<uchar> (p));
			if (inRange(sp))
				cuenta++;
		}
	return cuenta >= total / 2;
}
string RangeColor::getID() const {
	return label;
}

void RangeColor::init(const string &configLine, const string &id) {
	label = id;
	string temp = configLine;
	unsigned n = temp.length();
	for (unsigned i = 0; i < n; i++) {
		char c = temp[i];
		switch (c) {
		case 't':
		case 'o':
		case '(':
		case ')':
		case ',':
			temp[i] = ' ';
		}
	}

	stream.clear();
	stream << temp << endl;
	int six[6];
	for (int i = 0; i < 6; i++)
		stream >> six[i];

	lowerVal = Scalar(six[2], six[1], six[0]);
	upperVal = Scalar(six[5], six[4], six[3]);
}
