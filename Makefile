# 指定編譯器與編譯選項
CC = gcc

#-I 到指定目錄找header
CFLAGS = -Wall -Iinclude -g

# 連結選項（加入 wiringOP lgpiod mqtt同步 函式庫）
LDFLAGS = -lwiringPi -lwiringPiDev -lpthread -lm -lcrypt -lrt -lgpiod -lpaho-mqtt3c -lcjson

# 設定目錄
SRC_DIR = src
OBJ_DIR = obj
TARGET  = app

# 取得 src 目錄下所有 .c 檔案
SRCS    := $(wildcard $(SRC_DIR)/*.c)
# 將 .c 檔案轉換成 .o 檔案，放到 obj 資料夾中
OBJS    := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# 告知 all 和 clean是個偽目標
.PHONY: all clean
 
# 預設目標
all: $(TARGET)

# 連結物件檔案成最終執行檔
$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

# 規則：編譯 .c 檔案到 .o 檔案
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# 確保 obj 目錄存在
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# 清除編譯產物
clean:
	rm -rf $(OBJ_DIR) $(TARGET)
