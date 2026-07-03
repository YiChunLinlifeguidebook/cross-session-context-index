CC      = gcc
CXX     = g++
CFLAGS  = -Wall -Wextra -std=c99
CXXFLAGS= -Wall -Wextra -std=c++14

CONFIG  = config/weights.conf
DATA    = records.dat

.PHONY: all build test clean install help

all: build

build: bin/weight bin/index

bin:
	mkdir -p bin

bin/weight: src/weight.c | bin
	$(CC) $(CFLAGS) -o bin/weight src/weight.c

bin/index: src/index.cpp | bin
	$(CXX) $(CXXFLAGS) -o bin/index src/index.cpp

test: build
	@echo "=== 寫入測試記錄 ==="
	./bin/weight $(CONFIG) $(DATA) JIU_C  "系統核心架構測試"
	./bin/weight $(CONFIG) $(DATA) JIU_ES "Termux測試環境"
	./bin/weight $(CONFIG) $(DATA) JIU_W  "商業計畫架構"
	./bin/weight $(CONFIG) $(DATA) JIU_C  "AI生成式模型推理"
	./bin/weight $(CONFIG) $(DATA) JIU_NE "機械靈魂生活指南書目標"
	@echo ""
	@echo "=== 讀取索引 ==="
	./bin/index $(DATA)
	@echo ""
	@echo "=== JSON 輸出 ==="
	./bin/index $(DATA) --json

install: build
	@echo "安裝到 Termux PATH..."
	cp bin/weight $(PREFIX)/bin/npi-weight 2>/dev/null || cp bin/weight /usr/local/bin/npi-weight
	cp bin/index  $(PREFIX)/bin/npi-index  2>/dev/null || cp bin/index  /usr/local/bin/npi-index
	@echo "✅ 安裝完成，可直接使用 npi-weight 和 npi-index"

clean:
	rm -rf bin $(DATA)

help:
	@echo "Nine Palace Index - 指令說明"
	@echo "────────────────────────────────────"
	@echo "  make build    編譯 weight 與 index 程式"
	@echo "  make test     執行完整測試流程"
	@echo "  make install  安裝到系統 PATH (Termux 適用)"
	@echo "  make clean    清除編譯產物與記錄資料"
	@echo "  make help     顯示此說明"
	@echo ""
	@echo "手動使用方式："
	@echo "  手動分類: ./bin/weight config/weights.conf records.dat <宮位> <內容>"
	@echo "  自動分類: ./bin/weight config/weights.conf records.dat <內容>"
	@echo "  查看索引: ./bin/index records.dat"
	@echo "  JSON輸出: ./bin/index records.dat --json"
