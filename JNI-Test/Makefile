JAVA_HOME := /usr/lib/jvm/java-1.8.0-openjdk-amd64



help:
	@echo 'Makefile for JNI Example                                                '
	@echo '                                                                        '
	@echo 'Usage:                                                                  '
	@echo '   make jni-compile                 compile native C code               '
	@echo '   make java-compile                compile Java code                   '
	@echo '   make clean                       remove generated shared library     '
	@echo '   make run                         run JNI Example                     '
	@echo '                                                                        '
	@echo "Note: To work from Java IDE you'll probably need only jni-compile target"

jni-compile: libjni-test.so

libjni-test.so: jni/TestNative.cpp include/JNITest.h
	gcc -O3 -fPIC -shared -I include -I $(JAVA_HOME)/include/ \
	-I $(JAVA_HOME)/include/linux/ \
	jni/TestNative.cpp \
	-o libjni-test.so

java-compile: src/%.class

src/%.class:
	javac src/*.java

include/JNITest.h: src/JNITest.class
	javah -cp src -d include JNITest
	

clean:
	[ ! -f libjni-test.so ] || rm libjni-test.so
	[ ! -f include/*.h ] || rm include/*
	[ ! -f src/*.class ] || rm src/*.class

run: java-compile jni-compile
	java -Djava.library.path=./ -cp src/ JNITest

.PHONY: clean java-compile jni-compile run help
