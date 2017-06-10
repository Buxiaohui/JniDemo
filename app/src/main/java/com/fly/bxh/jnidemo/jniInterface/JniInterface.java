package com.fly.bxh.jnidemo.jniInterface;

import com.fly.bxh.jnidemo.bean.JNIBean;

/**
 * Created by bxh on 6/10/17.
 */

public class JniInterface {
    private static JniInterface instance;

    // Used to load the 'native-mine-lib' library on application startup.
    static {
        //名字和CMakeLists中add_library中定义的对应，与cpp文件名字无关
        System.loadLibrary("native_mine_lib");
    }

    public JniInterface() {
    }

    public static JniInterface getInstance() {
        if (instance == null) {
            instance = new JniInterface();
        }
        return instance;
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public static native String stringFromJNI();

    public static native String stringFromMineJNI();

    public static native int addFromMineJNI(int x, int y);

    public static native int[] intArrayFromMineJNI(int[] intArray);

    public static native void transferData(JNIBean bean);
}
