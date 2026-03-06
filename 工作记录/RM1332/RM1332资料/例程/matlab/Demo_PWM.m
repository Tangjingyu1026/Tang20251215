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

res = 0;

% 设备序号
SerialNumber = SerialNumbers.Value(1);

% Channel：通道0
Channel = 0;

% 初始PWM0
% Frequency：频率/Hz。1KHz
% Duty：占空比/千分比。50%
% Phase：相位/千分比。0%
% Polarity：波形极性.
Frequency = 1000;
Duty = 500;
Phase = 0;
Polarity = 0;
res = calllib('librockmong', 'PWM_Init', SerialNumber, Channel, Frequency, Duty, Phase, Polarity);
if res ~= 0
    error('Failed to initialize pwm.');
end

% PWM0开始输出
% RunTimeUs：运行时间/us。0则永久
RunTimeUs = 0;
res = calllib('librockmong', 'PWM_Start', SerialNumber, Channel, RunTimeUs);
if res ~= 0
    error('Failed to start pwm.');
end

% PWM0停止输出
res = calllib('librockmong', 'PWM_Stop', SerialNumber, Channel);
if res ~= 0
    error('Failed to stop pwm.');
end

% 释放内存空间
clear SerialNumbers;

% 释放库文件
unloadlibrary('librockmong');
