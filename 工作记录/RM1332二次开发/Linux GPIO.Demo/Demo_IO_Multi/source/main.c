/*
#include "stdio.h"
#include "usb_device.h"
#include "io.h"

#define IO_NUMBER	(32)

int main(void)
{
	int ret = 0, i;
	int SerialNumbers[16];
	int PinState = 0;
	
	ret = UsbDevice_Scan(SerialNumbers);
	if (ret < 0)
	{
		printf("Scan error: %d\n", ret);
		return ret;
	}
	else if (ret == 0)
	{
		printf("No device\n");
		return ret;
	}
	else
	{
		for (i = 0; i < ret; i++)
		{
			printf("Dev%d SN: %d\n", i, SerialNumbers[i]);
		}
	}
	
	//P0~P32初始化为输出模式
	IO_InitStruct_Tx_t initStruct_Tx[IO_NUMBER];
	IO_InitStruct_Rx_t initStruct_Rx[IO_NUMBER];
	for (i = 0; i < IO_NUMBER; i++)
	{
		initStruct_Tx[i].Pin = i;
		initStruct_Tx[i].Mode = 1;
		initStruct_Tx[i].Pull = 0;
	}
	ret = IO_InitMultiPin(SerialNumbers[0], initStruct_Tx, initStruct_Rx, IO_NUMBER);
	if (ret < 0)
	{
		printf("Error: %d\n", ret);
		return ret;
	}

	//P0输出低电平
	IO_WriteStruct_Tx_t writeStruct_Tx[IO_NUMBER];
	IO_WriteStruct_Rx_t writeStruct_Rx[IO_NUMBER];
	for (i = 0; i < IO_NUMBER; i++)
	{
		writeStruct_Tx[i].Pin = i;
		writeStruct_Tx[i].PinState = 0;
	}
	ret = IO_WriteMultiPin(SerialNumbers[0], writeStruct_Tx, writeStruct_Rx, IO_NUMBER);
	if (ret < 0)
	{
		printf("Error: %d\n", ret);
		return ret;
	}

	//P0输出高电平
	for (i = 0; i < IO_NUMBER; i++)
	{
		writeStruct_Tx[i].Pin = i;
		writeStruct_Tx[i].PinState = 1;
	}
	ret = IO_WriteMultiPin(SerialNumbers[0], writeStruct_Tx, writeStruct_Rx, IO_NUMBER);
	if (ret < 0)
	{
		printf("Error: %d\n", ret);
		return ret;
	}

	//P0初始化为输入模式
	for (i = 0; i < IO_NUMBER; i++)
	{
		initStruct_Tx[i].Pin = i;
		initStruct_Tx[i].Mode = 0;
		initStruct_Tx[i].Pull = 1;//上拉
	}
	ret = IO_InitMultiPin(SerialNumbers[0], initStruct_Tx, initStruct_Rx, IO_NUMBER);
	if (ret < 0)
	{
		printf("Error: %d\n", ret);
		return ret;
	}
	if (ret < 0)
	{
		printf("Error: %d\n", ret);
		return ret;
	}

	//读取P0状态
	IO_ReadStruct_Tx_t readStruct_Tx[IO_NUMBER];
	IO_ReadStruct_Rx_t readStruct_Rx[IO_NUMBER];
	for (i = 0; i < IO_NUMBER; i++)
	{
		readStruct_Tx[i].Pin = i;
	}
	ret = IO_ReadMultiPin(SerialNumbers[0], readStruct_Tx, readStruct_Rx, IO_NUMBER);
	if (ret < 0)
	{
		printf("Error: %d\n", ret);
		return ret;
	}
	for (i = 0; i < IO_NUMBER; i++)
	{
		printf("Read pin%d: %d\n", i, readStruct_Rx[i].PinState);
	}
	
}
	*/

#include <stdio.h>
#include <stdlib.h>   // 为了使用 atoi 等函数
#include <string.h>   // 为了字符串比较
#include "usb_device.h"
#include "io.h"

#define MAX_PINS 32   // 引脚总数

// 打印菜单
void print_menu() {
    printf("\n========== GPIO 控制菜单 ==========\n");
    printf("1. 初始化单个引脚\n");
    printf("2. 写入单个引脚（输出电平）\n");
    printf("3. 读取单个引脚\n");
    printf("4. 批量初始化多个引脚\n");
    printf("5. 批量写入多个引脚\n");
    printf("6. 批量读取多个引脚\n");
    printf("7. 显示当前所有引脚状态（软件缓存）\n");
    printf("0. 退出\n");
    printf("请选择操作：");
}

