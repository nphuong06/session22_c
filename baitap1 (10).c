#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Students {
    char id[10], fullName[100];
    int age;
};

void addStudents(struct Students s[], int *sizePtr){
	fflush(stdin);
	printf("\nNhap ID: ");
	fgets(s[*sizePtr].id, 10, stdin);
	s[*sizePtr].id[strcspn(s[*sizePtr].id, "\n")] = '\0';
	printf("Nhap ho ten: ");
	fgets(s[*sizePtr].fullName, 100, stdin);
	s[*sizePtr].fullName[strcspn(s[*sizePtr].fullName, "\n")] = '\0';
	printf("Nhap tuoi: ");
	scanf("%d", &s[*sizePtr].age);
	(*sizePtr)++;
	printf("\n");
}

void saveToFile(struct Students s[], int *sizePtr){
	FILE *file;
	file  = fopen("students.bin", "wb");
	if(file == NULL){
		printf("\nKhong the luu file\n\n");
		return;
	}
	fwrite(s, sizeof(struct Students), *sizePtr, file);
	fclose(file);
}

void loadToFile(struct Students s[], int *sizePtr){
	FILE *file = fopen("students.bin", "rb");
	if(file == NULL){
		printf("\nKhong the load file\n\n");
		return;
	}
	(*sizePtr) = 0;
    while(fread(&s[*sizePtr], sizeof(struct Students), 1, file) == 1 && *sizePtr < 100) {
        (*sizePtr)++;
    }
	if(*sizePtr != 0){
		printf("\nLoad file thanh cong\n\n");
	}
	fclose(file);
}

void printStudents(struct Students s[], int *sizePtr){
	if(*sizePtr == 0){
		printf("\nDanh sach sinh vien trong\n\n");
	}
	else{
		printf("\nThong tin sinh vien\n");
		printf("--------------------\n");
		for(int i = 0; i < *sizePtr; i++){
			printf("ID: %s", s[i].id);
			printf("\nHo ten: %s", s[i].fullName);
			printf("\nTuoi: %d", s[i].age);
			printf("\n--------------------\n");
		}
	printf("\n");
	}
}

void editStudents(struct Students s[], int *sizePtr){
	fflush(stdin);
	char *id;
	int found = 0;
	id = (char *)calloc(10, sizeof(char));
	printf("\nNhap ID sinh vien muon sua thong tin: ");
	fgets(id, 10, stdin);
	id[strcspn(id, "\n")] = '\0';
	for(int i = 0; i < *sizePtr; i++){
		if(strstr(s[i].id, id) != NULL){
			found = 1;
			printf("\nNhap ten sinh vien: ");
			fgets(s[i].fullName, 100, stdin);
			s[i].fullName[strcspn(s[i].fullName, "\n")] = '\0';
			printf("Nhap tuoi: ");
			scanf("%d", &s[i].age);
		}
	}
	if(found == 0){
		printf("\nID sinh vien khong ton tai\n\n");
	}
	else{
		printf("\nSua thong tin hoan tat\n\n");
	}
	free(id);
}

void removeStudents(struct Students s[], int *sizePtr) {
    fflush(stdin);
    char *id;
    int found = 0;
    id = (char *)calloc(10, sizeof(char));
    printf("\nNhap ID sinh vien muon xoa: ");
    fgets(id, 10, stdin);
    id[strcspn(id, "\n")] = '\0';
    for (int i = 0; i < *sizePtr; i++) {
        if (strstr(s[i].id, id) != NULL) {
            found = 1;
            for (int j = i; j < *sizePtr - 1; j++){
                s[j] = s[j + 1];
            }
            (*sizePtr)--;
            break;
        }
    }
    if (found == 0) {
        printf("\nID sinh vien khong ton tai\n\n");
    } else {
        printf("\nXoa thanh cong\n\n");
    }
    free(id);
}

void searchByID(struct Students s[], int *sizePtr){
	fflush(stdin);
	char *id;
	int found = 0;
	id = (char *)calloc(10, sizeof(char));
	printf("\nNhap ID sinh vien can tim kiem: ");
	fgets(id, 10, stdin);
	id[strcspn(id, "\n")] = '\0';
	for(int i = 0; i < *sizePtr; i++){
		if(strstr(s[i].id, id) != NULL){
			found = 1;
			printf("\nID: %s", s[i].id);
			printf("\nHo ten: %s", s[i].fullName);
			printf("\nTuoi: %d", s[i].age);
		}
	}
	if(found == 0){
		printf("\nID sinh vien khong ton tai\n\n");
	}
	free(id);
}

void sortByName(struct Students s[], int *sizePtr){
	for(int i = 0; i < (*sizePtr)-1; i++){
		for(int j = 0; j < (*sizePtr)-i-1; j++){
			if(s[j].fullName > s[j+1].fullName){
				struct Students temp = s[j];
				s[j] = s[j+1];
				s[j+1] = temp;
			}
		}
	}
	printf("\nSap xep thanh cong\n\n");
}

int main(){
    struct Students s[100];
    int size = 0, choice;
    int *sizePtr = &size;
    loadToFile(s, sizePtr);
    do {
        printf("1. In danh sach sinh vien\n");
        printf("2. Them sinh vien\n");
        printf("3. Sua thong tin sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Tim kiem sinh vien\n");
        printf("6. Sap xep sinh\n");
        printf("7. Thoat\n");
        printf("Nhap chuc nang: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                printStudents(s, sizePtr);
                break;
            case 2:
                addStudents(s, sizePtr);
                saveToFile(s, sizePtr);
                break;
            case 3:
            	editStudents(s, sizePtr);
            	saveToFile(s, sizePtr);
            	break;
            case 4:
            	removeStudents(s, sizePtr);
            	saveToFile(s, sizePtr);
            	break;
            case 5:
            	searchByID(s, sizePtr);
            	break;
            case 6:
            	sortByName(s, sizePtr);
            	saveToFile(s, sizePtr);
            	break;
            case 7:
            	printf("\nThoat thanh cong\n");
            	break;
            default:
            	printf("\nChuc nang khong hop le\n\n");
            	break;
        }
    } 
	while(choice != 7);
    return 0;
}

