#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

// 카운트다운 함수 (숫자만 간단하게 출력)
// 숫자 3의 ASCII 아트 출력

void set_text_color(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void reset_text_color()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // 흰색
}

void print_three() {
    printf(" _____ \n");
    printf("|____ |\n");
    printf("    / /\n");
    printf("    \\ \\\n");
    printf(".___/ /\n");
    printf("\\____/ \n");
}

// 숫자 2의 ASCII 아트 출력
void print_two() {
    printf(" _____ \n");
    printf("/ __  \\\n");
    printf("`' / /'\n");
    printf("  / /  \n");
    printf("./ /___\n");
    printf("\\_____/\n");
}

// 숫자 1의 ASCII 아트 출력
void print_one() {
    printf(" __   \n");
    printf("/  |  \n");
    printf("`| |  \n");
    printf(" | |  \n");
    printf("_| |_ \n");
    printf("\\___/ \n");
}

// 카운트다운 함수 (ASCII 아트 출력)
void countdown() {
    for (int i = 3; i > 0; i--) {
        system("cls");  // 화면 지우기 (Windows 기준)
        switch (i) {
            case 3:
                print_three();  // 3 출력
                break;
            case 2:
                print_two();  // 2 출력
                break;
            case 1:
                print_one();  // 1 출력
                break;
        }
        Sleep(1000);  // 1초 대기
    }
    system("cls");  // 화면 지우기 (Windows 기준)
}

void start_screen() {
	set_text_color(11);
    printf(" _____        _              _                                                   _   \n");
    printf("/  ___|      | |            | |                                                 | |  \n");
    printf("\\ `--.   ___ | |  ___   ___ | |_   _   _   ___   _   _  _ __   ___   ___   __ _ | |_ \n");
    printf(" `--. \\ / _ \\| | / _ \\ / __|| __| | | | | / _ \\ | | | || '__| / __| / _ \\ / _` || __|\n");
    printf("/\\__/ /|  __/| ||  __/| (__ | |_  | |_| || (_) || |_| || |    \\__ \\|  __/| (_| || |_ \n");
    printf("\\____/  \\___||_| \\___| \\___| \\__|  \\__, | \\___/  \\__,_||_|    |___/ \\___| \\__,_| \\__|\n");
    printf("                                    __/ |                                             \n");
    printf("                                   |___/                                              \n");
    reset_text_color(); 
        
    printf("\n아무 키나 누르십시오...\n");
    system("pause > nul");  // 사용자 입력 대기 후 다음으로 넘어감
    system("cls");  // 화면 지우기
}

// 자리 배치 관련 함수들
void seat_arrangement(int row, int column, int seats[], int eyesight[], int tall[], int manual[], int swapped[], int eyesight_count, int tall_count, int manual_count, int swapped_count);
void shuffle_number(int sit_number[], int total);
void set_text_color(int color);
void reset_text_color();
int is_in_list(int num, int list[], int count);
void assign_students(int row, int column, int seats[], int list[], int count, int start_row, int end_row);
void swap_seats(int seats[], int row, int column, int swapped[], int *swapped_count); // 자리 교환 기능 (배정 후에만 사용 가능)
void save_to_csv(int seats[], int row, int column); // CSV로 자리 배정 결과 내보내기
void print_seats(int seats[], int row, int column, int eyesight[], int tall[], int manual[], int swapped[], int eyesight_count, int tall_count, int manual_count, int swapped_count); // 현재 좌석 배치를 출력하는 함수
void manual_seat_assignment(int seats[], int row, int column, int manual[], int *manual_count); // 수동 배정 기능

void reset_logs(int seats[], int eyesight[], int tall[], int manual[], int swapped[], int *eyesight_count, int *tall_count, int *manual_count, int *swapped_count, int total) {
    for (int i = 0; i < total; i++) {
        seats[i] = 0;
    }
    *eyesight_count = 0;
    *tall_count = 0;
    *manual_count = 0;
    *swapped_count = 0;

    printf("모든 로그가 초기화되었습니다.\n");
}

