#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXBOOKS 40

//�û��ṹ�嶨��
typedef struct user {
    char name[20];
    char password[20];
    char id[12];
    struct user* next;
} User;

//�鼮�ṹ�嶨��
typedef struct book {
    char ISBN[14];
    char name[50];
    char author[50];
    char publisher[50];
    int year;
    char shelf[10];
    int floor;
    int borrow;
    int lei;
    char leiname[50];
} Book;

//������
typedef struct bookfile
{
    Book bookdata;
    struct bookfile* next;
} Bookfile;


//ȫ�ֱ�������

Book bookfile[MAXBOOKS];
int booknum;
int length = sizeof(bookfile) / sizeof(Book);
char username[20];
//��������ͷ
User* head = NULL;


//��������
int registerUser();//ע�ắ��
int loginUser(char* m);//��¼����
void addBook();//���ͼ��
void deleteBook();//ɾ��ͼ��
void borrowBook(char* n);//����ͼ��
void returnBook(char* username);//�黹ͼ��
void searchBook();//��ѯͼ��
void ReaderMenu();//���߽���
void ManagerMenu();//����Ա����
void BeginMenu();//��ʼ�˵�
void userSearchMenu();//�û���ѯ�˵�
void managerSearchMenu();//����Ա��ѯ�˵�
void dayi();//����ϵͳ
void yanzhengma();//��֤��
void bookreview();//������ѯ
void tuijian();//�����Ƽ�
void mohu();//ģ����ѯ
void suijisearchBook();//���ѡ��
void gexinghua(); //���Ի��Ƽ�
void outlei(struct book *p);
void feedback();//����������
void searchfeedback();//��ѯ����������
Bookfile* creathead();//������ͷ
Bookfile* creatnode(Book newbook);//�����ڵ�
void erweima();//��ά��

//������
int main()
{
    int flag_1, flag_2, flag_3, flag_4,
        cash_1, cash_2;
    int choice;


    cash_1 = cash_2 = 1;
    yanzhengma();
    while (1) {
        //��¼ҳ��
        BeginMenu();
        scanf("%d", &choice);//��¼��ע��ķ�֧
        switch (choice) {
        case 1:


            flag_1 = loginUser(username);
            cash_1 = 1;
            //flag_1=1Ϊ���ߵ�¼��2Ϊ�����ߵ�¼
            switch (flag_1)
            {
            case 1://����ģ��
                while (cash_1) {

                    ReaderMenu();//����ҳ��

                    scanf("%d", &choice);//���߲����ķ�֧
                    switch (choice)
                    {
                    case 1://�軹ͼ���
                        borrowBook(username);//����ͼ��
                        break;
                    case 2:
                        returnBook(username);//�黹ͼ��
                        break;
                    case 3:
                        userSearchMenu();
                        searchBook();//��ѯͼ��
                        break;
                    case 4:
                        bookreview();//������ѯ
                        break;
                    case 5:
                        dayi();//����
                        break;
                    case 6:
                        suijisearchBook();//�����ѯ
                        break;
                    case 7:
                        tuijian();//�����Ƽ�
                        break;
                    case 8:
                        gexinghua(); //���Ի��Ƽ�
                        break;
                    case 9:
                        feedback();//����������
                        break;
                    case 10:
                        erweima();
                        break;
                    case 0:cash_1 = 0; break;
                    default:
                        break;
                    }
                }

                break;
            case 2://����Աģ��
                while (cash_1) {
                    ManagerMenu();
                    //����Աҳ��
                    scanf("%d", &choice);//���߲����ķ�֧
                    switch (choice)
                    {
                    case 1://����ͼ��
                        addBook(); break;
                    case 2: // ��ѯͼ��
                        managerSearchMenu();
                        searchBook(); break;
                    case 3://��ѯ����������
                        searchfeedback();
                        break;
                    case 0:cash_1 = 0; break;
                    default:
                        break;
                    }
                }
                break;
            case 0:
                break;
            default:
                break;
            }

            break;
        case 2:

            registerUser();
            break;
        case 0:
            exit(0);
        default:
            printf("��Ч��ѡ�����������롣\n");
        }
    }

    return 0;
}



//��������


//������ͷ
Bookfile* creathead()
{
    Bookfile* head = (Bookfile*)malloc(sizeof(Bookfile));
    head->next = NULL;
    return head;
}

//�����ڵ�
Bookfile* creatnode(Book newbook)
{
    Bookfile* Newbookfile= (Bookfile*)malloc(sizeof(Bookfile));
    Newbookfile->next = NULL;
    return Newbookfile;
}



