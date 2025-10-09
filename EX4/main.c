#include <stdio.h>

int main() {
    int arr1[3] = {0, 1, 2};
    char arr2[3] = {'A', 'B', 'C'};
    float arr3[3] = {1.1f, 1.2f, 1.3f};
    FILE *fp = fopen("a.bin", "wb");
    if (fp == NULL) {
        printf("無法開啟檔案進行寫入\n");
        return 1;
    }
    fwrite(arr1, sizeof(int), 3, fp);
    fwrite(arr2, sizeof(char), 3, fp);
    fwrite(arr3, sizeof(float), 3, fp);
    fclose(fp);
    FILE *fp2 = fopen("a.bin", "rb");
    if (fp2 == NULL) {
        printf("無法開啟檔案進行讀取\n");
        return 1;
    }
    int read_arr1[3];
    char read_arr2[3];
    float read_arr3[3];
    fread(read_arr1, sizeof(int), 3, fp2);
    fread(read_arr2, sizeof(char), 3, fp2);
    fread(read_arr3, sizeof(float), 3, fp2);
    fclose(fp2);
    for (int i = 0; i < 3; i++) {
        printf("%d ", read_arr1[i]);
    }
    printf("\n");

    for (int i = 0; i < 3; i++) {
        printf("%c ", read_arr2[i]);
    }
    printf("\n");

    for (int i = 0; i < 3; i++) {
        printf("%f ", read_arr3[i]);
    }
    printf("\n");

    return 0;
}