// 将引脚号字符串（如"0,1,3-5"）解析为引脚数组，返回引脚个数
int parse_pins(const char *input, int pins[], int max_pins) {
    int count = 0;
    char *token;
    char *str = strdup(input); // 复制字符串，因为strtok会修改原串
    if (!str) return 0;

    token = strtok(str, ",");
    while (token != NULL && count < max_pins) {
        // 检查是否有范围（如3-5）
        char *dash = strchr(token, '-');
        if (dash) {
            int start = atoi(token);
            int end = atoi(dash + 1);
            if (start < 0 || start >= max_pins || end < 0 || end >= max_pins || start > end) {
                printf("错误：无效的范围 %s\n", token);
                free(str);
                return -1;
            }
            for (int i = start; i <= end && count < max_pins; i++) {
                pins[count++] = i;
            }
        } else {
            int pin = atoi(token);
            if (pin < 0 || pin >= max_pins) {
                printf("错误：无效的引脚号 %d\n", pin);
                free(str);
                return -1;
            }
            pins[count++] = pin;
        }
        token = strtok(NULL, ",");
    }
    free(str);
    return count;
}

// 将引脚模式字符串转换为枚举值
int parse_mode(const char *str) {
    if (strcmp(str, "输入") == 0 || strcmp(str, "in") == 0) return IO_MODE_INPUT;
    if (strcmp(str, "输出") == 0 || strcmp(str, "out") == 0) return IO_MODE_OUTPUT;
    if (strcmp(str, "开漏") == 0 || strcmp(str, "od") == 0) return IO_MODE_OPEN_DRAIN;
    return -1;
}

// 将上下拉字符串转换为枚举值
int parse_pull(const char *str) {
    if (strcmp(str, "无") == 0 || strcmp(str, "none") == 0 || strcmp(str, "浮空") == 0) return IO_NOPULL;
    if (strcmp(str, "上拉") == 0 || strcmp(str, "up") == 0) return IO_PULLUP;
    if (strcmp(str, "下拉") == 0 || strcmp(str, "down") == 0) return IO_PULLDOWN;
    return -1;
}

// 将电平字符串转换为值
int parse_state(const char *str) {
    if (strcmp(str, "低") == 0 || strcmp(str, "low") == 0 || strcmp(str, "0") == 0) return IO_STATE_LOW;
    if (strcmp(str, "高") == 0 || strcmp(str, "high") == 0 || strcmp(str, "1") == 0) return IO_STATE_HIGH;
    return -1;
}

