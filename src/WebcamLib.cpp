
#include "../lib/WebcamLib.h"
#include "../lib/WebcamImp.h"

JNIEXPORT void JNICALL Java_WebcamLib_videoRutine(JNIEnv *env, jobject me,
		jint cam) {
	videoRutine(cam);
}