//ע�ắ��
int registerUser() {
    int i;
    system("cls");
    User* newUser = (User*)malloc(sizeof(User));
    printf("\n");
    printf("\t|--------------------ͼ�����ϵͳ-------------------------|\n");
    printf("\t|                      ע��ϵͳ                           |\n");
    printf("\t|                    ��ã���ͬѧ��                       |\n");
    printf("\t|                ѧ��:_____________                       |");
    for (i = 0; i < 37; i++)	printf("\b");
    scanf("%s", newUser->id);
    printf("\t|                �˺�:_____________                       |");
    for (i = 0; i < 37; i++)	printf("\b");
    scanf("%s", newUser->name);
    printf("\t|                ����:____________                        |");
    for (i = 0; i < 37; i++)	printf("\b");
    scanf("%s", newUser->password);
    newUser->next = head;
    head = newUser;

    //���û���Ϣ���浽�ļ���
    FILE* fp = fopen("users.txt", "a");
    fprintf(fp, "%s %s\n", newUser->name, newUser->password);
    fclose(fp);

    printf("\t\t\t ע��ɹ����������س�����¼����\n");
    getchar();
    getchar();
}

//��¼����
int loginUser(char* username) {
    char name[20], password[20];
    int result, i;
    system("cls");
    printf("\n");
    printf("\t|--------------------ͼ�����ϵͳ-------------------------|\n");
    printf("\t|                      ��¼ϵͳ                           |\n");
    printf("\t|                �˺�:_____________                       |");
    for (i = 0; i < 37; i++)	printf("\b");
    scanf("%s", name);
    printf("\t|                ����:____________                        |");
    for (i = 0; i < 37; i++)	printf("\b");
    scanf("%s", password);

    //���ļ��ж�ȡ�û���Ϣ����֤
    FILE* fp = fopen("users.txt", "r");
    char file_name[20], file_password[20];
    while (fscanf(fp, "%s %s", file_name, file_password) != EOF) {
        if (strcmp(file_name, name) == 0 && strcmp(file_password, password) == 0) {
            printf("\t\t\t    ��¼�ɹ�������\n");
            strcpy(username, name);
            getchar();
            getchar();
            fclose(fp);
            result = 1;
            return result;
        }
        else if (strcmp("guanli", name) == 0 && strcmp("guanli", password) == 0) {
            printf("\t\t\t   ��ӭ����Ա������\n");
            getchar();
            getchar();
            fclose(fp);
            result = 2;
            return result;
        }
    }
    fclose(fp);
    printf("\t\t    �û���������������������롣\n");
    getchar();
    getchar();
}


//��֤��
void yanzhengma() {
    int code, input, i;
    int try3;
    try3 = 1;
    while (try3 = 1) {

        code = rand() % 9000 + 1000; // generate a random 4-digit code
        printf("\n");
        printf("\t|--------------------ͼ�����ϵͳ-------------------------|\n");
        printf("\t|            Ϊȷ���������࣬��������֤��                 |\n");
        printf("\t|                        %d                             |\n", code);
        printf("\t|              ��֤��:____                                |");
        for (i = 0; i < 37; i++)	printf("\b");
        scanf("%d", &input);
        if (input == code) {

            printf("\t|                 ��֤����ȷ����ӭ����\n");

            break;
        }
        else {
            printf("\t|                 ��֤���������������\n");
        }
    }





}

//����ͼ��
void addBook()//����ͼ��
{
    Book book;
    FILE* fp;
    int i, k = 0;
    struct book* p;
    p = &book;
    
    
    fp = fopen("books.txt", "a+");
    if (fp == NULL) {
        printf("Error opening file\n");
    
    }
    system("cls");
    printf("\n");
    printf("\t|--------------------ͼ�����ϵͳ-------------------------|\n");
    printf("\t|                    ͼ������ϵͳ                         |\n");
    printf("\t|               ISBN��:_____________                      |");
    for (i = 0; i < 36; i++)	printf("\b");
    scanf("%s", book.ISBN);
    printf("\t|                 ����:_____________                      |");
    for (i = 0; i < 36; i++)	printf("\b");
    scanf("%s", book.name);
    printf("\t|                 ����:_____________                      |");
    for (i = 0; i < 36; i++)	printf("\b");
    scanf("%s", book.author);
    printf("\t|               ������:_____________                      |");
    for (i = 0; i < 36; i++)	printf("\b");
    scanf("%s", book.publisher);
    printf("\t|             �������:_____________                      |");
    for (i = 0; i < 36; i++)	printf("\b");
    scanf("%d", &book.year);
    printf("\t|             ����¥��:_____________                      |");
    for (i = 0; i < 36; i++)	printf("\b");
    scanf("%d", &book.floor);
    printf("\t|             �������:_____________                      |");
    for (i = 0; i < 36; i++)	printf("\b");
    scanf("%s", book.shelf);
    printf("\t|                 ����:_____________                      |");
    for (i = 0; i < 36; i++)	printf("\b");
    scanf("%d", &book.borrow);
    printf("\t|                                                         |\n");
    printf("\t|                  1.�������塢ë��˼��                 |\n");
    printf("\t|                  2.��ѧ������ѧ                       |\n");
    printf("\t|                  3.��Ȼ��ѧ                             |\n");
    printf("\t|                  4.��ѧС˵                             |\n");
    printf("\t|                  5.�������                             |\n");
    printf("\t|                  6.����ѧϰ                             |\n");
    printf("\t|                  7.��ʷ                                 |\n");
    printf("\t|                  8.��Ϣ����                             |\n");
    printf("\t|                  9.�ڿ���־                             |\n");
    printf("\t|                                                         |\n");
    printf("\t|             ͼ�����:_____________                      |");
    for (i = 0; i < 36; i++)	printf("\b");
    scanf("%d", &book.lei);
    outlei(p);
    booknum++;
    fprintf("%d\n", booknum);
    for (i = 0; i < booknum-1; i++)
    {
        fprintf(fp, "%s %s %s %s %d %s %d %d %d %s\n", bookfile[i].ISBN, bookfile[i].name, bookfile[i].author, bookfile[i].publisher, bookfile[i].year, bookfile[i].shelf, bookfile[i].floor, bookfile[i].borrow, bookfile[i].lei, bookfile[i].leiname);
    }
    fprintf(fp, "%s %s %s %s %d %s %d %d %d %s\n", book.ISBN, book.name, book.author, book.publisher, book.year, book.shelf, book.floor, book.borrow,book.lei,book.leiname);
    printf("\t\t\t   ͼ����ӳɹ�������\n");
    printf("\t\t\t   ���س�������������\n");
    getchar();
    getchar();



    fclose(fp);

}

