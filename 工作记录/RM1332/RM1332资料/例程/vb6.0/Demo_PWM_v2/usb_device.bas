Attribute VB_Name = "usb_device"

Declare Function UsbDevice_Scan Lib "librockmong.dll" (ByVal SerialNumbers As Long) As Long

