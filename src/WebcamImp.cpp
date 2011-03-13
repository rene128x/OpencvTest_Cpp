#include "../lib/WebcamImp.h"
#include "../lib/utils.h"

#include <vector>

void videoRutine(ConfigParser &config) {

	bool liveVideo = config.getFlag("camera");

	Mat tablero;
	if (!liveVideo)
		tablero = imread(config.getText("image_name"), 1);

	Mat grayscale(tablero.size(), CV_8UC1);
	Mat blurred(tablero.size(), CV_8UC1);
	Mat threshed(tablero.size(), CV_8UC1);

	Size stdSize = tablero.size();

	Size outputSize(config.getProperty("output_width"),
			config.getProperty("output_height"));

	VideoCapture camera;
	if (liveVideo) {
		int cam = config.getProperty("camera_device");
		camera.open(cam);
		if (!camera.isOpened()) {
			cout << "device " << cam << " is not opened" << endl;
			return;
		}
	}

	vector<RangeColor> ranges;
	string global_colors = config.getText("global_colors");
	stringstream ss(stringstream::in | stringstream::out);
	ss << global_colors << endl;
	string s;
	while (ss >> s)
		ranges.push_back(RangeColor(config.getText(s), s));

	int _delay = liveVideo ? config.getProperty("latency") : 0;
	int rect_thickness = config.getProperty("rect_thickness");

	int b = config.getProperty("rect_B");
	int g = config.getProperty("rect_G");
	int r = config.getProperty("rect_R");
	Scalar rect_color(b, g, r);

	// si es liveVideo, se ejecuta indefinidamente, de lo contrario, una sola vez
	do {
		if (liveVideo)
			camera >> tablero;

		cvtColor(tablero, grayscale, CV_BGR2GRAY);
		GaussianBlur(grayscale, blurred, Size(11, 11), 0);
		threshold(blurred, threshed, 128, 255, THRESH_BINARY);

		keepBiggestBlob(threshed, 255);
		keepBiggestBlob(threshed, 0);

		BoundingBox bb(threshed, 0);
		Rect r = bb.getRect();

		recognizePieces(tablero, r, config, ranges);

		rectangle(tablero, Point(r.x, r.y),
				Point(r.x + r.width, r.y + r.height), rect_color,
				rect_thickness);

		imshow("tablero bottom_left", resizePic(tablero, outputSize));
		//imshow("grayscale bottom_right", resizePic(grayscale, outputSize));
		imshow("threshed top_left", resizePic(threshed, outputSize));
		//imshow("blurred top_right", resizePic(blurred, outputSize));

		if (waitKey(_delay) != -1)
			break;

	} while (liveVideo);

	if (liveVideo)
		camera.release();
}
