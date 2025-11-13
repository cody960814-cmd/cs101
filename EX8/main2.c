#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_SETS 5
#define NUM_PER_SET 7
#define MAX_LOTTO_NUM 69
#define COUNT_FILE "lotto_count.txt"

void generate_lotto_set(int numbers[]) {
    int i, j, new_num, is_duplicate;
    
    srand((unsigned int)time(NULL) + rand()); 

    for (i = 0; i < NUM_PER_SET; i++) {
        do {
            new_num = (rand() % MAX_LOTTO_NUM) + 1;
            
            is_duplicate = 0;
            for (j = 0; j < i; j++) {
                if (numbers[j] == new_num) {
                    is_duplicate = 1;
                    break;
                }
            }
        } while (is_duplicate);
        
        numbers[i] = new_num;
    }
}

void update_lotto_count(int *current_count) {
    FILE *fp;
    
    fp = fopen(COUNT_FILE, "r");
    if (fp != NULL) {
        fscanf(fp, "%d", current_count);
        fclose(fp);
    } else {
        *current_count = 0;
    }
    
    (*current_count)++;

    fp = fopen(COUNT_FILE, "w");
    if (fp != NULL) {
        fprintf(fp, "%d", *current_count);
        fclose(fp);
    }
}

int main() {
    int lotto_count;
    char filename[50];
    char time_str[50];
    time_t timer;
    struct tm *tm_info;
    FILE *output_file;
    int lotto_numbers[NUM_PER_SET];
    
    update_lotto_count(&lotto_count);
    
    time(&timer);
    tm_info = localtime(&timer);
    strftime(time_str, 50, "%a %b %e %H:%M:%S %Y", tm_info);
    
    sprintf(filename, "lotto[%05d].txt", lotto_count);
    
    output_file = fopen(filename, "w");
    if (output_file == NULL) {
        fprintf(stderr, "Error: Could not open output file %s\n", filename);
        return 1;
    }
    
    // 寫入彩票單據內容
    fprintf(output_file, "======== lotto649 ========\n");
    fprintf(output_file, "+ No.%05d +\n", lotto_count);
    fprintf(output_file, "= %s =\n", time_str);
    
    for (int i = 0; i < NUM_SETS; i++) {
        generate_lotto_set(lotto_numbers);
        
        fprintf(output_file, "[%d]:", i + 1);
        for (int j = 0; j < NUM_PER_SET; j++) {
            fprintf(output_file, " %02d", lotto_numbers[j]);
        }
        fprintf(output_file, "\n");
    }
    
    fprintf(output_file, "======== csie@CGU ========\n");
    
    fclose(output_file);
    
    printf("成功生成單據：%s\n", filename);
    
    return 0;
}
