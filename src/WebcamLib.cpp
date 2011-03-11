#include "../lib/WebcamLib.h"
#include "../lib/WebcamImp.h"

JNIEXPORT void JNICALL Java_WebcamLib_videoRutine(JNIEnv *env, jobject me,
		jint cam) {
	ConfigParser config = ConfigParser("params.ini");
	if (cam >= 0)
		config.setProperty("camera_device", cam);
	videoRutine(config);
}
