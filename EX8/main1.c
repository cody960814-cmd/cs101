#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定義常數
#define MAX_LINE_LENGTH 100 // 每一行彩票數據的最大長度
#define LOTTO_NUM_COUNT 7   // 每張彩票有 7 個號碼
#define WIN_NUM_COUNT 3     // 需檢查的 3 個中獎號碼

// 結構體用於儲存彩票號碼
typedef struct {
    int id;
    int numbers[LOTTO_NUM_COUNT];
} LottoTicket;

/**
 * @brief 檢查一張彩票是否包含三個中獎號碼中的任一個 (根據您提供的輸出範例)
 * * @param ticket_numbers 7 個彩票號碼的陣列
 * @param win_numbers 3 個中獎號碼的陣列
 * @return int 1 if at least one number matches, 0 otherwise
 */
int check_winning(int ticket_numbers[], int win_numbers[]) {
    // 迴圈檢查每一個中獎號碼
    for (int i = 0; i < WIN_NUM_COUNT; i++) {
        // 迴圈檢查彩票的 7 個號碼
        for (int j = 0; j < LOTTO_NUM_COUNT; j++) {
            // 只要找到任何一個中獎號碼，立即判定為中獎並返回 1
            if (win_numbers[i] == ticket_numbers[j]) {
                return 1; // 找到至少一個符合的號碼
            }
        }
    }
    
    // 遍歷所有號碼後都沒有找到符合的，則未中獎
    return 0;
}

int main() {
    FILE *fp;
    char line[MAX_LINE_LENGTH];
    char date_line[MAX_LINE_LENGTH] = ""; // 用來儲存日期行
    int win_numbers[WIN_NUM_COUNT];
    LottoTicket current_ticket;

    // 1. 獲取使用者輸入的中獎號碼
    printf("請輸入中獎號碼三個 : ");
    if (scanf("%d %d %d", &win_numbers[0], &win_numbers[1], &win_numbers[2]) != WIN_NUM_COUNT) {
        fprintf(stderr, "輸入錯誤，請輸入三個數字。\n");
        return 1;
    }
    
    // 輸出確認中獎號碼 (使用 %02d 確保輸出為兩位數，如 05)
    printf("輸入中獎號碼為 : %02d %02d %02d\n", win_numbers[0], win_numbers[1], win_numbers[2]);
    printf("以下為中獎彩卷:\n");

    // 2. 開啟檔案
    fp = fopen("lotto.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "無法開啟檔案 lotto.txt。請確認檔案存在。\n");
        return 1;
    }
    
    // 3. 讀取檔案內容
    // 讀取第一行標頭 (忽略)
    if (fgets(line, MAX_LINE_LENGTH, fp) == NULL) goto end_of_file;
    
    // 讀取第二行日期 (儲存)
    if (fgets(date_line, MAX_LINE_LENGTH, fp) == NULL) goto end_of_file;
    // 移除換行符
    date_line[strcspn(date_line, "\n")] = 0; // 清除末尾的 \n
    
    // 讀取並處理每一期的彩票號碼
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        if (line[0] == '[') {
            // 嘗試從行中解析出號碼：[id]: N1 N2 N3 N4 N5 N6 N7
            int result = sscanf(line, "[%d]: %d %d %d %d %d %d %d", 
                                &current_ticket.id, 
                                &current_ticket.numbers[0], 
                                &current_ticket.numbers[1], 
                                &current_ticket.numbers[2], 
                                &current_ticket.numbers[3], 
                                &current_ticket.numbers[4], 
                                &current_ticket.numbers[5], 
                                &current_ticket.numbers[6]);

            if (result == LOTTO_NUM_COUNT + 1) { // 成功解析 1 個 ID 和 7 個號碼
                // 4. 對獎判斷 (現在使用寬鬆的「包含任一」標準)
                if (check_winning(current_ticket.numbers, win_numbers)) {
                    // 5. 輸出中獎結果
                    // 輸出日期 (date_line)
                    printf("售出時間 : %s [%d]:", date_line, current_ticket.id);
                    // 輸出彩票號碼
                    for (int i = 0; i < LOTTO_NUM_COUNT; i++) {
                        printf(" %02d", current_ticket.numbers[i]);
                    }
                    printf("\n");
                }
            }
        } else if (strstr(line, "========") != NULL) {
            // 遇到結尾標記，停止讀取
            break;
        }
    }

end_of_file:
    // 關閉檔案
    fclose(fp);

    return 0;
}
