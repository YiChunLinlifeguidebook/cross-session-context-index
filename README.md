# 🧭 九宮多維對話索引系統（Nine-Palace Index）

A lightweight, dependency-free symbolic indexing engine for structured conversation records — written in plain C + C++.

輕量級、無外部依賴的結構化記錄索引引擎,用 C 計算權重、C++ 讀取與統計,適合個人知識庫、AI 協作記憶、會議記錄等場景。

---

## ✨ Features

- **設定檔驅動的關鍵字權重**:關鍵字與權重全部寫在 `config/weights.conf`,不用改程式碼就能自訂分類邏輯
- **動態記錄陣列**:記錄筆數不再受限於固定大小,依需求自動擴充
- **累加式寫入**:多次執行會讀入既有記錄再新增,不會覆蓋掉之前的資料
- **分類篩選查詢**:`./bin/index records.dat <分類>` 只看特定宮位的記錄
- **宮位權重統計**:自動加總各分類的權重
- **跨語言二進位交換**:C 寫入 `.dat`,C++ 讀取,零外部函式庫依賴

---

## 🚀 安裝與建置

需要 `gcc` 與 `g++`(支援 C99 / C++14 即可)。

```bash
make
```

會產生 `bin/weight` 與 `bin/index` 兩個執行檔。

---

## 📖 使用方式

### 1. 設定關鍵字權重

編輯 `config/weights.conf`:

```
核心:0.3
測試:0.2
商業:0.2
架構:0.1
環境:0.1
```

格式是 `關鍵字:權重增量`,基礎權重固定 0.5,命中越多關鍵字權重越高(封頂 1.0)。

### 2. 新增記錄

```bash
./bin/weight config/weights.conf records.dat JIU_C "系統核心架構設計"
```

### 3. 查詢與統計

```bash
# 顯示全部記錄與各宮位權重統計
./bin/index records.dat

# 只顯示特定分類
./bin/index records.dat JIU_C
```

---

## 🧪 測試

```bash
make test
```

會自動寫入三筆示範記錄並執行檢索,驗證整個流程可以正常運作。

---

## 🏗 架構

```
weight.c (讀設定檔 + 計算權重)  --->  records.dat (二進位)  --->  index.cpp (讀取 + 統計)
```

```
nine-palace-index/
├── src/
│   ├── weight.c
│   └── index.cpp
├── config/
│   └── weights.conf
├── bin/                (build 產生,不進版控)
├── Makefile
├── build.sh
├── test.sh
├── README.md
├── LICENSE
├── CHANGELOG.md
├── CONTRIBUTING.md
└── .gitignore
```

---

## ⚠️ 已知限制

- 二進位格式使用 C struct 直接讀寫,理論上跨平台(不同 endianness / struct padding)可能有相容性問題,同一台機器 / 相同編譯環境下使用沒有問題
- 關鍵字比對是單純子字串比對,不含分詞或語意理解
- 分類名稱(`cat`)最長 31 字元,內容(`content`)最長 255 字元,超過會被截斷

歡迎透過 PR 改進以上任一項。

---

## 📄 License

MIT License,詳見 [LICENSE](LICENSE)。
# nine-palace-index
