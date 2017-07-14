#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

//so phan tu cua danh sach
static int n=0;

//khai bao kieu du lieu hang hoa
typedef struct hanghoa
{
	char ten[50],loai[50],model[50],size[5];
	int ton,trangthai,gia,sl;
}HH;

//khai bao kieu du lieu node
struct node
{
	node *ppre;
	node *pnext;
	HH info;
};

//khai bao kieu du lieu danh sach
struct list
{
	node *phead;
	node *ptail;
};

//tao danh sach rong
void init(list &l)
{
	l.phead =l.ptail =NULL;
}

//tao mot node
node *getnode(HH x)
{
	node *p=new node;
	if (p==NULL)
		printf("khong du bo nho\n");
	p->info=x;
	p->pnext=NULL;
	p->ppre=NULL;
	return p;
}

//nhap mot hang hoa
HH nhap()
{
	HH a;
	fflush(stdin); 
	printf("nhap loai hang: ");
	gets(a.loai);
	printf("nhap ten hang: ");
	gets(a.ten);
	if(strcmp(a.loai,"ao")==0 || strcmp(a.loai,"giay")==0 || strcmp(a.loai,"quan")==0)
		{
			printf("nhap size: ");
			gets(a.size);
		}	
	printf("nhap model: ");
	gets(a.model);
	printf("nhap so luong: ");
	scanf("%d",&a.sl);
	a.ton=a.sl;
	printf("nhap gia: ");
	scanf("%d",&a.gia);
	a.trangthai =1;
	printf("\n");
	return a;
}

void addtail(list &l,node *p)
{
	if(l.phead ==NULL)
		l.phead =l.ptail =p;
	else
	{
		p->ppre=l.ptail ;
		l.ptail->pnext=p;
		l.ptail=p;
	}
}

//nhap danh sach
void nhapds(list &l)
{
	node *p;
	HH a;
	for (int i=0; i<n;i++)
	{
		a=nhap();
		p=getnode(a);
		addtail(l,p);
	}
}

//xuat mot node cua danh sach
void xuatnode(node *p)
{
	if(!p)
	{
		printf("danh sach rong\n");
		return;
	}
	printf("\nloai hang: ");
	puts(p->info.loai);
	printf("ten hang: ");
	puts(p->info.ten);
	printf("model: ");
	puts(p->info.model);
	if(strcmp(p->info.loai,"ao")==0 || strcmp(p->info.loai,"giay")==0 || strcmp(p->info.loai,"quan")==0)
		{
			printf("size: ");
			puts(p->info.size);
		}
	printf("gia: %d\n",p->info.gia );	
	//printf("so luong: %d",p->info.sl);
	if(p->info.trangthai == 1)
	{	
		printf("ton: %d",p->info.ton);
		printf("\ncon hang\n");
	}
	else
		printf("het hang\n");
}

//xuat danh sach
void xuatds(list l)
{
	node *p=l.phead;
	while(p!=NULL)
	{
		xuatnode(p);
		p=p->pnext;
	}
}

//xoa phan tu cuoi cung cua danh sach
void XoaCuoi(list &l)
{
	node *p;
	if (!l.phead )
		printf("danh sach rong\n");
	else if(l.phead == l.ptail )
	{
		delete l.phead;
		l.phead = l.ptail = NULL;
	}
	else
	{
		p = l.ptail ;
		l.ptail->ppre->pnext=NULL;
		l.ptail =l.ptail->ppre ;
		delete p; 
	}
}

