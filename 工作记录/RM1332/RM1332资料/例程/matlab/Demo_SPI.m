% 加载 DLL 文件和头文件
loadlibrary('rockmongSDK\libs\windows\x86\librockmong.dll', 'rockmongSDK\matlab\rockmong.h');

% 创建输入参数和输出参数
SerialNumbers = libpointer('int32Ptr', zeros(1, 10)); % 申请一段连续的内存空间，用于存放设备序列号
numDevices = 0; % 初始化设备数量为 0

% 调用 DLL 中的函数
numDevices = calllib('librockmong', 'UsbDevice_Scan', SerialNumbers);

% 显示结果
if numDevices > 0
    disp(['Found ', num2str(numDevices), ' devices:']);
    disp(SerialNumbers.Value(1:numDevices));
elseif numDevices == 0
    disp('No USB devices found.');
else
    error('Failed to scan USB devices.');
end

% 设备序号
SerialNumber = SerialNumbers.Value(1);

% SPI通道编号
SPI_Ch = 0;

% 初始化引脚工作模式
% Mode：模式。0，从机。1，主机
Mode = 1;
CPOL = 0;
CPHA = 0;
NSS = 0;
BaudRate = 0;
res = 0;
res = calllib('librockmong', 'SPI_Init', SerialNumber, SPI_Ch, Mode, CPOL, CPHA, NSS, BaudRate);
if res ~= 0
    error('Failed to initialize SPI.');
end

% 写数据
writeBuf = libpointer('int8Ptr', zeros(1, 10));
writeLen = 1;
res = calllib('librockmong', 'SPI_WriteBytes', SerialNumber, SPI_Ch, writeBuf, writeLen);
if res ~= 0
    error('Failed to write data.');
end

% 读数据
readBuf = libpointer('int8Ptr', zeros(1, 10));
readLen = 1;
res = calllib('librockmong', 'SPI_ReadBytes', SerialNumber, SPI_Ch, readBuf, readLen);
if res ~= 0
    error('Failed to read data.');
end
disp(['Data: ', num2str(readBuf.Value(1))]);

% 写读数据
writeBuf = libpointer('int8Ptr', zeros(1, 10));
writeLen = 1;
readBuf = libpointer('int8Ptr', zeros(1, 10));
readLen = 1;
res = calllib('librockmong', 'SPI_WriteReadBytes', SerialNumber, SPI_Ch, writeBuf, writeLen, readBuf, readLen);
if res ~= 0
    error('Failed to write read data.');
end
disp(['Data: ', num2str(readBuf.Value(1))]);

% 释放内存空间
clear SerialNumbers;

% 释放库文件
unloadlibrary('librockmong');
