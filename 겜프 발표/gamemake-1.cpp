#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

// ī��Ʈ�ٿ� �Լ� (���ڸ� �����ϰ� ���)
// ���� 3�� ASCII ��Ʈ ���

void set_text_color(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void reset_text_color()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // ���
}

void print_three() {
    printf(" _____ \n");
    printf("|____ |\n");
    printf("    / /\n");
    printf("    \\ \\\n");
    printf(".___/ /\n");
    printf("\\____/ \n");
}

// ���� 2�� ASCII ��Ʈ ���
void print_two() {
    printf(" _____ \n");
    printf("/ __  \\\n");
    printf("`' / /'\n");
    printf("  / /  \n");
    printf("./ /___\n");
    printf("\\_____/\n");
}

// ���� 1�� ASCII ��Ʈ ���
void print_one() {
    printf(" __   \n");
    printf("/  |  \n");
    printf("`| |  \n");
    printf(" | |  \n");
    printf("_| |_ \n");
    printf("\\___/ \n");
}

// ī��Ʈ�ٿ� �Լ� (ASCII ��Ʈ ���)
void countdown() {
    for (int i = 3; i > 0; i--) {
        system("cls");  // ȭ�� ����� (Windows ����)
        switch (i) {
            case 3:
                print_three();  // 3 ���
                break;
            case 2:
                print_two();  // 2 ���
                break;
            case 1:
                print_one();  // 1 ���
                break;
        }
        Sleep(1000);  // 1�� ���
    }
    system("cls");  // ȭ�� ����� (Windows ����)
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
        
    printf("\n�ƹ� Ű�� �����ʽÿ�...\n");
    system("pause > nul");  // ����� �Է� ��� �� �������� �Ѿ
    system("cls");  // ȭ�� �����
}

// �ڸ� ��ġ ���� �Լ���
void seat_arrangement(int row, int column, int seats[], int eyesight[], int tall[], int manual[], int swapped[], int eyesight_count, int tall_count, int manual_count, int swapped_count);
void shuffle_number(int sit_number[], int total);
void set_text_color(int color);
void reset_text_color();
int is_in_list(int num, int list[], int count);
void assign_students(int row, int column, int seats[], int list[], int count, int start_row, int end_row);
void swap_seats(int seats[], int row, int column, int swapped[], int *swapped_count); // �ڸ� ��ȯ ��� (���� �Ŀ��� ��� ����)
void save_to_csv(int seats[], int row, int column); // CSV�� �ڸ� ���� ��� ��������
void print_seats(int seats[], int row, int column, int eyesight[], int tall[], int manual[], int swapped[], int eyesight_count, int tall_count, int manual_count, int swapped_count); // ���� �¼� ��ġ�� ����ϴ� �Լ�
void manual_seat_assignment(int seats[], int row, int column, int manual[], int *manual_count); // ���� ���� ���

void reset_logs(int seats[], int eyesight[], int tall[], int manual[], int swapped[], int *eyesight_count, int *tall_count, int *manual_count, int *swapped_count, int total) {
    for (int i = 0; i < total; i++) {
        seats[i] = 0;
    }
    *eyesight_count = 0;
    *tall_count = 0;
    *manual_count = 0;
    *swapped_count = 0;

    printf("��� �αװ� �ʱ�ȭ�Ǿ����ϴ�.\n");
}

