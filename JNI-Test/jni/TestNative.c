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

	jclass cls = (*env)->GetObjectClass(env, obj);
	jmethodID method = (*env)->GetMethodID(env, cls, "javaTest","(I)V");
	if (method == 0) {
		printf (" cannot find method javaTest ...");
	}

	printf("In C, call java \n ");
	//sleep(5);

	(*env)->CallVoidMethod(env, obj, method, 55);

	printf("IN c, after Call javaTest \n");




}


void *thread_func(void *ptr){

	JNIEnv *env;
	//g_jvm->AttachCurrentThread(g_jvm, (void **)&env, NULL);
	(*g_jvm)->AttachCurrentThread(g_jvm, (void **)&env, NULL);
	jclass cls = (*env)->GetObjectClass(env, g_object);

	jfieldID field = (*env)->GetFieldID(env, cls, "var", "I");

	(*env)->SetIntField(env, g_object, field, 55);

	jmethodID method = (*env)->GetMethodID(env, cls, "testVar","(I)V");
	(*env)->CallVoidMethod(env, g_object, method, 2);

	printf(" thread_func exit \r\n");

	(*g_jvm)->DetachCurrentThread(g_jvm);

	//（*g_jvm)->DetachCurrentThread();





	return 0;
}


JNIEXPORT void JNICALL Java_JNITest_threadTest(JNIEnv *env, jobject obj) {


	printf(" ========= \r\n\r\n");
	printf(" JNI thread test \r\n\r\n");
	printf(" ========= \r\n");

	pthread_t tid;

	(*env)->GetJavaVM(env, &g_jvm);
	g_object = (*env)->NewGlobalRef(env, obj);

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

	(*env)->DeleteGlobalRef(env, obj);

	printf("exit!\r\n");

	//sleep(2);

}



