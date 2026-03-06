

Imports System.Runtime.InteropServices

Module usb_device

    Declare Function UsbDevice_Scan Lib "librockmong.dll" (<Out()> ByVal pDevHandle As UInt32()) As Int32

End Module
