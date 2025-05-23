#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct lichHen{
	int maHen;
	char tenBN[50];
	char tenBS[50];
	char ngayKham[10];
	char gioKham[10];
	char ghiChu[100];
	struct lichHen *pNext;
}LichHen;

typedef struct list {
	LichHen *pHead;
	LichHen *pTail;
}LIST;

//khoi tao 
void inIt(LIST &l){
	l.pHead = l.pTail = NULL;
	}

LichHen* GetlichHen(int maHen, char* tenBN, char* tenBS, char* ngayKham, char* gioKham, char* ghiChu){
	LichHen* p = (LichHen*)malloc(sizeof(LichHen));
	if(p==NULL){
		return NULL;
		}
		p->maHen = maHen;
		strcpy(p->ngayKham, ngayKham);
		strcpy(p->gioKham, gioKham);
		strcpy(p->tenBN, tenBN);
		strcpy(p->tenBS, tenBS);
		strcpy(p->ghiChu, ghiChu);
		p->pNext = NULL;
		return p;
	}

//them vao dau danh sach
void addHead(LIST &l,LichHen* p){
	if(l.pHead==NULL){
		l.pHead = l.pTail = p;
		}else{
			p->pNext = l.pHead;
			l.pHead = p;
		}
	}
	
//them vao cuoi danh sach
void addTail(LIST &l, LichHen* p){
	if(l.pTail==NULL){
		l.pHead = l.pTail = p;
		}else{
			l.pTail->pNext = p;
			l.pTail = p;
		}
	}
	
// Ham kiem tra nam nhuan
int checkNamNhuan(int nam) {
    return (nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0);
}