//ɾ��ͼ��
void deleteBook()//ɾ��ͼ��
{

}


//����ͼ��
void borrowBook(char* username)//����ͼ��
{
    char bookname[20];
    char bookauthor[15];
    char bookpublisher[20];
    int bookyear;
    Book book;
    FILE* fp;
    FILE* file;
    int i = 0, k = 0, door = 0;


    //// ���ļ��Զ�ȡ�ṹ������
    //file = fopen("books.txt", "rb");
    //int found = 0;

    fp = fopen("books.txt", "r");

    if (fp == NULL) {
        printf("Error opening file\n");

    }
    int readerid;

    system("cls");
    printf("\n");
    printf("\t|             ��������:_____________                      |");
    for (i = 0; i < 36; i++)	printf("\b");
    scanf("%s", bookname);
    printf("\t|                 ����:_____________                      |");
    for (i = 0; i < 36; i++)	printf("\b");
    scanf("%s", bookauthor);
    printf("\t|               ������:_____________                      |");
    for (i = 0; i < 36; i++)	printf("\b");
    scanf("%s", bookpublisher);
    printf("\t|             �������:_____________                      |");
    for (i = 0; i < 36; i++)	printf("\b");
    scanf("%d", &bookyear);
    i = 0;
    
    while (fscanf(fp, "%s %s %s %s %d %s %d %d %d %s\n", &bookfile[i].ISBN, bookfile[i].name, bookfile[i].author, bookfile[i].publisher, &bookfile[i].year, &bookfile[i].shelf, &bookfile[i].floor, &bookfile[i].borrow, &bookfile[i].lei, bookfile[i].leiname) != EOF)
    {
        i++;

    }
    for (i = 0; i < MAXBOOKS; i++)
    {
        if (strcmp(bookfile[i].ISBN, "\0") != 0)    k++;
        else continue;
    }
    for (i = 0; i < k; i++)
    {   
        
    
        if ((strcmp(bookfile[i].name, bookname) == 0) &&
            (strcmp(bookfile[i].author, bookauthor) == 0) &&
            (strcmp(bookfile[i].publisher, bookpublisher) == 0) &&
            (bookfile[i].year == bookyear))
        {
            if (bookfile[i].borrow >= 1) {
                printf("\n");
                printf("\t|                 ISBN��%s\n", bookfile[i].ISBN);
                printf("\t|             ����������%s\n", bookfile[i].name);
                printf("\t|                 ����: %s\n", bookfile[i].author);
                printf("\t|               ������: %s\n", bookfile[i].publisher);
                printf("\t|             �������: %d\n", bookfile[i].year);
                printf("\t|             �������: %s\n", bookfile[i].shelf);
                printf("\t|             ����¥��: %d\n", bookfile[i].floor);
                bookfile[i].borrow--;
                printf("\t|             ʣ������: %d\n", bookfile[i].borrow);

                strcpy(book.ISBN, bookfile[i].ISBN);
                strcpy(book.name, bookfile[i].name);
                strcpy(book.author, bookfile[i].author);
                strcpy(book.publisher, bookfile[i].publisher);
                book.year = bookfile[i].year;
                strcpy(book.shelf, bookfile[i].shelf);
                book.floor = bookfile[i].floor;
                
                


                fclose(fp);
                fp = fopen("books.txt", "w");
                

                for (i = 0; i < k; i++)
                    fprintf(fp, "%s %s %s %s %d %s %d %d %d %s\n", bookfile[i].ISBN, bookfile[i].name, bookfile[i].author, bookfile[i].publisher, bookfile[i].year, bookfile[i].shelf, bookfile[i].floor, bookfile[i].borrow, bookfile[i].lei, bookfile[i].leiname);

                fclose(fp);

                // ��¼������Ϣ���ļ�
                char filename[50];
                sprintf(filename, "reader_%s.txt", username);
                FILE* fp_name = fopen(filename, "a");
                fprintf(fp_name, "%s %s %s %s %d %s %d ����\n", book.ISBN, book.name, book.author, book.publisher, book.year, book.shelf, book.floor);

                fclose(fp_name);
                printf("\t|             ���ĳɹ�������\n");
                printf("\t|             ���س�����������");
                system("pause");

            }
            else if (bookfile[i].borrow == 0) {
                printf("\t|             ��Ǹ�������ѽ������\n");
                fclose(fp);
                system("pause");
                return;

            }
            door = 1;

            break;


        }

     

    }
    if(!door)
    {
        printf("\t|             ��Ǹ��δ�ҵ����顭��\n");
        system("pause");
        return;
    }
}


