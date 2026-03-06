# 设置cmake的最低版本
cmake_minimum_required(VERSION 3.0.0)

# 设置工程名称
project(Demo_PWM)

# 设置源文件路径
set(SRC_DIRs ../source)

# 添加源文件
foreach(SRC_DIR ${SRC_DIRs})
	include_directories(${SRC_DIR})
	aux_source_directory(${SRC_DIR} SRCs)
endforeach(SRC_DIR)

# 生成文件
add_executable(${PROJECT_NAME} ${SRCs})

# 链接库文件
target_link_libraries(${PROJECT_NAME} usb-1.0 rockmong)

