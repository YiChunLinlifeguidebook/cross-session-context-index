# Changelog

## v0.3.0

- 修復 `src/index.cpp` 缺少 `#include <cstdint>` 導致 Termux 編譯失敗的問題
- 清除根目錄殘留的舊版草稿檔案（`weight.c`、`test.c`、`t.c`）
- 大幅擴充 `config/weights.conf`：新增完整九宮覆蓋、AI 專項關鍵字、機械靈魂/生活指南書關鍵字
- 新增 `Makefile` 的 `install` target 與 `help` target，方便 Termux 一鍵安裝
- 完善 `build.sh`、`test.sh` 腳本說明輸出

## v0.2.0

- 關鍵字權重改為外部設定檔驅動（`config/weights.conf`),不用改程式碼即可自訂分類邏輯
- 記錄陣列改為動態配置(`realloc`),移除原本 `MAX_RECORDS=100` 的固定上限
- 新增累加式讀寫:執行 `weight` 會先讀入既有 `records.dat` 再新增,不會覆蓋舊資料
- `index` 新增分類篩選查詢功能(`./bin/index records.dat <分類>`)
- `cat` 欄位長度由 10 擴充為 32 字元,容納更長的分類名稱
- 修正編譯警告(`snprintf` 字串截斷警告)
- CLI 化:`weight` 與 `index` 皆改為接收命令列參數,不再只能跑寫死的示範資料

## v0.1.0

- Added C weight calculation layer.
- Added binary storage format.
- Added C++ index reading layer.
- Added palace weight statistics.
- Added Makefile, README, LICENSE, build script, and test script.