//�黹ͼ��
void returnBook(char* username)//�黹ͼ��
{
    char bookname[20];
    char bookauthor[15];
    char bookpublisher[20];
    int bookyear;
    int choice;
    Book book;
    FILE* fp;
    FILE* file;
    int i = 0, k = 0;


    //// ���ļ��Զ�ȡ�ṹ������
    //file = fopen("books.txt", "rb");
    //int found = 0;

    fp = fopen("books.txt", "r");

    if (fp == NULL) {
        printf("Error opening file\n");

    }
    int readerid;

    system("cls");
    printf("\n");
    printf("\t|             �黹����:_____________                      |");
    for (i = 0; i < 36; i++)	printf("\b");
    scanf("%s", bookname);
    printf("\t|                 ����:_____________                      |");
    for (i = 0; i < 36; i++)	printf("\b");
    scanf("%s", bookauthor);
    printf("\t|               ������:_____________                      |");
    for (i = 0; i < 36; i++)	printf("\b");
    scanf("%s", bookpublisher);
    printf("\t|             �������:_____________                      |");
    for (i = 0; i < 36; i++)	printf("\b");
    scanf("%d", &bookyear);
    i = 0;

    while (fscanf(fp, "%s %s %s %s %d %s %d %d %d %s\n", &bookfile[i].ISBN, bookfile[i].name, bookfile[i].author, bookfile[i].publisher, &bookfile[i].year, &bookfile[i].shelf, &bookfile[i].floor, &bookfile[i].borrow, &bookfile[i].lei, bookfile[i].leiname) != EOF)
    {
        i++;

    }
    for (i = 0; i < MAXBOOKS; i++)
    {
        if (strcmp(bookfile[i].ISBN, "\0") != 0)    k++;
        else continue;
    }
    for (i = 0; i < k; i++)
    {


        if ((strcmp(bookfile[i].name, bookname) == 0) &&
            (strcmp(bookfile[i].author, bookauthor) == 0) &&
            (strcmp(bookfile[i].publisher, bookpublisher) == 0) &&
            (bookfile[i].year == bookyear))
        {

            printf("\n");
            printf("\t|                 ISBN��%s\n", bookfile[i].ISBN);
            printf("\t|             ����������%s\n", bookfile[i].name);
            printf("\t|                 ����: %s\n", bookfile[i].author);
            printf("\t|               ������: %s\n", bookfile[i].publisher);
            printf("\t|             �������: %d\n", bookfile[i].year);
            printf("\t|             �������: %s\n", bookfile[i].shelf);
            printf("\t|             ����¥��: %d\n", bookfile[i].floor);
            bookfile[i].borrow++;
            printf("\t|             ʣ������: %d\n", bookfile[i].borrow);

            strcpy(book.ISBN, bookfile[i].ISBN);
            strcpy(book.name, bookfile[i].name);
            strcpy(book.author, bookfile[i].author);
            strcpy(book.publisher, bookfile[i].publisher);
            book.year = bookfile[i].year;
            strcpy(book.shelf, bookfile[i].shelf);
            book.floor = bookfile[i].floor;




            fclose(fp);
            fp = fopen("books.txt", "w");


            for (i = 0; i < k; i++)
                fprintf(fp, "%s %s %s %s %d %s %d %d %d %s\n", bookfile[i].ISBN, bookfile[i].name, bookfile[i].author, bookfile[i].publisher, bookfile[i].year, bookfile[i].shelf, bookfile[i].floor, bookfile[i].borrow, bookfile[i].lei, bookfile[i].leiname);

            fclose(fp);

            // ��¼������Ϣ���ļ�
            char filename[50];
            sprintf(filename, "reader_%s.txt", username);
            FILE* fp_name = fopen(filename, "a");
            fprintf(fp_name, "%s %s %s %s %d %s %d �黹\n", book.ISBN, book.name, book.author, book.publisher, book.year, book.shelf, book.floor);
            fclose(fp_name);
            printf("\t|             �黹�ɹ�������\n");



            // ��д�������ļ� 
            printf("\t|             �Ƿ���д������\n");
            printf("\t|             ��1  ��\n");
            printf("\t|             ��2  ��\n");
            printf("\t|             �����루1 - 2����");
            scanf("%d", &choice);
            char review[255];
            char time[15];
            int score;
            switch (choice)
            {
            case 1:
                

                
                system("cls");
                printf("���ڣ�20XX��XX��XX�գ���");
                scanf("%s", time);
                printf("���֣�");
                scanf("%d", &score);
                printf("����:\n");
                getchar();
                fgets(review, 255, stdin);
                char bookreview[50];
                sprintf(bookreview, "%s.txt", bookname);
                FILE* fp_review = fopen(bookreview, "a");

                fprintf(fp, "%s\t%s ���֣�", time, username);
                for (i = 0; i < score; i++)    fprintf(fp, "��");
                fprintf(fp, "\n    %s\n\n", review);
                fclose(fp_review);
                printf("������д�ɹ������س�����������");
                getchar();
                break;
                //case 2:
                //    break;

                //default:
                //    break;
            }

            break;
        }


      

        else {
                printf("\t|             ��Ǹ��δ�ҵ����顭��\n");
                getchar();
            }

           

        
    }
}