//check xem da co hang trong danh sach chua
void check(list &l,node *q) //sai
{
	node *p=l.phead;
	for (p=l.phead ;p!=NULL;p=p->pnext)
	{
		if(strcmp(q->info.loai,"ao")==0 || strcmp(q->info.loai,"giay")==0 || strcmp(q->info.loai,"quan")==0)
		{
			if((strcmp(q->info.model,p->info.model)==0) && (strcmp(q->info.loai,p->info.loai)==0) && (strcmp(q->info.ten,p->info.ten)==0) && (strcmp(q->info.size,p->info.size)==0))
			{
				p->info.ton = p->info.sl + q->info.sl;
				if(p->info.trangthai ==0)
					p->info.trangthai = 1;
				XoaCuoi(l);
				n=n-1;
			}
		}
		if((strcmp(q->info.model,p->info.model)==0) && (strcmp(q->info.loai,p->info.loai)==0) && (strcmp(q->info.ten,p->info.ten)==0))
		{
			p->info.ton = p->info.sl + q->info.sl;
			if(p->info.trangthai ==0)
				p->info.trangthai = 1;
			XoaCuoi(l);
			n=n-1;
		}
	}
	return ;
}

//ban hang hoa
void subhh(list &l)
{
	node *p=l.phead ;
	char t[20], n[20],m[20];
	int s;
	fflush(stdin);
	printf("nhap loai hang muon ban: ");
	gets(n);
	printf("nhap ten hang muon ban: ");
	gets(t);
	printf("nhap model hang muon ban: ");
	gets(m);
	printf("nhap so luong muon ban: ");
	scanf("%d",&s);
	for(p=l.phead;p!=NULL;p=p->pnext )
	{
		if((strcmp(p->info.ten,t)==0) &&(strcmp(p->info.loai,n)==0) &&(strcmp(p->info.model,m)==0))
		{
			p->info.ton = p->info.ton - s;
			if(p->info.ton == 0)
				p->info.trangthai = 0;
		}
	}
}

//tim kiem hang hoa theo model
node *search(list l)
{
	node *p=l.phead;
	char m[20];
	fflush(stdin);
	printf("nhap model muon tim: ");
	gets(m);
	for(p=l.phead;p!=NULL;p=p->pnext)
	{
		if(strcmp(p->info.model,m)==0)
		{
			xuatnode(p);
		}
	}
	return p;
}

//xoa mot hang hoa
void xoa(list &l)
{
	node *p,*q;
	char a[20],t[20],m[20];
	fflush(stdin);
	printf("nhap loai hang muon xoa: ");
	gets(a);
	printf("nhap ten hang muon xoa: ");
	gets(t);
	printf("nhap model hang muon xoa: ");
	gets(m);
	for (p=l.phead;p!=NULL;p=p->pnext)
	{
		if((strcmp(p->info.ten,t)==0) &&(strcmp(p->info.loai,a)==0) &&(strcmp(p->info.model,m)==0))
		{
			q->pnext = p->pnext ;
			delete p;
		}
		q=p;
	}
}
//ham menu
void menu()
{
	int k;
	HH a;
	node *p;
	list l;
	init(l);
	do{
		system("cls");
		printf("1. nhap danh sach hang hoa\n");
		printf("2. in danh sach hang hoa\n");
		printf("3. nhap them mot hang hoa\n");
		printf("4. ban so luong hang hoa\n");
		printf("5. tim kiem hang hoa\n");
		printf("6. xoa mot hang hoa\n");
		printf("7. exit\n");
		printf("nhap lua chon: ");
		scanf("%d",&k);
		switch(k)
		{	
			case 1: 
				system("cls");
				printf("nhap so hang hoa: ");
				scanf("%d",&n);
				nhapds(l);
				break;
			case 2:
				system("cls");
				printf("-------------danh sach hang hoa------------\n");
				xuatds(l);
				getch();
				break;
			case 3:
				system("cls");
				a=nhap();
				p=getnode(a);
				addtail(l,p);
				n=n+1;
				check(l,p);
				break;
			case 4:
				system("cls");
				subhh(l);
				break;
			case 5:
				system("cls");
				search(l);
				getch();
				break;
			case 6:
				system("cls");
				xoa(l);
				break;
		}
	}while(k<7);
}

int main()
{
	menu();
	return 0;
}
