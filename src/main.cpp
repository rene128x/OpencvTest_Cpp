#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

#include "../lib/ConfigParser.h"
extern void videoRutine(ConfigParser &config);

int main() {
	ConfigParser cp("params.ini");
	videoRutine(cp);
	return 0;
}
