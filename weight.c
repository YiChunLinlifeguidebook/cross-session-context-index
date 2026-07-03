#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX 100
typedef struct { char cat[10]; char content[256]; double weight; } Rec;
Rec list[MAX]; int count=0;

double calc(const char *s) {
    double w=0.5;
    if(strstr(s,"核心")) w+=0.3;
    if(strstr(s,"測試")) w+=0.2;
    if(strstr(s,"商業")) w+=0.2;
    if(w>1.0) w=1.0;
    return w;
}

void add(const char *c, const char *s) {
    strcpy(list[count].cat, c);
    strcpy(list[count].content, s);
    list[count].weight = calc(s);
    count++;
    printf("✅ 記錄 %d | %s | 權重 %.2f\n", count, c, list[count-1].weight);
}

int main() {
    printf("九宮權重計算\n");
    add("JIU_C","悟空系統核心架構");
    add("JIU_ES","Termux測試環境");
    add("JIU_W","FITI計畫申請");
    for(int i=0;i<count;i++)
        printf("[%s] %s (%.2f)\n", list[i].cat, list[i].content, list[i].weight);
    return 0;
}
