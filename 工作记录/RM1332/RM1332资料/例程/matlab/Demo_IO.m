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

% 引脚编号
Pin = 0;

% 初始化引脚工作模式
% Mode：输入输出模式。0，输入。1，输出。2，开漏
% Pull：上拉下拉电阻。0，无。1，使能内部上拉。2，使能内部下拉
Mode = 1;
Pull = 0;
res = 0;
res = calllib('librockmong', 'IO_InitPin', SerialNumber, Pin, Mode, Pull);
if res ~= 0
    error('Failed to initialize pin.');
end

% 读取引脚状态
PinState = 0;
res = calllib('librockmong', 'IO_ReadPin', SerialNumber, Pin, PinState);
if res ~= 0
    error('Failed to read pin state.');
end
disp(['Pin state: ', num2str(PinState)]);

% 控制引脚输出状态
PinState = 1; % 1 表示输出高电平
res = calllib('librockmong', 'IO_WritePin', SerialNumber, Pin, PinState);
if res ~= 0
    error('Failed to write pin state.');
end

% 释放内存空间
clear SerialNumbers;

% 释放库文件
unloadlibrary('librockmong');
