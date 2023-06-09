﻿#define _CRT_SECURE_NO_WARNINGS // nếu không dùng visual studio thì xóa bỏ dòng này đi
#include <stdio.h>
#include <string.h>

/*
* @author Branium Academy
* @version 2023.05
* @see https://braniumacademy.net
*/

// cấu trúc sinh viên
typedef struct {
	char id[20];		// mã sinh viên
	char fullName[40];	// họ tên đầy đủ
	char address[40];	// địa chỉ
	float math;			// điểm toán
	float eng;			// điểm tiếng anh
	float prog;			// điểm lập trình
	float gpa;			// điểm TB
} Student;

// hàm nguyên mẫu
// hàm nhập thông tin sinh viên
void getStudentInfo(Student*);
// hàm đọc file
void readFile(Student*, int*);
// hàm ghi danh sách sv vào file
void writeFile(const Student*, int);
// hàm hiển thị
void showStudents(const Student*, int);
// hàm sắp xếp theo điểm TB giảm dần
void sort(Student*, int);
// hàm tính điểm trung bình
void calculateGpa(Student*, int);
// hàm tìm kiếm sinh viên theo mã
int findStudentById(const Student*, int, const char*);
// hàm cập nhật điểm của sinh viên theo mã
void updateGrades(Student*, int, const char*);
// hàm hiển thị thông tin 1 sinh viên
void showAStudent(Student);

int main() {
	Student students[100];
	int n = 0;
	int choice;
	// đọc danh sách sinh viên khi chương trình khởi động
	readFile(students, &n);
	do {
		puts("============ QUAN LY SINH VIEN ============");
		puts("1. Them moi sinh vien vao danh sach");
		puts("2. Hien thi danh sach sinh vien ra man hinh");
		puts("3. Tim kiem sinh vien theo ma");
		puts("4. Cap nhat diem sinh vien theo ma");
		puts("5. Tinh diem trung binh cho cac sinh vien");
		puts("6. Sap xep danh sach sinh vien theo diem trung binh giam dan");
		puts("7. Ghi danh sach sinh vien vao file");
		puts("0. Thoat chuong trinh");
		printf("Xin moi chon: ");
		scanf("%d", &choice);
		printf("============ Chuc nang so %d ============ \n", choice);

		switch (choice)
		{
		case 0:
			puts("\n");
			puts("========================================");
			puts("===> CAM ON BAN DA SU DUNG DICH VU! <===");
			puts("========================================");
			break;
		case 1:
		{
			// nhập thêm sinh viên mới
			char id[20];
			printf("Ma SV: ");
			scanf("%19s", id);
			// kiểm tra xem sinh viên có mã id này đã tồn tại chưa
			int index = findStudentById(students, n, id);
			if (index != -1) {
				puts("--> Sinh vien nay da ton tai. Hay nhap ma sv khac! <--");
			}
			else {
				strcpy(students[n].id, id); // copy id vào sinh viên thứ n
				// nhập các thông tin còn lại của sv
				getStudentInfo(&students[n]);
				n++;
			}
			break;
		}
		case 2:
		{
			showStudents(students, n);
			break;
		}
		case 3:
		{
			char id[20];
			printf("%s", "Nhap ma sv can tim: ");
			scanf("%*c%19s", id);
			int index = findStudentById(students, n, id);
			if (index == -1) {
				puts("--> Sinh vien can tim khong co trong danh sach <--");
			}
			else {
				printf("--> Tim thay sinh vien ma \"%s\": <--\n", id);
				showAStudent(students[index]);
			}
			break;
		}
		case 4:
		{
			char id[20];
			printf("%s", "Nhap ma sv can cap nhat diem: ");
			scanf("%*c%19s", id);
			int index = findStudentById(students, n, id);
			updateGrades(students, n, id);
			break;
		}
		case 5:
		{
			calculateGpa(students, n);
			showStudents(students, n);
			break;
		}
		case 6:
		{
			sort(students, n);
			if (n > 0) {
				showStudents(students, n);
			}
			break;
		}
		case 7:
		{
			writeFile(students, n);
			break;
		}
		default:
			puts("--> Vui long chon cac chuc nang tu 0 - 7 <--");
			break;
		}
		puts(""); // in xuống dòng
	} while (choice != 0);

	return 0;
}

