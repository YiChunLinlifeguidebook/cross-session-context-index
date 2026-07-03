#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

#define MAGIC "NPI1"
#define VERSION 1
#define INITIAL_CAPACITY 16
#define MAX_KEYWORDS 256
#define MAX_LINE 256

typedef struct {
    char magic[4];
    uint32_t version;
    uint32_t count;
} FileHeader;

typedef struct {
    uint32_t id;
    char category[16];
    char content[512];
    double weight;
    int64_t created_at;
} Record;

typedef struct {
    char keyword[32];
    char category[16];
    double weight;
} KeywordEntry;

Record *records = NULL;
uint32_t record_count = 0;
uint32_t record_capacity = 0;
uint32_t next_id = 1;

KeywordEntry keywords[MAX_KEYWORDS];
int keyword_count = 0;

int load_config(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("無法讀取設定檔: %s\n", filename);
        return 0;
    }
    char line[MAX_LINE];
    keyword_count = 0;
    while (fgets(line, sizeof(line), fp) && keyword_count < MAX_KEYWORDS) {
        if (line[0] == '#' || line[0] == '\n') continue;
        line[strcspn(line, "\n")] = 0;
        char *keyword = strtok(line, "|");
        char *category = strtok(NULL, "|");
        char *weight_str = strtok(NULL, "|");
        if (keyword && category && weight_str) {
            strncpy(keywords[keyword_count].keyword, keyword, 31);
            strncpy(keywords[keyword_count].category, category, 15);
            keywords[keyword_count].weight = atof(weight_str);
            keyword_count++;
        }
    }
    fclose(fp);
    printf("設定檔載入 %d 個關鍵字\n", keyword_count);
    return 1;
}

double calc_weight(const char *content) {
    double w = 0.0;
    for (int i = 0; i < keyword_count; i++) {
        if (strstr(content, keywords[i].keyword)) {
            w += keywords[i].weight;
        }
    }
    if (w > 1.0) w = 1.0;
    return w;
}

void auto_classify(const char *content, char *out_category, double *out_weight) {
    double category_weights[16] = {0};
    char category_names[16][16] = {0};
    int category_count = 0;
    double total_weight = 0.0;

    for (int i = 0; i < keyword_count; i++) {
        if (strstr(content, keywords[i].keyword)) {
            total_weight += keywords[i].weight;
            int found = -1;
            for (int j = 0; j < category_count; j++) {
                if (strcmp(category_names[j], keywords[i].category) == 0) {
                    found = j;
                    break;
                }
            }
            if (found == -1) {
                strcpy(category_names[category_count], keywords[i].category);
                category_weights[category_count] = keywords[i].weight;
                category_count++;
            } else {
                category_weights[found] += keywords[i].weight;
            }
        }
    }

    if (category_count > 0) {
        int best = 0;
        for (int i = 1; i < category_count; i++) {
            if (category_weights[i] > category_weights[best]) best = i;
        }
        strcpy(out_category, category_names[best]);
        *out_weight = (total_weight > 1.0) ? 1.0 : total_weight;
    } else {
        strcpy(out_category, "UNKNOWN");
        *out_weight = 0.0;
    }
}

void add_record(const char *category, const char *content, double weight) {
    if (record_count >= record_capacity) {
        record_capacity = (record_capacity == 0) ? INITIAL_CAPACITY : record_capacity * 2;
        records = (Record*)realloc(records, record_capacity * sizeof(Record));
        if (!records) {
            printf("記憶體分配失敗\n");
            exit(1);
        }
    }
    Record *r = &records[record_count];
    r->id = next_id++;
    strncpy(r->category, category, 15);
    strncpy(r->content, content, 511);
    r->weight = weight;
    r->created_at = (int64_t)time(NULL);
    record_count++;
    printf("新增記錄 ID:%u | %s | 權重: %.2f\n", r->id, category, weight);
}

void save_records(const char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        printf("無法寫入\n");
        return;
    }
    FileHeader hdr;
    memcpy(hdr.magic, MAGIC, 4);
    hdr.version = VERSION;
    hdr.count = record_count;
    fwrite(&hdr, sizeof(FileHeader), 1, fp);
    fwrite(records, sizeof(Record), record_count, fp);
    fclose(fp);
    printf("已儲存 %u 筆記錄到 %s\n", record_count, filename);
}

void show_records() {
    printf("\n對話記錄:\n");
    for (uint32_t i = 0; i < record_count; i++) {
        Record *r = &records[i];
        char time_buf[32];
        struct tm *tm_info = localtime((time_t*)&r->created_at);
        strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M", tm_info);
        printf("[ID:%u][%s] %s\n  權重: %.2f | %s\n", r->id, r->category, r->content, r->weight, time_buf);
    }
}

void load_records(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) return;
    FileHeader hdr;
    fread(&hdr, sizeof(FileHeader), 1, fp);
    if (strncmp(hdr.magic, MAGIC, 4) != 0 || hdr.version != VERSION) {
        fclose(fp);
        return;
    }
    record_count = hdr.count;
    record_capacity = record_count + INITIAL_CAPACITY;
    records = (Record*)malloc(record_capacity * sizeof(Record));
    fread(records, sizeof(Record), record_count, fp);
    fclose(fp);
    for (uint32_t i = 0; i < record_count; i++) {
        if (records[i].id >= next_id) next_id = records[i].id + 1;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("用法:\n");
        printf("  手動分類: %s config records category content\n", argv[0]);
        printf("  自動分類: %s config records content\n", argv[0]);
        return 1;
    }

    char *config_file = argv[1];
    char *data_file = argv[2];

    if (!load_config(config_file)) return 1;

    load_records(data_file);

    char category[16];
    char content[512];
    double weight;

    if (argc == 5) {
        strcpy(category, argv[3]);
        strcpy(content, argv[4]);
        weight = calc_weight(content);
        printf("手動分類: %s\n", category);
    } else {
        strcpy(content, argv[3]);
        auto_classify(content, category, &weight);
        printf("自動分類: %s (權重: %.2f)\n", category, weight);
    }

    add_record(category, content, weight);
    show_records();
    save_records(data_file);

    free(records);
    return 0;
}
