﻿#define _CRT_SECURE_NO_WARNINGS // nếu không dùng visual studio thì xóa bỏ dòng này đi
#include <stdio.h>
#include <string.h>

/*
* @author Branium Academy
* @version 2023.05
* @see https://braniumacademy.net
*/

// cấu trúc tài khoản ngân hàng
typedef struct {
	int id;					// mã tài khoản
	char name[40];			// tên tài khoản
	char accNumber[30];		// số tài khoản
	long long ballance;		// số dư
	char startDate[20]; 	// ngày phát hành
	int depositTerm;		// kì hạn gửi
	double interest;		// lãi suất
} BankAcc;

// hàm nguyên mẫu
// hàm nhập thông tin tài khoản
void createAccount(BankAcc*);
// hàm đọc file
void readFile(BankAcc*, int*);
// hàm ghi danh sách tk vào file
void writeFile(const BankAcc*, int);
// hàm hiển thị
void showAccounts(const BankAcc*, int);
// hàm sắp xếp theo số dư giảm dần
void sortAcc(BankAcc*, int);
// hàm tính tiền lãi
void calculateInterest(BankAcc*, int);
// hàm tìm kiếm tài khoản theo mã
int findBankAccById(const BankAcc*, int, int);
// hàm tìm kiếm tài khoản theo số tài khoản
int findByAccNumber(const BankAcc*, int, const char*);
// hàm tìm kiếm tài khoản theo tên tài khoản
int findByAccName(const BankAcc*, int, BankAcc*, const char*);
// hàm cập số dư của tài khoản theo mã
void updateBallance(BankAcc*, int, int);
// hàm hiển thị thông tin 1 tài khoản
void showABankAcc(BankAcc acc);
// hàm xóa tài khoản theo mã tk
void removeAccById(BankAcc*, int*, int);

int main() {
	BankAcc accounts[100];
	int n = 0;
	int choice;
	// đọc danh sách tài khoản khi chương trình khởi động
	readFile(accounts, &n);
	do {
		puts("============ QUAN LY TAI KHOAN NGAN HANG ============");
		puts("1. Them moi tai khoan vao danh sach");
		puts("2. Hien thi danh sach tai khoan ra man hinh");
		puts("3. Tim kiem tai khoan theo so tai khoan");
		puts("4. Tim kiem tai khoan theo ten tai khoan");
		puts("5. Xoa 1 tai khoan theo ma");
		puts("6. Cap nhat so du theo ma tai khoan");
		puts("7. Sap xep danh sach tai khoan theo so du giam dan");
		puts("8. Tinh tien lai cho cac tai khoan theo ki han");
		puts("9. Ghi danh sach tai khoan vao file");
		puts("0. Thoat chuong trinh");
		printf("Xin moi chon: ");
		scanf("%d", &choice);
		printf("============ Chuc nang so %d ============ \n", choice);

		switch (choice)
		{
		case 0:
			system("cls");
			puts("\n");
			puts("================================================================");
			puts("===> CAM ON BAN DA SU DUNG DICH VU CUA NGAN HANG CHUNG TOI! <===");
			puts("================================================================");
			break;
		case 1:
		{
			// nhập thêm tài khoản mới
			int id;
			printf("Nhap ma tk: ");
			scanf("%d", &id);
			// kiểm tra xem tài khoản có mã id này đã tồn tại chưa
			int index = findBankAccById(accounts, n, id);
			if (index != -1) {
				puts("--> Tai khoan nay da ton tai. Hay nhap ma khac! <--");
			}
			else {
				accounts[n].id = id;
				// nhập các thông tin còn lại của tk
				createAccount(&accounts[n]);
				n++;
			}
			break;
		}
		case 2:
		{
			system("cls"); // xóa màn hình
			showAccounts(accounts, n);
			break;
		}
		case 3:
		{
			system("cls");
			char accNum[30];
			printf("%s", "Nhap so tk can tim: ");
			scanf("%*c%29[^\n]", accNum);
			int index = findByAccNumber(accounts, n, accNum);
			if (index == -1) {
				puts("--> Tai khoan can tim khong co trong danh sach <--");
			}
			else {
				printf("--> Tim thay TK co so TK \"%s\": <--\n", accNum);
				showABankAcc(accounts[index]);
			}
			break;
		}
		case 4:
		{
			system("cls");
			BankAcc result[100];
			char accName[20];
			printf("%s", "Nhap ten TK can tim: ");
			scanf("%*c%39[^\n]", accName);
			int count = findByAccName(accounts, n, result, accName);
			if (count == 0) { // nếu giá trị nhận được là 0
				puts("--> Tai khoan can tim khong co trong danh sach <--");
			}
			else { // ngược lại hiển thị danh sách các tài khoản thỏa mãn
				printf("--> Tim thay TK co ten \"%s\": <--\n", accName);
				showAccounts(result, count);
			}
			break;
		}
		case 5:
		{
			system("cls");
			int id;
			printf("Nhap ma tk can xoa: ");
			scanf("%d", &id);
			removeAccById(accounts, &n, id);
			break;
		}
		case 6:
		{
			system("cls");
			int id;
			printf("Nhap ma tk can cap nhat so du: ");
			scanf("%d", &id);
			updateBallance(accounts, n, id);
			break;
		}
		case 7:
		{
			system("cls");
			sortAcc(accounts, n);
			if (n > 0) {
				showAccounts(accounts, n);
			}
			break;
		}
		case 8:
		{
			system("cls");
			calculateInterest(accounts, n);
			if (n > 0) {
				showAccounts(accounts, n);
			}
			break;
		}
		case 9:
		{
			system("cls");
			writeFile(accounts, n);
			break;
		}
		default:
			system("cls"); // xóa màn hình
			puts("--> Vui long chon cac chuc nang tu 0 - 9 <--");
			break;
		}
		puts(""); // in xuống dòng
	} while (choice != 0);

	return 0;
}