//������ѯͼ��
void namesearchBook()//������ѯͼ��
{
    char name[50];
    Book book;
    FILE* fp;
    int found = 0;
    int i;

    fp = fopen("books.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");

    }

    printf("\t|                 ����:_____________                      |");
    for (i = 0; i < 36; i++)	printf("\b");
    scanf("%s", &name);

    while (fscanf(fp, "%s %s %s %s %d %s %d %d", book.ISBN, book.name, book.author, book.publisher, &book.year, book.shelf, &book.floor, &book.borrow) != EOF) {
        getchar();
        if (strcmp(book.name, name) == 0) {
            printf("\t|                   ISBN��: %s\n", book.ISBN);
            printf("\t|                     ����: %s\n", book.name);
            printf("\t|                     ����: %s\n", book.author);
            printf("\t|                   ������: %s\n", book.publisher);
            printf("\t|                 �������: %d\n", book.year);
            printf("\t|                 �������: %s\n", book.shelf);
            printf("\t|                 ����¥��: %d\n", book.floor);
            printf("\t|                 ʣ������: %d\n", book.borrow);
            found = 1;
            printf("\t|                 ���س�����������");
            getchar();
            break;
        }
    }

    if (!found) {
        printf("\t|                 ��Ǹ��û�в�ѯ�����顭��\n");
        printf("\t|                 ���س�����������");
        getchar();
    }

    fclose(fp);
}

//ISBN��ѯͼ��
void ISBNsearchBook()//ISBN��ѯͼ��
{
    char id[14];
    Book book;
    FILE* fp;
    int found = 0;
    int i;

    fp = fopen("books.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");

    }

    printf("\t|                 ISBN��:_____________                      |");
    for (i = 0; i < 36; i++)	printf("\b");
    scanf("%s", id);

    while (fscanf(fp, "%s %s %s %s %d %s %d %d", book.ISBN, book.name, book.author, book.publisher, &book.year, &book.shelf, &book.floor, &book.borrow) != EOF) {
        getchar();
        if (strcmp(book.ISBN, id) == 0) {
            printf("\t|                   ISBN��: %s\n", book.ISBN);
            printf("\t|                     ����: %s\n", book.name);
            printf("\t|                     ����: %s\n", book.author);
            printf("\t|                   ������: %s\n", book.publisher);
            printf("\t|                 �������: %d\n", book.year);
            printf("\t|                 �������: %s\n", book.shelf);
            printf("\t|                 ����¥��: %d\n", book.floor);
            printf("\t|                 ʣ������: %d\n", book.borrow);
            found = 1;
            printf("\t|                 ���س�����������");
            getchar();


            break;
        }
    }

    if (!found) {
        printf("\t|                 ��Ǹ��û�в�ѯ�����顭��\n");
        printf("\t|                 ���س�����������");
        getchar();
    }

    fclose(fp);
}

//ͼ���ѯ
void searchBook()
{
    int choice;

    scanf("%d", &choice);
    switch (choice)
    {
    case 1:namesearchBook(); break;
    case 2:ISBNsearchBook(); break;
    case 3:mohu(); break;
    case 0:break;
    default:
        break;
    }
}