int main(void)
{
    int row, column;
    int eyesight[100] = {0}, tall[100] = {0}, manual[100] = {0}, swapped[100] = {0};  // �÷��� �� ���� ģ��, Ű�� ū ģ��, ���� ���� ģ��, ��ȯ�� ģ�� �迭
    int eyesight_count = 0, tall_count = 0, manual_count = 0, swapped_count = 0;
    int seats[100] = {0};  // ��ü �¼� �迭
    int seat_assigned = 0; // �ڸ� ���� �Ϸ� ���� �÷���
    int choice;

	start_screen();

    printf("�ڸ���ġ ���α׷�\n\n");
    printf("�¼���ġ�� ���� ��� ���� �Է��ؾ� �մϴ�.\n");
    printf("�л����� �ִ� 100���Դϴ�.(10X10)\n");
    printf("���� ���� �Է��ϰ� Enter>");
    scanf("%d", &row);
    printf("���� ���� �Է��ϰ� Enter>");
    scanf("%d", &column);

    do {
        printf("\n�ڸ� �迭 ����� �����Ͻÿ� 1: �÷���, 2: �÷��� �� ���� ģ��, 3: Ű�� ū ģ��, 4: �ڸ� ��ȯ (���� ��), 5: ���� ����, 6: CSV ��������, 7: �ʱ�ȭ, 0: ����\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                countdown(); // ī��Ʈ�ٿ� ����
                seat_arrangement(row, column, seats, eyesight, tall, manual, swapped, eyesight_count, tall_count, manual_count, swapped_count);
                print_seats(seats, row, column, eyesight, tall, manual, swapped, eyesight_count, tall_count, manual_count, swapped_count); // �ڸ� ��ġ �� ���
                seat_assigned = 1; // �ڸ� ���� �Ϸ� �÷���
                break;
            case 2:
                printf("�÷��� �� ���� ģ���� �л� ��ȣ�� �Է��Ͻʽÿ� (0 �Է� �� ����): ");
                while (1) {
                    int num;
                    scanf("%d", &num);
                    if (num == 0) break;
                    eyesight[eyesight_count++] = num;
                }
                break;
            case 3:
                printf("Ű�� ū ģ���� �л� ��ȣ�� �Է��Ͻʽÿ� (0 �Է� �� ����): ");
                while (1) {
                    int num;
                    scanf("%d", &num);
                    if (num == 0) break;
                    tall[tall_count++] = num;
                }
                break;
            case 4:
                if (seat_assigned) {
                    swap_seats(seats, row, column, swapped, &swapped_count); // �ڸ� ��ȯ �� ���
                    print_seats(seats, row, column, eyesight, tall, manual, swapped, eyesight_count, tall_count, manual_count, swapped_count);
                } else {
                    printf("�ڸ� ������ �Ϸ���� �ʾҽ��ϴ�. ���� �ڸ��� �������ּ���.\n");
                }
                break;
            case 5:
                manual_seat_assignment(seats, row, column, manual, &manual_count); // ���� ���� �� ���
                print_seats(seats, row, column, eyesight, tall, manual, swapped, eyesight_count, tall_count, manual_count, swapped_count);
                break;
            case 6:
                save_to_csv(seats, row, column); // CSV ��������
                break;
            case 7:
                reset_logs(seats, eyesight, tall, manual, swapped, &eyesight_count, &tall_count, &manual_count, &swapped_count, row * column); // �ʱ�ȭ ��� �߰�
                break;
            case 0:
                printf("���α׷� ����\n");
                break;
            default:
                printf("�߸��� �����Դϴ�.\n");
        }
    } while (choice != 0);

    return 0;
}

void seat_arrangement(int row, int column, int seats[], int eyesight[], int tall[], int manual[], int swapped[], int eyesight_count, int tall_count, int manual_count, int swapped_count)
{
    int sit_number[100] = {0};  // ��ü �¼��� ������ �л� ��ȣ �迭
    int total = row * column;  // ��ü �¼� ��
    int i, j;

    for (i = 0; i < total; i++)
        sit_number[i] = i + 1;  // �л� ��ȣ �ʱ�ȭ

    shuffle_number(sit_number, total);  // ��ü �л� ��ȣ�� �������� ����

    // �÷��� �� ���� ģ������ ���� ���ݿ� �������� ��ġ
    int half_row = row / 2;
    assign_students(row, column, seats, eyesight, eyesight_count, 0, half_row - 1);

    // Ű�� ū ģ������ ���� ���ݿ� �������� ��ġ
    assign_students(row, column, seats, tall, tall_count, half_row, row - 1);

    // ���� ������ �л����� �̹� �ڸ��� �����Ǿ� ����

    // ������ �л��� ���� ��ġ (�÷�, Ű, ���� ���� ����)
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
            return 1;  // �ش� ��ȣ�� ����Ʈ�� ������
    }
    return 0;  // ����Ʈ�� �������� ����
}