void createAccount(BankAcc* acc) {
	printf("%s", "So tai khoan: ");
	scanf("%*c%29[^\n]", acc->accNumber);
	printf("%s", "Ten TK: ");
	scanf("%*c%39[^\n]", acc->name);
	printf("%s", "So du: ");
	scanf("%lld", &acc->ballance);
	printf("%s", "Ngay phat hanh: ");
	scanf("%*c%19s", acc->startDate);
	printf("%s", "Ki han gui: ");
	scanf("%d", &acc->depositTerm);
	acc->interest = 0; // ban đầu cho tiền lãi = 0
}

int findBankAccById(const BankAcc* accounts, int n, int id) {
	int i;
	for (i = 0; i < n; i++) {
		// nếu mã tài khoản cần tìm trùng với tk bất kì trong ds
		if (accounts[i].id == id) {
			return i; // trả về chỉ số của phần tử trong mảng
		}
	}
	return -1; // không tìm thấy tài khoản
}

int findByAccNumber(const BankAcc* accounts, int n, const char* accNum) {
	int i;
	for (i = 0; i < n; i++) {
		// nếu số tài khoản cần tìm trùng với tk bất kì trong ds
		if (strcmp(accounts[i].accNumber, accNum) == 0) {
			return i; // trả về chỉ số của phần tử trong mảng
		}
	}
	return -1; // không tìm thấy tài khoản
}

int findByAccName(const BankAcc* accounts, int n,
	BankAcc* found, const char* accName) {
	int count = 0; // đếm số tài khoản đc tìm thấy
	int i;
	for (i = 0; i < n; i++) {
		// nếu tên tài khoản cần tìm trùng với tk bất kì trong ds
		if (strcmp(accounts[i].name, accName) == 0) {
			found[count++] = accounts[i]; // thêm vào ds kq
		}
	}
	return count; // trả về số lượng tài khoản đc tìm thấy
}

void updateBallance(BankAcc* accounts, int n, int id) {
	int index = findBankAccById(accounts, n, id);
	if (index != -1) {
		// tiến hành cập nhật
		long long ballance;
		puts("Nhap so du moi: ");
		scanf("%lld", &ballance);
		accounts[index].ballance = ballance;
		puts("--> Cap nhat so du thanh cong <--");
	}
	else {
		printf("--> Tai khoan ma %d khong ton tai! <--\n", id);
	}
}