//������ѯ
void bookreview()
{
    FILE* fp;
    char bookreviewname[100] = { '\0' };
    char line[100];
    fp = NULL;

    printf("������������");
    scanf("%s", bookreviewname);
    strcat(bookreviewname, ".txt");
    fp = fopen(bookreviewname, "r");

    if (fp == NULL)
    {
        printf("�޷����ļ�\n");
    }
    system("cls");
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        printf("%s", line);
    }

    fclose(fp);
    system("pause");

}

//���߽���
void ReaderMenu()
{
    system("cls");
    printf("\n");
    printf("\t|-----------------%sͬѧ����ӭ����---------------------|\n", username);
    printf("\t|                    ����ҳ��ϵͳ                        |\n");
    printf("\t|                       ���˵�                           |\n");
    printf("\t|                  ��1   ͼ�����                         |\n");
    printf("\t|                  ��2   ͼ��黹                         |\n");
    printf("\t|                  ��3   ͼ���ѯ                         |\n");
    printf("\t|                  ��4   ������ѯ                         |\n");
    printf("\t|                  ��5   ����ϵͳ                         |\n");
    printf("\t|                  ��6   ����Ƽ�                         |\n");
    printf("\t|                  ��7   �����Ƽ�                         |\n");
    printf("\t|                  ��8   ���Ի��Ƽ�                       |\n");
    printf("\t|                  ��9   ����������                       |\n");
    printf("\t|                  ��10  ͼ�����Ϣ���������ǣ�           |\n");
    //printf("\t|                  ��8   ͼ��������а�                     |\n");
    //printf("\t|                  ��9   �������а�                         |\n");
    printf("\t|                  ��0   �˳�ϵͳ                         |\n");
    printf("\t|--------------------------------------------------------|\n");
    printf("\n");
    printf("\t\t��ѡ��0-9����");
}

//����Ա����
void ManagerMenu()//����Ա����
{
    system("cls");
    printf("\n");
    printf("\t|-----------------�𾴵Ĺ���Ա����ӭ����-------------------|\n");
    printf("\t|                    ͼ�����ϵͳ                          |\n");
    printf("\t|                       ���˵�                             |\n");
    printf("\t|                  ��1   ����ͼ��                           |\n");
    printf("\t|                  ��2   ��ѯͼ��                           |\n");
    printf("\t|                  ��3   �鿴����������                     |\n");
    printf("\t|                  ��0   �����ϼ�                           |\n");
    printf("\n");
    printf("\t\t��ѡ��0-3����");
}

//�û���ѯͼ��ҳ��
void userSearchMenu()
{
    system("cls");
    printf("\n");
    printf("\t|-----------------%sͬѧ����ӭ����---------------------|\n", username);
    printf("\t|                    ͼ���ѯϵͳ                        |\n");
    printf("\t|                       ���˵�                           |\n");
    printf("\t|                  ��1 ������ѯ                           |\n");
    printf("\t|                  ��2 ISBN��ѯ                           |\n");
    printf("\t|                  ��3 ģ����ѯ                           |\n");
    printf("\t|                  ��0 �����ϼ�                           |\n");
    printf("\n");
    printf("\t\t��ѡ��0-2����");

}

//����Ա��ѯͼ��ҳ��
void managerSearchMenu()
{
    system("cls");
    printf("\n");
    printf("\t|-----------------�𾴵Ĺ���Ա����ӭ����-----------------|\n");
    printf("\t|                    ͼ���ѯϵͳ                        |\n");
    printf("\t|                       ���˵�                           |\n");
    printf("\t|                  ��1 ������ѯ                           |\n");
    printf("\t|                  ��2 ISBN��ѯ                           |\n");
    printf("\t|                  ��0 �����ϼ�                           |\n");
    printf("\n");
    printf("\t\t��ѡ��0-2����");

}

//��ʼ�˵�
void BeginMenu()//��ʼ�˵�
{
    system("cls");/*��������*/
    printf("\n");
    printf("\t|-----------------------��ӭ����--------------------------|\n");
    printf("\t|                     ͼ�����ϵͳ                        |\n");
    printf("\t|                        ���˵�                           |\n");
    printf("\t|                 ��1     ��¼                             |\n");
    printf("\t|                 ��2     ע��                             |\n");
    printf("\t|                 ��0     �˳�                             |\n");
    printf("\t|---------------------------------------------------------|\n");
    printf("\n");
    printf("\t\t��ѡ��0-2����");
}