int main(void)
{
    int row, column;
    int eyesight[100] = {0}, tall[100] = {0}, manual[100] = {0}, swapped[100] = {0};  // 시력이 안 좋은 친구, 키가 큰 친구, 수동 배정 친구, 교환된 친구 배열
    int eyesight_count = 0, tall_count = 0, manual_count = 0, swapped_count = 0;
    int seats[100] = {0};  // 전체 좌석 배열
    int seat_assigned = 0; // 자리 배정 완료 여부 플래그
    int choice;

	start_screen();

    printf("자리배치 프로그램\n\n");
    printf("좌석배치에 대한 행과 열을 입력해야 합니다.\n");
    printf("학생수는 최대 100명입니다.(10X10)\n");
    printf("행의 수를 입력하고 Enter>");
    scanf("%d", &row);
    printf("열의 수를 입력하고 Enter>");
    scanf("%d", &column);

    do {
        printf("\n자리 배열 방법을 선택하시오 1: 올랜덤, 2: 시력이 안 좋은 친구, 3: 키가 큰 친구, 4: 자리 교환 (배정 후), 5: 수동 지정, 6: CSV 내보내기, 7: 초기화, 0: 종료\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                countdown(); // 카운트다운 실행
                seat_arrangement(row, column, seats, eyesight, tall, manual, swapped, eyesight_count, tall_count, manual_count, swapped_count);
                print_seats(seats, row, column, eyesight, tall, manual, swapped, eyesight_count, tall_count, manual_count, swapped_count); // 자리 배치 후 출력
                seat_assigned = 1; // 자리 배정 완료 플래그
                break;
            case 2:
                printf("시력이 안 좋은 친구의 학생 번호를 입력하십시오 (0 입력 시 종료): ");
                while (1) {
                    int num;
                    scanf("%d", &num);
                    if (num == 0) break;
                    eyesight[eyesight_count++] = num;
                }
                break;
            case 3:
                printf("키가 큰 친구의 학생 번호를 입력하십시오 (0 입력 시 종료): ");
                while (1) {
                    int num;
                    scanf("%d", &num);
                    if (num == 0) break;
                    tall[tall_count++] = num;
                }
                break;
            case 4:
                if (seat_assigned) {
                    swap_seats(seats, row, column, swapped, &swapped_count); // 자리 교환 후 출력
                    print_seats(seats, row, column, eyesight, tall, manual, swapped, eyesight_count, tall_count, manual_count, swapped_count);
                } else {
                    printf("자리 배정이 완료되지 않았습니다. 먼저 자리를 배정해주세요.\n");
                }
                break;
            case 5:
                manual_seat_assignment(seats, row, column, manual, &manual_count); // 수동 배정 후 출력
                print_seats(seats, row, column, eyesight, tall, manual, swapped, eyesight_count, tall_count, manual_count, swapped_count);
                break;
            case 6:
                save_to_csv(seats, row, column); // CSV 내보내기
                break;
            case 7:
                reset_logs(seats, eyesight, tall, manual, swapped, &eyesight_count, &tall_count, &manual_count, &swapped_count, row * column); // 초기화 기능 추가
                break;
            case 0:
                printf("프로그램 종료\n");
                break;
            default:
                printf("잘못된 선택입니다.\n");
        }
    } while (choice != 0);

    return 0;
}

void seat_arrangement(int row, int column, int seats[], int eyesight[], int tall[], int manual[], int swapped[], int eyesight_count, int tall_count, int manual_count, int swapped_count)
{
    int sit_number[100] = {0};  // 전체 좌석에 배정할 학생 번호 배열
    int total = row * column;  // 전체 좌석 수
    int i, j;

    for (i = 0; i < total; i++)
        sit_number[i] = i + 1;  // 학생 번호 초기화

    shuffle_number(sit_number, total);  // 전체 학생 번호를 랜덤으로 섞음

    // 시력이 안 좋은 친구들을 앞쪽 절반에 랜덤으로 배치
    int half_row = row / 2;
    assign_students(row, column, seats, eyesight, eyesight_count, 0, half_row - 1);

    // 키가 큰 친구들을 뒤쪽 절반에 랜덤으로 배치
    assign_students(row, column, seats, tall, tall_count, half_row, row - 1);

    // 수동 배정된 학생들은 이미 자리에 배정되어 있음

    // 나머지 학생들 랜덤 배치 (시력, 키, 수동 배정 제외)
    int remaining_students[100] = {0};
    int remaining_count = 0;

    for (i = 0; i < total; i++) {
        if (!is_in_list(sit_number[i], eyesight, eyesight_count) && 
            !is_in_list(sit_number[i], tall, tall_count) && 
            !is_in_list(sit_number[i], manual, manual_count)) {
            remaining_students[remaining_count++] = sit_number[i];
        }
    }
    assign_students(row, column, seats, remaining_students, remaining_count, 0, row - 1);
}

