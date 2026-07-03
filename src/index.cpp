#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <iomanip>
#include <cstring>
#include <ctime>
#include <cstdint>
using namespace std;

struct FileHeader {
    char magic[4];
    uint32_t version;
    uint32_t count;
};

struct Record {
    uint32_t id;
    char category[16];
    char content[512];
    double weight;
    int64_t created_at;
};

void export_json(const vector<Record>& records, const map<string, double>& stats) {
    cout << "{\n";
    cout << "  \"version\": 1,\n";
    cout << "  \"total\": " << records.size() << ",\n";
    cout << "  \"records\": [\n";
    for (size_t i = 0; i < records.size(); i++) {
        const auto& r = records[i];
        char buf[32];
        struct tm *tm_info = localtime((time_t*)&r.created_at);
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M", tm_info);
        cout << "    {\n";
        cout << "      \"id\": " << r.id << ",\n";
        cout << "      \"category\": \"" << r.category << "\",\n";
        cout << "      \"content\": \"" << r.content << "\",\n";
        cout << "      \"weight\": " << r.weight << ",\n";
        cout << "      \"created_at\": \"" << buf << "\"\n";
        cout << "    }" << (i < records.size() - 1 ? "," : "") << "\n";
    }
    cout << "  ],\n";
    cout << "  \"stats\": {\n";
    int stat_count = 0;
    for (auto& p : stats) {
        cout << "    \"" << p.first << "\": " << fixed << setprecision(2) << p.second;
        cout << (++stat_count < (int)stats.size() ? "," : "") << "\n";
    }
    cout << "  }\n";
    cout << "}\n";
}

int main(int argc, char *argv[]) {
    bool json_mode = false;
    string data_file = "records.dat";

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--json") == 0) json_mode = true;
        else if (argv[i][0] != '-') data_file = argv[i];
    }

    ifstream f(data_file, ios::binary);
    if (!f) {
        cout << "找不到 records.dat\n";
        return 1;
    }

    FileHeader hdr;
    f.read((char*)&hdr, sizeof(hdr));
    if (strncmp(hdr.magic, "NPI1", 4) != 0) {
        cout << "無效的檔案格式\n";
        return 1;
    }

    vector<Record> records(hdr.count);
    f.read((char*)records.data(), hdr.count * sizeof(Record));
    f.close();

    map<string, double> stats;
    for (auto& r : records) stats[r.category] += r.weight;

    if (json_mode) {
        export_json(records, stats);
    } else {
        cout << "版本: " << hdr.version << "\n";
        cout << "總記錄數: " << hdr.count << "\n\n";
        for (auto& r : records) {
            char buf[32];
            struct tm *tm_info = localtime((time_t*)&r.created_at);
            strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M", tm_info);
            cout << "[ID:" << r.id << "] [" << r.category << "] " << r.content << "\n";
            cout << "  權重: " << fixed << setprecision(2) << r.weight << " | " << buf << "\n\n";
        }
        cout << "=== 宮位權重統計 ===\n";
        for (auto& p : stats) {
            cout << p.first << ": " << fixed << setprecision(2) << p.second << "\n";
        }
        cout << "\n提示: 使用 --json 參數可輸出 JSON 格式\n";
    }

    return 0;
}