//���ɲ˵�
void dayi()
{
    int flag = 1;
    while (flag)
    {
        system("cls");
        printf("\n");
        printf("\t|----------------------%sͬѧ����ӭ����---------------------|\n", username);
        printf("\t|                        ����ϵͳ                          |\n");
        printf("\t|                      ��ѡ���������                      |\n");
        printf("\t|                  ��1   ͼ������δ�黹                     |\n");
        printf("\t|                  ��2   ���ĵ�ͼ�鶪ʧ����               |\n");
        printf("\t|                  ��3   ͼ�����ϵͳ���ֹ���               |\n");
        printf("\t|                  ��0   ������һ��                         |\n");
        int choice;
        printf("\n");
        printf("\t\t��ѡ��0-3����");
        scanf("%d", &choice);
        switch (choice)
        {
        case(1):
            system("cls");
            printf("\n");
            printf("\t|       ���������                                                          |\n");
            printf("\t|          �뵽һ¥������ѯ���ҵ�ͼ�����Ա���еǼǹ黹�����������ɽ�             \n\t        ���ֲ��������޵�������Ϊ                                            |\n");
            printf("\t|                                 (���س������ء���)                          |\n");
            getchar();
            getchar();
            break;
        case(2):
            system("cls");
            printf("\n");
            printf("\t|       ���������                                                                           |\n");
            printf("\t|       1.����鿯�𻵣�����Ա���������󣬸�������̶Ȳ�ͬ�����չ涨�����⳥                 |\n");
            printf("\t|       2.����鿯��ʧ��������ͬ��������ͬ���ߡ���ͬ�汾��ͼ������⳥������\n\t     ��Ŀ��Ϣ�������ķ���̨��ѯ                                                              |\n");
            printf("\t|                                 (���س������ء���)                                           |\n");
            getchar();
            getchar();
            break;
        case(3):
            system("cls");
            printf("\n");
            printf("\t|       ���������                                                                   |\n");
            printf("\t|                      ��γ����޹������µ�ͼ��ݼ�����Ա���й����޸�                |\n");
            printf("\t|                        �������ŷ�ʦ��     ��ϵ�绰��13960605609                    |\n");
            printf("\t|                                 (���س������ء���)                                   |\n");
            getchar();
            getchar();
            break;
        case(0):
            flag = 0;
        default:
            printf("��Ч��ѡ�����������롣\n");
        }
    }

}


//�����Ƽ�
void tuijian()
{

    system("cls");
    printf("\n");
    printf("\t|                          �����Ƽ�                         |\n");
    printf("\t|���ܺ����Ƽ��������š�                                     |\n");
    printf("\t|���ݼ�飺                                                 |\n");
    printf("\t| �����š�����һ����һ���Ĺ��£�����һ�����������ɣ��ĥ��  |\n");
    printf("\t|  ���˵���������,��һĻ�����������Ѿ�����Ϸ�硣            |\n");
    printf("\t|�Ƽ����ɣ�                                                 |\n");
    printf("\t|  �����ñ���ıʵ�����˵�Ÿ��󱯲ҵ�һ���������侲��̬�� |\n");
    printf("\t|  ���Կ���������֮ǿ�������˹����ҵľ�����������ʱ������ |\n");
    printf("\t|  ����û�����ǣ��������ÿ���˵�������ʱ��������Ʒ������δ |\n");
    printf("\t|  ��ìͷֱָʱ��������ͨ����Щ�ʻ�����ӣ���ʱ������չ�ָ� |\n");
    printf("\t|  ���ǿ���                                                 |\n");
    system("pause");
}

void suijisearchBook()//���ѡ�� 
{

    Book book;
    FILE* fp;
    FILE* file;

    int i, k;

    i = 0;
    k = rand() % 5; // generate a random number between 1 and 9


    fp = fopen("books.txt", "r");

    if (fp == NULL) {
        printf("Error opening file\n");

    }

    fp = fopen("books.txt", "r");

    if (fp == NULL) {
        printf("Error opening file\n");

    }

    while (fscanf(fp, "%s %s %s %s %d %s %d %d\n", &bookfile[i].ISBN, bookfile[i].name, bookfile[i].author, bookfile[i].publisher, &bookfile[i].year, &bookfile[i].shelf, &bookfile[i].floor, &bookfile[i].borrow) != EOF)
    {
        getchar();
        i++;
        if (i >= length)  break;
    }
    printf("Ϊ������Ƽ�����ͼ��\n");
    printf("ISBN: %s\n", bookfile[k].ISBN);
    printf("����: %s\n", bookfile[k].name);
    printf("����: %s\n", bookfile[k].author);
    printf("������: %s\n", bookfile[k].publisher);
    printf("�������: %d\n", bookfile[k].year);
    printf("�������: %s\n", bookfile[k].shelf);
    printf("����¥��: %d\n", bookfile[k].floor);
    printf("ʣ������: %d\n", bookfile[k].borrow);
    fclose(fp);
    system("pause");
}

