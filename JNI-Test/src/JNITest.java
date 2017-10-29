
public class JNITest {
	
	static {
		System.loadLibrary("jni-test");
		//System.load("/home/luochunbo/eclipse-workspace/JNI-Test/libjni-test.so");
	}
	
	private native void sayHello();
	
	private native void threadTest();
	
	private native void callJavaTest();
	
	
	public void javaTest(int v) {
		
		System.out.println("java,  test for v, v = " + v);
		System.out.println(v);
	}
	
	public int var;
	
	public void testVar(int v) {
		
		System.out.println("in testVar");
		System.out.println("var = " + var + ", v = " + v);
		
		int result = var + v;
		
		System.out.println("result = " + result);
		
		var += v;
		
	}
	
	
	public static void main(String[] args ) {
		//System.out.println("hello world");
		//new JNITest().sayHello();
		//new JNITest().callJavaTest();
		new JNITest().threadTest();
	}

}