void assign_students(int row, int column, int seats[], int list[], int count, int start_row, int end_row)
{
    int total_seats = row * column;
    int available_seats[100] = {0};
    int available_count = 0;

    if (start_row < 0 || end_row >= row || start_row > end_row) {
        printf("�߸��� �� ����: start_row = %d, end_row = %d\n", start_row, end_row);
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

// �ڸ� ��ȯ ��� (�ڸ� ���� �Ŀ��� ��� ����)
void swap_seats(int seats[], int row, int column, int swapped[], int *swapped_count)
{
    int seat1, seat2;
    printf("��ȯ�� �� �л��� ��ȣ�� �Է��Ͻʽÿ�: ");
    scanf("%d %d", &seat1, &seat2);

    for (int i = 0; i < row * column; i++) {
        if (seats[i] == seat1) seats[i] = seat2;
        else if (seats[i] == seat2) seats[i] = seat1;
    }

    swapped[*swapped_count] = seat1; // ��ȯ�� �л� ����
    (*swapped_count)++;
    swapped[*swapped_count] = seat2;
    (*swapped_count)++;

    printf("�ڸ� ��ȯ �Ϸ�.\n");
}

// �¼� ��ġ�� ����ϴ� �Լ�
void print_seats(int seats[], int row, int column, int eyesight[], int tall[], int manual[], int swapped[], int eyesight_count, int tall_count, int manual_count, int swapped_count)
{
    printf("\n���� �¼� ��ġ:\n");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            int current_student = seats[i * column + j];

            if (is_in_list(current_student, eyesight, eyesight_count)) {
                set_text_color(12);  // ������ (�÷��� �� ���� ģ��)
            } else if (is_in_list(current_student, tall, tall_count)) {
                set_text_color(9);   // �Ķ��� (Ű�� ū ģ��)
            } else if (is_in_list(current_student, manual, manual_count)) {
                set_text_color(10);  // �ʷϻ� (���� ������ ģ��)
            } else if (is_in_list(current_student, swapped, swapped_count)) {
                set_text_color(14);  // ����� (�ڸ� ��ȯ�� ģ��)
            } else {
                set_text_color(15);  // �Ͼ�� (������)
            }

            if (current_student != 0) {
                printf("%2d ", current_student);
            } else {
                printf("   ");  // �� �ڸ�
            }
            reset_text_color();  // ���� ����
        }
        printf("\n");
    }
    printf("\n");
}

// CSV�� �ڸ� ���� ��� ��������
void save_to_csv(int seats[], int row, int column)
{
    FILE *fp = fopen("seat_arrangement.csv", "w");
    if (fp == NULL) {
        printf("���� ���� ����\n");
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
    printf("CSV ���Ϸ� ���� �Ϸ�.\n");
}

// ���� ���� ���
void manual_seat_assignment(int seats[], int row, int column, int manual[], int *manual_count)
{
    int student, seat_row, seat_col;
    printf("������ �л� ��ȣ�� �Է��Ͻʽÿ�: ");
    scanf("%d", &student);
    printf("������ �¼��� ��� ���� �Է��Ͻʽÿ� (��: 3 4): ");
    scanf("%d %d", &seat_row, &seat_col);

    if (seat_row >= 1 && seat_row <= row && seat_col >= 1 && seat_col <= column) {
        seats[(seat_row - 1) * column + (seat_col - 1)] = student;
        manual[*manual_count] = student; // ���� ������ �л� ���
        (*manual_count)++;
        printf("���� ���� �Ϸ�.\n");
    } else {
        printf("�߸��� �¼� �����Դϴ�.\n");
    }
}

