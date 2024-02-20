package me.bitefoo.androidencryptor;

public class StringEncoder {

    static{
        System.loadLibrary("androidencryptor");
    }

    public static native void postDeviceInfo(String deviceInfo);

}
