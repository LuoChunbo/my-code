#include <jni.h>
#include <stdio.h>
#include "JNITest.h"
#include "pthread.h"

#include "unistd.h"

JavaVM* g_jvm = NULL;
static jobject g_object = NULL;



JNIEXPORT void JNICALL Java_JNITest_sayHello (JNIEnv *env, jobject obj) {

	printf(" ======  \r\n");
	printf(" ====== \r\n");
	printf(" ====== \r\n");
	printf( "Hello World on JNI !\n");
	printf(" ====== \r\n");
}

JNIEXPORT void JNICALL Java_JNITest_callJavaTest(JNIEnv *env, jobject obj) {

	printf(" ========= \r\n\r\n");
	printf(" call Java Test \r\n\r\n");
	printf(" ========= \r\n");

	jclass cls = env->GetObjectClass(obj);
	jmethodID method = env->GetMethodID(cls, "javaTest","(I)V");
	if (method == 0) {
		printf (" cannot find method javaTest ...");
	}

	printf("In C, call java \n ");

	env->CallVoidMethod(obj, method, 55);

	printf("IN c, after Call javaTest \n");




}


void *thread_func(void *ptr){

	JNIEnv *env;
	g_jvm->AttachCurrentThread((void **)&env, NULL);
	jclass cls = env->GetObjectClass(g_object);

	jfieldID field = env->GetFieldID(cls, "var", "I");

	env->SetIntField(g_object, field, 55);

	jmethodID method = env->GetMethodID(cls, "testVar","(I)V");
	env->CallVoidMethod(g_object, method, 2);

	printf(" thread_func exit \r\n");

	g_jvm->DetachCurrentThread();



	return 0;
}


JNIEXPORT void JNICALL Java_JNITest_threadTest(JNIEnv *env, jobject obj) {


	printf(" ========= \r\n\r\n");
	printf(" JNI thread test \r\n\r\n");
	printf(" ========= \r\n");

	pthread_t tid;

	env->GetJavaVM(&g_jvm);
	g_object = env->NewGlobalRef(obj);

	int ret = pthread_create(&tid, NULL, thread_func, NULL);
	if (ret != 0) {
		printf( "pthread create error");
		return ;
	}

	int count = 0;
	while(1) {
		printf(" loop , count = %d \r\n", count);
		count++;
		if (count >=10)
			break;
		sleep(1);
	}

	env->DeleteGlobalRef(obj);

	printf("exit!\r\n");

}



