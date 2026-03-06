package com.rockmong.rockmong;

import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Pointer;

public interface MISC extends Library {

    MISC INSTANTCE = (MISC) Native.loadLibrary("rockmong", MISC.class);

    int MISC_GetFwVersion(int SerialNumber, Pointer Ver);
    int MISC_GetModel(int SerialNumber, Pointer Ver);
}
