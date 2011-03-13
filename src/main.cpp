#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

#include "../lib/ConfigParser.h"
extern void videoRutine(ConfigParser &config);
#include <cv.h>
#include <highgui.h>
using namespace cv;

int main() {
	ConfigParser cp("params.ini");
	videoRutine(cp);
	return 0;
}