// Ham kiem tra ngay hop le: ngay, thang, nam
int checkDate(int ngay, int thang, int nam) {
    if (nam < 1)
        return 0;
    if (thang < 1 || thang > 12)
        return 0;
    int ngayTrongThang[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if (checkNamNhuan(nam))
        ngayTrongThang[2] = 29;
    if (ngay < 1 || ngay > ngayTrongThang[thang])
        return 0;
    return 1;
}
	
	// Ham kiem tra gio hop le: gio, phut
int checkTime(int gio, int phut) {
    if(gio < 0 || gio > 23)
        return 0;
    if(phut < 0 || phut > 59)
        return 0;
    return 1;
}


//Nhap danh sach
void datLich(LIST &l){
	int n, ngay, thang, nam, gio, phut;
	printf("Nhap so luong cuoc hen: ");
	scanf("%d",&n);
	inIt(l);
	for(int i=1; i<=n; i++){
		int maHen;
		char tenBN[50], tenBS[50], ghiChu[100],ngayKham[10],gioKham[10];
		printf("Nhap ma lich hen: ");
		scanf("%d",&maHen);
		getchar();
		
		// Nhap va kiem tra ngay
        do {
            printf("Nhap ngay kham (ngay/thang/nam): ");
            scanf("%d/%d/%d", &ngay, &thang, &nam);
            if (!checkDate(ngay, thang, nam)) {
                printf("Ngay khong hop le! Vui long nhap lai.\n");
            }
        } while(!checkDate(ngay, thang, nam));
        sprintf(ngayKham, "%d/%d/%d", ngay, thang, nam);// sprintf(dung de in so lieu vao chuoi)
		
		// Nhap va kiem tra gio
        do {
            printf("Nhap gio kham (gio 'h' phut): ");
            scanf("%d h %d", &gio, &phut);
            if (!checkTime(gio, phut)) {
                printf("Gio khong hop le! Vui long nhap lai.\n");
            }
        } while(!checkTime(gio, phut));
        sprintf(gioKham, "%d h %d", gio, phut);// sprintf(dung de in so lieu vao chuoi)
        getchar(); // Xoa bo dem nhap

		
		printf("Nhap ten benh nhan (day du ho va ten): ");
		fgets(tenBN, sizeof(tenBN),stdin);
		tenBN[strcspn(tenBN,"\n")] = '\0';
		
		printf("Nhap ten bac si (day du ho va ten): ");
		fgets(tenBS, sizeof(tenBS),stdin);
		tenBS[strcspn(tenBS,"\n")] = '\0';
		
		printf("Ghi chu (trieu chung benh): ");
		fgets(ghiChu, sizeof(ghiChu),stdin);
		ghiChu[strcspn(ghiChu,"\n")] = '\0';
		
		LichHen *p = GetlichHen(maHen, tenBN, tenBS, ngayKham, gioKham, ghiChu);
		if(p==NULL){
			printf("Loi khong the dat lich!\n");
			return;
			}
		addTail(l,p);
		printf("Lich hen da duoc dat thanh cong.\n");
		}
	}
	
void xuatLich(LIST l){
	if(l.pHead==NULL){
		printf("\nDanh sach lich hen trong!");
		return ;
		}else{
			printf("\n---------------------------------\n");
			printf("Danh sach cuoc hen: ");
			for(LichHen *p = l.pHead; p!= NULL; p = p->pNext){
				printf("\nMa lich hen: %d",p->maHen);
				printf("\nNgay kham: %s",p->ngayKham);
				printf("\nGio kham: %s",p->gioKham);
				printf("\nTen benh nhan: %s",p->tenBN);
				printf("\nTen bac si: %s",p->tenBS);
				printf("\nGhi chu (trieu chung benh): %s\n",p->ghiChu);
		}
		}
	}
	

void huyLich(LIST *l, int maHen) {
	printf("\n-----------------------------------\n");
	printf("\nVui long nhap ma lich can huy: ");
	scanf("%d",&maHen);
	
LichHen *prev = NULL, *node = l->pHead;
while (node != NULL && node->maHen != maHen) { // Duyet danh sách
    prev = node; // prev giu phan tu truoc
    node = node->pNext; // node di chuyen tiep
}
if (node == NULL) {
    printf("Khong tim thay lich hen voi ma %d!\n", maHen);
    return;
}
if (prev == NULL) { // Xóa phan tu dau tien
    l->pHead = node->pNext;
    if (l->pHead == NULL) l->pTail = NULL;
} else { // Xóa phan tu o giua hoac cuoi danh sach
    prev->pNext = node->pNext;
    if (prev->pNext == NULL) l->pTail = prev;
}

free(node); // Giai phong bo nho cua phan tu bi xaa
printf("Lich hen voi ma %d da duoc huy!\n", maHen);
}

void timKiem(LIST *l) {
    if (l->pHead == NULL) {
        printf("Danh sach lich hen trong! Khong co du lieu de tim.\n");
        return;
    }

    char key[50];
    printf("\nNhap ten benh nhan hoac ten bac si can tim kiem: ");
    getchar(); // Loai bo ky tu thua trong bo dem
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Loai bo ky tu xuong dong

    int found = 0;
    printf("Danh sach cac cuoc hen voi '%s':\n", key);
    for (LichHen *p = l->pHead; p != NULL; p = p->pNext) {
        if (strstr(p->tenBN, key) || strstr(p->tenBS, key)) { // Tim kiem theo ten
            printf("Ma lich hen: %d", p->maHen);
            printf("\nNgay kham: %s", p->ngayKham);
            printf("\nGio kham: %s", p->gioKham);
            printf("\nTen benh nhan: %s", p->tenBN);
            printf("\nTen bac si: %s", p->tenBS);
            printf("\nGhi chu: %s\n", p->ghiChu);
            found = 1;
        }
    }

    if (!found) {
        printf("Khong tim thay cuoc hen nao voi ten '%s'!\n", key);
    }
}

void sapXep(LIST *l) {
    if (l->pHead == NULL) return;

    for (LichHen *i = l->pHead; i != NULL; i = i->pNext) {
        for (LichHen *j = i->pNext; j != NULL; j = j->pNext) {
            if (strcmp(i->ngayKham, j->ngayKham) > 0 ||(strcmp(i->ngayKham, j->ngayKham) == 0 && strcmp(i->gioKham, j->gioKham) > 0)) {
                // Hoan doi du lieu
                LichHen temp = *i;
                *i = *j;
                *j = temp;

                // Cap nhat con tro lien ket
                LichHen *nextTemp = i->pNext;
                i->pNext = j->pNext;
                j->pNext = nextTemp;
            }
        }
    }
}

void outPut(LIST l) {
    if (l.pHead == NULL) {
        printf("\nDanh sach lich hen trong!\n");
        return;
    }

    printf("\n---------------------------------\n");
    printf("Danh sach cuoc hen (sau khi sap xep):\n");

    for (LichHen *p = l.pHead; p != NULL; p = p->pNext) {
        printf("\nMa lich hen: %d", p->maHen);
        printf("\nNgay kham: %s", p->ngayKham);
        printf("\nGio kham: %s", p->gioKham);
        printf("\nTen benh nhan: %s", p->tenBN);
        printf("\nTen bac si: %s", p->tenBS);
        printf("\nGhi chu: %s\n", p->ghiChu);
    }
}

void xuatRaTep(LIST l) {
    FILE *f = fopen("LichHen.txt", "w"); // Mo tep o che do ghi

    if (f == NULL) {
        printf("Loi: Khong the mo tep de ghi!\n");
        return;
    }

    if (l.pHead == NULL) {
        fprintf(f, "Danh sach lich hen trong!\n");
        printf("\nDanh sach lich hen trong!\n");
        fclose(f);
        return;
    }

    fprintf(f, "Danh sach cuoc hen:\n");
    for (LichHen *p = l.pHead; p != NULL; p = p->pNext) {
        fprintf(f, "\nMa lich hen: %d", p->maHen);
        fprintf(f, "\nNgay kham: %s", p->ngayKham);
        fprintf(f, "\nGio kham: %s", p->gioKham);
        fprintf(f, "\nTen benh nhan: %s", p->tenBN);
        fprintf(f, "\nTen bac si: %s", p->tenBS);
        fprintf(f, "\nGhi chu: %s\n", p->ghiChu);
    }

    fclose(f);
    printf("Danh sach lich hen da duoc luu vao tep 'LichHen.txt'!\n");
}


int main() {
    LIST l;

    int chon, maHen;

    while (1) {
        printf("\n==================== MENU ====================");
        printf("\n1. Dat lich hen");
        printf("\n2. Huy lich hen");
        printf("\n3. Tim kiem lich hen");
        printf("\n4. Xap xep lich hen theo ngay, gio");
        printf("\n5. Hien thi danh sach lich hen");
        printf("\n6. Xuat danh sach lich hen ra tep");
        printf("\n0. Thoat");
        printf("\n==============================================");
        printf("\nChon chuc nang: ");
        scanf("%d", &chon);
        getchar();

        switch (chon) {
            case 1:
                datLich(l);
                
                xuatLich(l);
                break;
            case 2:
                huyLich(&l, maHen);
                break;
            case 3:
                timKiem(&l);
                break;
            case 4:
                sapXep(&l);
                printf("\nDanh sach lich hen da duoc xap xep!");
                break;
            case 5:
                outPut(l);
                break;
            case 6:
			    xuatRaTep(l);
			    break;
            case 0:
                printf("\nThoat chuong trinh!");
                return 0;
            default:
                printf("\nLua chon khong hop le!");
        }
    }
    return 0;
}