int main(void) {
    int ret, i;
    int serial_numbers[16];        // 存放扫描到的设备序号
    int device_count;
    int selected_device = -1;       // 当前选择的设备索引

    // 软件缓存：保存每个引脚当前的模式、上下拉和电平（用于显示，实际以硬件为准）
    // 注意：缓存仅用于展示，操作时仍直接调用硬件函数
    int cache_mode[MAX_PINS] = {0};
    int cache_pull[MAX_PINS] = {0};
    int cache_state[MAX_PINS] = {0}; // 仅对输出模式有意义

    // 扫描USB设备
    ret = UsbDevice_Scan(serial_numbers);
    if (ret < 0) {
        printf("扫描设备失败，错误码：%d\n", ret);
        return ret;
    } else if (ret == 0) {
        printf("未检测到任何USB设备，请连接设备后重试。\n");
        return 0;
    } else {
        printf("检测到 %d 个设备：\n", ret);
        for (i = 0; i < ret; i++) {
            printf("  设备 %d: 序号 %d\n", i, serial_numbers[i]);
        }
        // 默认选择第一个设备
        selected_device = 0;
        printf("默认选择设备 0（序号 %d）进行操作。\n", serial_numbers[selected_device]);
    }

    // 交互主循环
    int choice;
    char input[256];
    while (1) {
        print_menu();
        fgets(input, sizeof(input), stdin);
        choice = atoi(input);

        switch (choice) {
            case 0:
                printf("程序退出。\n");
                return 0;

            case 1: { // 初始化单个引脚
                int pin, mode, pull;
                printf("请输入引脚号 (0~%d)：", MAX_PINS-1);
                fgets(input, sizeof(input), stdin);
                pin = atoi(input);
                if (pin < 0 || pin >= MAX_PINS) {
                    printf("错误：引脚号超出范围。\n");
                    break;
                }
                printf("请输入模式 (输入/输出/开漏，或 in/out/od)：");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0; // 去掉换行符
                mode = parse_mode(input);
                if (mode < 0) {
                    printf("错误：无效的模式。\n");
                    break;
                }
                printf("请输入上下拉 (无/上拉/下拉，或 none/up/down)：");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0;
                pull = parse_pull(input);
                if (pull < 0) {
                    printf("错误：无效的上下拉。\n");
                    break;
                }

                // 调用单引脚初始化函数
                ret = IO_InitPin(serial_numbers[selected_device], pin, mode, pull);
                if (ret < 0) {
                    printf("初始化引脚 %d 失败，错误码：%d\n", pin, ret);
                } else {
                    printf("引脚 %d 初始化成功。\n", pin);
                    // 更新缓存
                    cache_mode[pin] = mode;
                    cache_pull[pin] = pull;
                    // 如果是输入模式，缓存电平未知，可标记为 -1 或保持原值
                    if (mode == IO_MODE_INPUT) {
                        cache_state[pin] = -1; // 表示未知
                    }
                }
                break;
            }

            case 2: { // 写入单个引脚
                int pin, state;
                printf("请输入引脚号 (0~%d)：", MAX_PINS-1);
                fgets(input, sizeof(input), stdin);
                pin = atoi(input);
                if (pin < 0 || pin >= MAX_PINS) {
                    printf("错误：引脚号超出范围。\n");
                    break;
                }
                printf("请输入电平 (低/高，或 low/high，或 0/1)：");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0;
                state = parse_state(input);
                if (state < 0) {
                    printf("错误：无效的电平。\n");
                    break;
                }

                ret = IO_WritePin(serial_numbers[selected_device], pin, state);
                if (ret < 0) {
                    printf("写入引脚 %d 失败，错误码：%d\n", pin, ret);
                } else {
                    printf("引脚 %d 已设置为 %s。\n", pin, state == IO_STATE_LOW ? "低电平" : "高电平");
                    // 更新缓存（注意：如果引脚当前不是输出模式，写入可能无效，但缓存仍记录）
                    cache_state[pin] = state;
                }
                break;
            }

            case 3: { // 读取单个引脚
                int pin, state;
                printf("请输入引脚号 (0~%d)：", MAX_PINS-1);
                fgets(input, sizeof(input), stdin);
                pin = atoi(input);
                if (pin < 0 || pin >= MAX_PINS) {
                    printf("错误：引脚号超出范围。\n");
                    break;
                }

                ret = IO_ReadPin(serial_numbers[selected_device], pin, &state);
                if (ret < 0) {
                    printf("读取引脚 %d 失败，错误码：%d\n", pin, ret);
                } else {
                    printf("引脚 %d 当前电平：%s\n", pin, state == IO_STATE_LOW ? "低电平" : "高电平");
                    // 更新缓存
                    cache_state[pin] = state;
                }
                break;
            }

            case 4: { // 批量初始化多个引脚
                int pins[MAX_PINS];
                int count;
                printf("请输入引脚列表（支持逗号分隔和范围，例如 0,1,3-5）：");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0;
                count = parse_pins(input, pins, MAX_PINS);
                if (count <= 0) {
                    printf("错误：无效的引脚列表。\n");
                    break;
                }

                // 获取统一的模式和上下拉
                int mode, pull;
                printf("请输入模式 (输入/输出/开漏，或 in/out/od)：");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0;
                mode = parse_mode(input);
                if (mode < 0) {
                    printf("错误：无效的模式。\n");
                    break;
                }
                printf("请输入上下拉 (无/上拉/下拉，或 none/up/down)：");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0;
                pull = parse_pull(input);
                if (pull < 0) {
                    printf("错误：无效的上下拉。\n");
                    break;
                }

                // 准备批量结构体
                IO_InitStruct_Tx_t tx[count];
                IO_InitStruct_Rx_t rx[count];
                for (i = 0; i < count; i++) {
                    tx[i].Pin = pins[i];
                    tx[i].Mode = mode;
                    tx[i].Pull = pull;
                }

                ret = IO_InitMultiPin(serial_numbers[selected_device], tx, rx, count);
                if (ret < 0) {
                    printf("批量初始化失败，整体错误码：%d\n", ret);
                } else {
                    printf("批量初始化完成，各引脚结果如下：\n");
                    for (i = 0; i < count; i++) {
                        if (rx[i].Ret == 0) {
                            printf("  引脚 %d 成功\n", pins[i]);
                            cache_mode[pins[i]] = mode;
                            cache_pull[pins[i]] = pull;
                            if (mode == IO_MODE_INPUT) cache_state[pins[i]] = -1;
                        } else {
                            printf("  引脚 %d 失败，错误码：%d\n", pins[i], rx[i].Ret);
                        }
                    }
                }
                break;
            }

            case 5: { // 批量写入多个引脚
                int pins[MAX_PINS];
                int count;
                printf("请输入引脚列表（支持逗号分隔和范围，例如 0,1,3-5）：");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0;
                count = parse_pins(input, pins, MAX_PINS);
                if (count <= 0) {
                    printf("错误：无效的引脚列表。\n");
                    break;
                }

                int state;
                printf("请输入电平 (低/高，或 low/high，或 0/1)：");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0;
                state = parse_state(input);
                if (state < 0) {
                    printf("错误：无效的电平。\n");
                    break;
                }

                IO_WriteStruct_Tx_t tx[count];
                IO_WriteStruct_Rx_t rx[count];
                for (i = 0; i < count; i++) {
                    tx[i].Pin = pins[i];
                    tx[i].PinState = state;
                }

                ret = IO_WriteMultiPin(serial_numbers[selected_device], tx, rx, count);
                if (ret < 0) {
                    printf("批量写入失败，整体错误码：%d\n", ret);
                } else {
                    printf("批量写入完成，各引脚结果如下：\n");
                    for (i = 0; i < count; i++) {
                        if (rx[i].Ret == 0) {
                            printf("  引脚 %d 成功\n", pins[i]);
                            cache_state[pins[i]] = state;
                        } else {
                            printf("  引脚 %d 失败，错误码：%d\n", pins[i], rx[i].Ret);
                        }
                    }
                }
                break;
            }

            case 6: { // 批量读取多个引脚
                int pins[MAX_PINS];
                int count;
                printf("请输入引脚列表（支持逗号分隔和范围，例如 0,1,3-5）：");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0;
                count = parse_pins(input, pins, MAX_PINS);
                if (count <= 0) {
                    printf("错误：无效的引脚列表。\n");
                    break;
                }

                IO_ReadStruct_Tx_t tx[count];
                IO_ReadStruct_Rx_t rx[count];
                for (i = 0; i < count; i++) {
                    tx[i].Pin = pins[i];
                }

                ret = IO_ReadMultiPin(serial_numbers[selected_device], tx, rx, count);
                if (ret < 0) {
                    printf("批量读取失败，整体错误码：%d\n", ret);
                } else {
                    printf("批量读取结果：\n");
                    for (i = 0; i < count; i++) {
                        if (rx[i].Ret == 0) {
                            printf("  引脚 %d：%s\n", pins[i], rx[i].PinState == IO_STATE_LOW ? "低电平" : "高电平");
                            cache_state[pins[i]] = rx[i].PinState;
                        } else {
                            printf("  引脚 %d 读取失败，错误码：%d\n", pins[i], rx[i].Ret);
                        }
                    }
                }
                break;
            }

            case 7: { // 显示缓存状态
                printf("\n当前引脚状态缓存（实际以硬件为准）：\n");
                printf("引脚\t模式\t上下拉\t电平\n");
                for (i = 0; i < MAX_PINS; i++) {
                    const char *mode_str, *pull_str, *state_str;
                    switch (cache_mode[i]) {
                        case IO_MODE_INPUT: mode_str = "输入"; break;
                        case IO_MODE_OUTPUT: mode_str = "输出"; break;
                        case IO_MODE_OPEN_DRAIN: mode_str = "开漏"; break;
                        default: mode_str = "未知";
                    }
                    switch (cache_pull[i]) {
                        case IO_NOPULL: pull_str = "无"; break;
                        case IO_PULLUP: pull_str = "上拉"; break;
                        case IO_PULLDOWN: pull_str = "下拉"; break;
                        default: pull_str = "未知";
                    }
                    if (cache_state[i] == IO_STATE_LOW) state_str = "低";
                    else if (cache_state[i] == IO_STATE_HIGH) state_str = "高";
                    else state_str = "未知";
                    printf("P%2d\t%s\t%s\t%s\n", i, mode_str, pull_str, state_str);
                }
                break;
            }

            default:
                printf("无效选项，请重新输入。\n");
                break;
        }
    }

    return 0;
}