void readFile(BankAcc* accounts, int* n) {
	FILE* fin = fopen("BACC.TXT", "rb"); // mo file de doc
	if (fin) {
		int i = 0;
		BankAcc s;
		while (!feof(fin)) {
			fread(&s, sizeof(BankAcc), 1, fin); // đọc tài khoản ra
			if (feof(fin)) {
				break;
			}
			accounts[i] = s;
			i++;
		}
		*n = i; // cập nhật số lượng tài khoản
		fclose(fin);
	}
	else {
		puts("==> Khong the mo file. Vui long kiem tra lai.");
	}
}

void writeFile(const BankAcc* accounts, int n) {
	FILE* fout = fopen("BACC.TXT", "wb"); // mở file để ghi mới
	if (fout) {
		int i;
		for (i = 0; i < n; i++)
		{
			fwrite(&accounts[i], sizeof(BankAcc), 1, fout); // ghi tk vào file
		}
		fclose(fout);
		puts("--> Ghi file thanh cong! <--");
	}
	else {
		puts("==> Khong the tao file. Vui long kiem tra lai.");
	}
}

void showABankAcc(BankAcc s) {
	printf("%-12s%-20s%-20s%-15s%-15s%-10s%-15s\n",
		"Ma TK", "Ten tai khoan", "So tai khoan", "So du",
		"Ngay phat hanh", "Ki han", "Lai suat");
	printf("%-12d%-20s%-20s%-15lld%-15s%-10d%-15.2lf\n",
		s.id, s.name, s.accNumber,
		s.ballance, s.startDate,
		s.depositTerm, s.interest);
}

void showAccounts(const BankAcc* accounts, int n) {
	if (n > 0) {
		puts("========================================="
			" DANH SACH TAI KHOAN "
			"==========================================");
		printf("%-12s%-20s%-20s%-15s%-15s%-10s%-15s\n",
			"Ma TK", "Ten tai khoan", "So tai khoan", "So du",
			"Ngay PH TK", "Ki han", "Lai suat");
		int i;
		for (i = 0; i < n; i++)
		{
			puts("----------------------------------"
				"-----------------------------------"
				"-----------------------------------");
			printf("%-12d%-20s%-20s%-15lld%-15s%-10d%-15.2lf\n",
				accounts[i].id, accounts[i].name, accounts[i].accNumber,
				accounts[i].ballance, accounts[i].startDate,
				accounts[i].depositTerm, accounts[i].interest);
		}
	}
	else {
		puts("--> Danh sach tai khoan rong <--");
	}
}

void sortAcc(BankAcc* accounts, int n) {
	void swap(BankAcc * a, BankAcc * b);
	if (n > 0) {
		int i, j;
		for (i = 0; i < n - 1; i++)
		{
			for (j = n - 1; j > i; j--)
			{
				if (accounts[j].ballance > accounts[j - 1].ballance) {
					swap(&accounts[j], &accounts[j - 1]);
				}
			}
		}
	}
	else {
		puts("--> Danh sach rong khong the sap xep <--");
	}
}

// hàm đổi chỗ hai phần tử
void swap(BankAcc* a, BankAcc* b) {
	BankAcc s = *a;
	*a = *b;
	*b = s;
}

void calculateInterest(BankAcc* accounts, int n) {
	float findInterestRate(int month); // function prototype 
	int i;
	for (i = 0; i < n; i++)
	{
		accounts[i].interest = accounts[i].ballance *
			findInterestRate(accounts[i].depositTerm) / 100;
	}
	puts("--> Tinh lai suat thanh cong! <--");
}

// hàm trả về lãi suất dựa trên kì hạn gửi
float findInterestRate(int month) {
	if (month == 1) { // 1 tháng
		return 7;
	}
	else if (month <= 3) { // 2 - 3 tháng
		return 6.5f;
	}
	else if (month <= 6) { // 4 - 6 tháng
		return 6.25f;
	}
	else if (month <= 12) { // 7-12 tháng
		return 6;
	}
	else { // trên 12 tháng-0 kì hạn
		return 5.5f;
	}
}

void removeAccById(BankAcc* accounts, int* n, int id) {
	int index = findBankAccById(accounts, *n, id);
	if (index != -1) { // tìm thấy tài khoản
		int i;
		for (i = (int)index; i < *n - 1; i++)
		{
			accounts[i] = accounts[i + 1]; // dịch trái ds tk 1 đơn vị
		}
		(*n)--;
		puts("--> Xoa tai khoan thanh cong! <--");
	}
	else {
		puts("--> Tai khoan can xoa khong ton tai! <--");
	}
}