void shuffle_number(int sit_number[], int total)
{
    int i, rnd, temp;
    for (i = 0; i < total; i++)
    {
        rnd = rand() % total;
        temp = sit_number[rnd];
        sit_number[rnd] = sit_number[i];
        sit_number[i] = temp;
    }
}



int is_in_list(int num, int list[], int count)
{
    for (int i = 0; i < count; i++) {
        if (list[i] == num)
            return 1;  // 해당 번호가 리스트에 존재함
    }
    return 0;  // 리스트에 존재하지 않음
}

void assign_students(int row, int column, int seats[], int list[], int count, int start_row, int end_row)
{
    int total_seats = row * column;
    int available_seats[100] = {0};
    int available_count = 0;

    if (start_row < 0 || end_row >= row || start_row > end_row) {
        printf("잘못된 행 범위: start_row = %d, end_row = %d\n", start_row, end_row);
        return;
    }

    for (int i = start_row; i <= end_row; i++) {
        for (int j = 0; j < column; j++) {
            int seat_index = i * column + j;
            if (seats[seat_index] == 0) {
                available_seats[available_count++] = seat_index;
            }
        }
    }

    shuffle_number(available_seats, available_count);

    for (int i = 0; i < count && i < available_count; i++) {
        seats[available_seats[i]] = list[i];
    }
}

// 자리 교환 기능 (자리 배정 후에만 사용 가능)
void swap_seats(int seats[], int row, int column, int swapped[], int *swapped_count)
{
    int seat1, seat2;
    printf("교환할 두 학생의 번호를 입력하십시오: ");
    scanf("%d %d", &seat1, &seat2);

    for (int i = 0; i < row * column; i++) {
        if (seats[i] == seat1) seats[i] = seat2;
        else if (seats[i] == seat2) seats[i] = seat1;
    }

    swapped[*swapped_count] = seat1; // 교환된 학생 저장
    (*swapped_count)++;
    swapped[*swapped_count] = seat2;
    (*swapped_count)++;

    printf("자리 교환 완료.\n");
}

// 좌석 배치를 출력하는 함수
void print_seats(int seats[], int row, int column, int eyesight[], int tall[], int manual[], int swapped[], int eyesight_count, int tall_count, int manual_count, int swapped_count)
{
    printf("\n현재 좌석 배치:\n");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            int current_student = seats[i * column + j];

            if (is_in_list(current_student, eyesight, eyesight_count)) {
                set_text_color(12);  // 빨간색 (시력이 안 좋은 친구)
            } else if (is_in_list(current_student, tall, tall_count)) {
                set_text_color(9);   // 파란색 (키가 큰 친구)
            } else if (is_in_list(current_student, manual, manual_count)) {
                set_text_color(10);  // 초록색 (수동 배정된 친구)
            } else if (is_in_list(current_student, swapped, swapped_count)) {
                set_text_color(14);  // 노란색 (자리 교환된 친구)
            } else {
                set_text_color(15);  // 하얀색 (나머지)
            }

            if (current_student != 0) {
                printf("%2d ", current_student);
            } else {
                printf("   ");  // 빈 자리
            }
            reset_text_color();  // 색상 리셋
        }
        printf("\n");
    }
    printf("\n");
}

// CSV로 자리 배정 결과 내보내기
void save_to_csv(int seats[], int row, int column)
{
    FILE *fp = fopen("seat_arrangement.csv", "w");
    if (fp == NULL) {
        printf("파일 저장 실패\n");
        return;
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            fprintf(fp, "%d", seats[i * column + j]);
            if (j < column - 1) fprintf(fp, ",");
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    printf("CSV 파일로 저장 완료.\n");
}

// 수동 배정 기능
void manual_seat_assignment(int seats[], int row, int column, int manual[], int *manual_count)
{
    int student, seat_row, seat_col;
    printf("배정할 학생 번호를 입력하십시오: ");
    scanf("%d", &student);
    printf("배정할 좌석의 행과 열을 입력하십시오 (예: 3 4): ");
    scanf("%d %d", &seat_row, &seat_col);

    if (seat_row >= 1 && seat_row <= row && seat_col >= 1 && seat_col <= column) {
        seats[(seat_row - 1) * column + (seat_col - 1)] = student;
        manual[*manual_count] = student; // 수동 배정한 학생 기록
        (*manual_count)++;
        printf("수동 배정 완료.\n");
    } else {
        printf("잘못된 좌석 범위입니다.\n");
    }
}