void gexinghua()
{
    system("cls");
    int seeklei=0;
    char seekname[100];

    printf("\t|              ��������ϲ�������                       |\n");
    printf("\t|                                                         |\n");
    printf("\t|                  1.�������塢ë��˼��                 |\n");
    printf("\t|                  2.��ѧ������ѧ                       |\n");
    printf("\t|                  3.��Ȼ��ѧ                             |\n");
    printf("\t|                  4.��ѧС˵                             |\n");
    printf("\t|                  5.�������                             |\n");
    printf("\t|                  6.����ѧϰ                             |\n");
    printf("\t|                  7.��ʷ                                 |\n");
    printf("\t|                  8.��Ϣ����                             |\n");
    printf("\t|                  9.�ڿ���־                             |\n");
    printf("\t|                                                         |\n");
    scanf("%d",&seeklei);
        switch (seeklei)
    {
    case 1:
        strcpy(seekname, "�������塢ë��˼��");
        break;
    case 2:
        strcpy(seekname, "��ѧ������ѧ");
        break;
    case 3:
        strcpy(seekname, "��Ȼ��ѧ");
        break;
    case 4:
        strcpy(seekname, "��ѧС˵");
        break;
    case 5:
        strcpy(seekname, "�������");
        break;
    case 6:
        strcpy(seekname, "����ѧϰ");
        break;
    case 7:
        strcpy(seekname, "��ʷ");
        break;
    case 8:
        strcpy(seekname, "��Ϣ����");
        break;
    case 9:
        strcpy(seekname, "�ڿ���־");
        break;
    default:
        break;
    }
         FILE* file = fopen("books.txt", "r");
    if (file == NULL)
    {
        printf("error");
    }
     char line[256];
    int linecount = 0;
    printf("�����\"%s\"�����У�\n", seekname);
    printf("ISBN�� ���� ���� ������ ������� ������� ����¥�� ʣ������\n");
    while (fgets(line, sizeof(line), file)) {
        //
        if (strstr(line, seekname) != NULL) {
            printf("%s", line);
        }
        linecount++;
    }
	system("pause");
    
    

}

//ģ����ѯ

void mohu()
{
    system("cls");
    char seek[100];
    printf("������ؼ���:\n");
    scanf("%s", seek);

    FILE* file = fopen("books.txt", "r");
    if (file == NULL)
    {
        printf("error");
    }

    char line[256];
    int linecount = 0;
    printf("�����ؼ���\"%s\"���飺\n", seek);
    printf("ISBN�� ���� ���� ������ ������� ������� ����¥�� ʣ������\n");

    while (fgets(line, sizeof(line), file)) {
        //
        if (strstr(line, seek) != NULL) {
            printf("%s", line);
        }
        linecount++;
    }
    system("pause");
}

void outlei(struct book *p)
{
    switch (p->lei)
    {
    case 1:
        strcpy(p->leiname, "�������塢ë��˼��");
        break;
    case 2:
        strcpy(p->leiname, "��ѧ������ѧ");
        break;
    case 3:
        strcpy(p->leiname, "��Ȼ��ѧ");
        break;
    case 4:
        strcpy(p->leiname, "��ѧС˵");
        break;
    case 5:
        strcpy(p->leiname, "�������");
        break;
    case 6:
        strcpy(p->leiname, "����ѧϰ");
        break;
    case 7:
        strcpy(p->leiname, "��ʷ");
        break;
    case 8:
        strcpy(p->leiname, "��Ϣ����");
        break;
    case 9:
        strcpy(p->leiname, "�ڿ���־");
        break;
    default:
        break;
    }
}


//��������ģ��
void feedback()
{
    int i;
    FILE* fp = fopen("feedback.txt", "a");
    char opinion[255];
    char time[15];
    system("cls");
    printf("\n");
    printf("\t|-----------------%sͬѧ����ӭ����---------------------|\n", username);
    printf("\t|                   ����������ϵͳ                   |\n");
    printf("\t|     ���ڣ�20XX��XX��XX�գ�:______________");
    for (i = 0; i < 14; i++)	printf("\b");
    scanf("%s", time);
    printf("\t|     ����������:\n");
    printf("\t|         ");
    getchar();
    fgets(opinion, 255, stdin);
    fprintf(fp, "%s\t%s��\n%s\n\n", time, username, opinion);
    fclose(fp);
    printf("\t|                                                    | \n");
    printf("\t|     ������������д�ɹ������س�����������             |\b\b\b\b\b");
    getchar();
}

//����Ա�鿴����������
void searchfeedback()
{
    FILE* fp;
    char line[100];
    fp = NULL;
    fp = fopen("feedback.txt", "r");

    if (fp == NULL)
    {
        printf("�޷����ļ�\n");
    }
    system("cls");
    printf("\n");
    printf("����Ϊ���ڵ����з��������ۣ�\n");
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        printf("%s", line);
    }
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    fclose(fp);
    printf("չʾ��ϣ����س���������");
    system("pause");
}


//��ά��
void erweima()
{
    FILE* fp;
    char line[205];
    fp = fopen("ascii-art.txt", "r");//QR_Code.txtΪ��ά����ļ���

    if (fp == NULL)
    {
        printf("�޷����ļ�\n");
    }
    system("cls");
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        printf("%s", line);
    }

    fclose(fp);

    system("pause");
    getchar();

}