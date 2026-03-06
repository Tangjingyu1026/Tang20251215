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
disp(['SerialNumber: ', num2str(SerialNumber)]);

% 同时控制16个IO
ioNum = 1;

% 创建初始化结构体
InitStructTx = struct('Pin', uint8(0), 'Mode', uint8(0), 'Pull', uint8(1));
InitStructRx = struct('Ret', uint8(0));

% 创建结构体指针
numStructs = 10;
cInitStructTx = cell(1, numStructs);
for i = 1:numStructs
    cInitStructTx{i} = libpointer('IO_InitStruct_TxPtr', struct('Pin', uint8(0), 'Mode', uint8(0), 'Pull', uint8(0)));
end
cInitStructRx = libpointer('IO_InitStruct_RxPtr', InitStructRx);

% 调用初始化函数
res = calllib('librockmong', 'IO_InitMultiPin', SerialNumber, cInitStructTx, cInitStructRx, ioNum);
disp(['res: ', num2str(res)]);
if res ~= 0
    error('Failed to init pin.');
end

% 释放内存空间
clear SerialNumbers;
clear cInitStructTx;
clear cInitStructRx;

% 释放库文件
unloadlibrary('librockmong');