void getStudentInfo(Student* s) {
	// nhập họ và tên
	printf("Ho ten sv: ");
	scanf("%*c%39[^\n]", s->fullName);
	printf("Dia chi: ");
	scanf("%*c%39[^\n]", s->address);
	printf("Diem toan: ");
	scanf("%f", &s->math);
	printf("Diem anh: ");
	scanf("%f", &s->eng);
	printf("Diem lap trinh: ");
	scanf("%f%*c", &s->prog);
	s->gpa = 0; // giả định ban đầu điểm tb là 0
}

int findStudentById(const Student* students, int n, const char* id) {
	int i;
	for (i = 0; i < n; i++) {
		// nếu mã sinh viên cần tìm trùng với sv bất kì trong ds
		if (strcmp(students[i].id, id) == 0) {
			return i; // trả về chỉ số của phần tử trong mảng
		}
	}
	return -1; // không tìm thấy sinh viên
}

void updateGrades(Student* students, int n, const char* id) {
	int index = findStudentById(students, n, id);
	if (index != -1) {
		// tiến hành cập nhật
		float math, eng, prog;
		puts("Nhap diem cac mon toan, anh, lap trinh: ");
		scanf("%f%f%f", &math, &eng, &prog);
		students[index].math = math;
		students[index].eng = eng;
		students[index].prog = prog;
	}
	else {
		printf("--> Sinh vien ma \"%s\" khong ton tai! <--\n", id);
	}
}

void readFile(Student* students, int* n) {
	FILE* fin = fopen("STUDENTS.TXT", "rb"); // mo file de doc
	if (fin) {
		int i = 0;
		Student s;
		while (!feof(fin)) {
			fread(&s, sizeof(Student), 1, fin); // đọc sinh viên ra
			if (feof(fin)) {
				break;
			}
			students[i] = s;
			i++;
		}
		*n = i; // cập nhật số sinh viên
		fclose(fin);
	}
	else {
		puts("--> Khong the mo file. Vui long kiem tra lai.");
	}
}

void writeFile(const Student* students, int n) {
	FILE* fout = fopen("STUDENTS.TXT", "wb"); // mở file để ghi mới
	if (fout) {
		int i;
		for (i = 0; i < n; i++)
		{
			fwrite(&students[i], sizeof(Student), 1, fout); // ghi sv vào file
		}
		fclose(fout);
		puts("--> Ghi file thanh cong! <--");
	}
	else {
		puts("--> Khong the tao file. Vui long kiem tra lai.");
	}
}

void showAStudent(Student s) {
	printf("%-15s%-20s%-20s%-10s%-10s%-10s%-10s\n",
		"Ma SV", "Ho va ten", "Dia chi", "Toan",
		"Anh", "Lap trinh", "Diem TB");
	printf("%-15s%-20s%-20s%-10.2f%-10.2f%-10.2f%-10.2f\n",
		s.id, s.fullName, s.address,
		s.math, s.eng,
		s.prog, s.gpa);
}

void showStudents(const Student* students, int n) {
	if (n > 0) {
		puts("===================================="
			" DANH SACH SINH VIEN "
			"=====================================");
		printf("%-15s%-20s%-20s%-10s%-10s%-10s%-10s\n",
			"Ma SV", "Ho va ten", "Dia chi", "Toan",
			"Anh", "Lap trinh", "Diem TB");
		int i;
		for (i = 0; i < n; i++)
		{
			puts("------------------------------"
				"--------------------------------"
				"--------------------------------");
			printf("%-15s%-20s%-20s%-10.2f%-10.2f%-10.2f%-10.2f\n",
				students[i].id, students[i].fullName, students[i].address,
				students[i].math, students[i].eng,
				students[i].prog, students[i].gpa);
		}
	}
	else {
		puts("--> Danh sach sinh vien rong <--");
	}
}

void sort(Student* students, int n) {
	void swap(Student * a, Student * b);
	if (n > 0) {
		int i, j;
		for (i = 0; i < n - 1; i++)
		{
			for (j = n - 1; j > i; j--)
			{
				if (students[j].gpa > students[j - 1].gpa) {
					swap(&students[j], &students[j - 1]);
				}
			}
		}
	}
	else {
		puts("--> Danh sach rong khong the sap xep <--");
	}
}

// hàm đổi chỗ hai phần tử
void swap(Student* a, Student* b) {
	Student s = *a;
	*a = *b;
	*b = s;
}

void calculateGpa(Student* students, int n) {
	int i;
	for (i = 0; i < n; i++)
	{
		students[i].gpa =
			(students[i].math + students[i].eng + students[i].prog) / 3;
	}
}