#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#define NAME_LENGTH 30
typedef struct employee {
    int id;
    int age;
    double salary;
    char name[NAME_LENGTH];
} employee_t;
void emp_info(employee_t emp);
int emp_aveage_age(employee_t emp[], int n); 
void emp_writefile(employee_t emp[], int n);
void emp_readfile(employee_t emp[], int n);
void emp_info(employee_t emp) {
    printf("employee id = %d\n", emp.id);
    printf("employee name = %s\n", emp.name);
    printf("employee age = %d\n", emp.age);
    printf("employee salary = %lf\n", emp.salary); 
}
int emp_aveage_age(employee_t emp[], int n) {
    if (n <= 0) {
        return 0;
    }
    int total_age = 0;
    for (int i = 0; i < n; i++) {
        total_age += emp[i].age;
    }
    return total_age / n;
}
void emp_writefile(employee_t emp[], int n) {
    FILE* fp = fopen("employee.bin", "wb+"); 
    if (fp == NULL) {
        perror("無法開啟檔案 employee.bin 進行寫入");
        return;
    }
    for (int i = 0; i < n; i++) {
        fwrite(&emp[i], sizeof(employee_t), 1, fp);
    }
    fclose(fp);
}
void emp_readfile(employee_t emp[], int n) {
    FILE* fp = fopen("employee.bin", "rb");
    if (fp == NULL) {
        perror("無法開啟檔案 employee.bin 進行讀取");
        return;
    }
    int i = 0;
    while (fread(emp + i, sizeof(employee_t), 1, fp)) {
        printf("[%d] %d %s\n", i, emp[i].id, emp[i].name);
        i++;
        if (i >= n) {
            printf("警告：讀取的資料數量已達到陣列最大容量 (%d)。\n", n);
            break; 
        }
    }
    fclose(fp);
}
int main() {
    employee_t emp[3];
    emp[0].id = 1; emp[0].age = 20; emp[0].salary = 30000.0; strcpy(emp[0].name, "IU");
    emp[1].id = 2; emp[1].age = 26; emp[1].salary = 36000.0; strcpy(emp[1].name, "taylor");
    emp[2].id = 3; emp[2].age = 31; emp[2].salary = 90000.0; strcpy(emp[2].name, "swift");
    emp_writefile(emp, 3);
    employee_t read_emp[10];
    printf("--- 讀取檔案並驗證資料 ---\n");
    emp_readfile(read_emp, 10); 
    printf("--------------------------\n");
    for (int i = 0; i < 3; i++) {
        emp_info(read_emp[i]);
    }
    int avg_age = emp_aveage_age(read_emp, 3);
    printf("\n[計算結果]\n");
    printf("員工平均年齡 = %d\n", avg_age); 
    return 0;
}
