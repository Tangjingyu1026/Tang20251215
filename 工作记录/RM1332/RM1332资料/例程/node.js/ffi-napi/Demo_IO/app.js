const ffi = require('ffi-napi');

// 创建 ffi-napi 库实例
const rockmongLib = ffi.Library('librockmong', {
  'UsbDevice_Scan': ['int', ['pointer']],
  'IO_InitPin': ['int', ['int', 'int', 'int', 'int']],
  'IO_ReadPin': ['int', ['int', 'int', 'pointer']],
  'IO_WritePin': ['int', ['int', 'int', 'int']]
});

// 创建一个缓冲区来存储返回的 SerialNumbers
const SerialNumbers = Buffer.alloc(16 * 4); // 创建缓冲区来存储 SerialNumbers

// 调用 UsbDevice_Scan 函数
const ret = rockmongLib.UsbDevice_Scan(SerialNumbers);

if (ret < 0) {
  console.log(`Scan error: ${ret}`);
  process.exit(1);
} else if (ret === 0) {
  console.log('No device');
  process.exit(0);
} else {
  const serialNumbers = [];
  for (let i = 0; i < ret; i++) {
    const serialNumber = SerialNumbers.readInt32LE(i * 4);
    serialNumbers.push(serialNumber);
    console.log(`Dev${i} SN: ${serialNumber}`);
  }
}

// P0初始化为输出模式
const sn = SerialNumbers.readInt32LE(0 * 4);
const retInit = rockmongLib.IO_InitPin(sn, 0, 1, 0);
if (retInit < 0) {
  console.log(`Error: ${retInit}`);
  process.exit(1);
}

// P0输出低电平
const retWriteLow = rockmongLib.IO_WritePin(sn, 0, 0);
if (retWriteLow < 0) {
  console.log(`Error: ${retWriteLow}`);
  process.exit(1);
}

// P0输出高电平
const retWriteHigh = rockmongLib.IO_WritePin(sn, 0, 1);
if (retWriteHigh < 0) {
  console.log(`Error: ${retWriteHigh}`);
  process.exit(1);
}

// P0初始化为输入模式
const retInitInput = rockmongLib.IO_InitPin(sn, 0, 0, 0);
if (retInitInput < 0) {
  console.log(`Error: ${retInitInput}`);
  process.exit(1);
}

// 读取P0状态
const PinStateBuffer = Buffer.alloc(4);
const retRead = rockmongLib.IO_ReadPin(sn, 0, PinStateBuffer);
if (retRead < 0) {
  console.log(`Error: ${retRead}`);
  process.exit(1);
}

const PinState = PinStateBuffer.readInt32LE();
console.log(`Read pin: ${PinState}`);
