#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
COORD coord = {0,0}; /// top-left corner of window

/**
    function : gotoxy
    @param input: x and y coordinates
    @param output: moves the cursor in specified position of console
*/
void gotoxy(int x,int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

struct book
{ /// Structure to hold all the book related information
	char bname[30];
	char barcode[10];
	char author[30];
	char publication[30];
	int issuedflag;
	char issuedto[30];

}b;
/// all functions used in the program are declared here
void Login(void);
void AddBook(void);
void AddMember(void);
void listbook(void);
void listmembers(void);
void DeleteBook(void);
void DeleteMember(void);
void IssueBook(void);
void ReturnBook(void);
void listissued(void);
void listunissued(void);
void Export(void);

struct student
{ /// structure to hold all the student data
	char name[30];
	char stid[20];
	int fine;
	int bookcount=0;


}s;
FILE *fp, *fpt, *fq, *fqt, *fr;   /// fp and fq are main file FILE pointer and fpt and fqt are temp files which are used to delete 
								 /// any record from main file , fr is pointer used to export to txt file;
		char bcode[10];          /// universal barcode variable used to take input from user
		char another,sid[20],isIssued[20];   /// isissued provide 'string' version of issue status
		long int recordsize1=sizeof(b);     
		long int recordsize2=sizeof(s);     /// size of structure records used in binary data file

void login()
{
	int a=0,i=0;
	char uname[10],c=' ';
	char password[20];
	//char user[10]="lol";
	//char pass[20]="lul";
while(a<=2)
{
	///printf("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
	gotoxy(89,20);
	printf("\n\t\t\t\t\t::::::::::::::::::::::::::  LOGIN FORM  :::::::::::::::::::::::::: \n\n");
	printf("               \t\t\t\t\tUSERNAME :-");
	scanf("%s",&uname);
	printf("               \t\t\t\t\tPASSWORD :-");
    //scanf("%s", &password);
	//gets(password);
	while(i<10)
	{
	    password[i]=getch();
	    c=password[i];
	    if(c==13) break;
	    else printf("*");
	    i++;
	}
	password[i]='\0';
	i=0;


	if(strcmp(uname,"lms") ^ strcmp(password,"lms"))

	{
	printf("\n        SORRY !!!!  LOGIN IS UNSUCESSFUL");
		a++;


	}
	else
	{
		printf("\n\n\n\n\t\t\t\t\tWELCOME TO THE LIBRARY MANAGEMENT SYSTEM\n\t\t\t\t\tLOGIN IS SUCCESSFUL");
	    printf("\n                LOADING PLEASE WAIT... \n");
    for(i=0; i<100; i++)
    {
        printf(".");
        Sleep(10);


    }
    fflush(stdin);
	printf("\n\n\n\t\t\t\tPress any key to continue...");
	getchar();
	break;
	}
}

	if (a>2)
	{
		printf("\n SORRY YOU HAVE ENTERED WRONG USERNAME AND PASSWORD MULTIPLE TIMES !!!!");
		printf("Press any key to exit.......");
		getchar();
		exit(1);

		}
}

int main(){

		login();
		system("cls");

		fq=fopen("DATA2.DAT","rb+");
		if(fq==NULL)
		{
		fq=fopen("DATA2.DAT","wb+");
		if(fq==NULL)
		{
			printf("CANNOT OPEN BOOKS FILE");
			exit(1);
		}
		}

		fp=fopen("DATA1.DAT","rb+");
		if(fp==NULL)
		{
		fp=fopen("DATA1.DAT","wb+");
		if(fp==NULL)
		{
			printf("CANNOT OPEN BOOKS FILE");
			exit(1);
		}
		}




		while(1){
		///system("cls");
        //gotoxy(51,65);
        
		printf("\n\n\t\t\t\t\t\t\t\t\tLIBRARY MANAGEMENT SYSTEM\n");
        printf ( "\t\t1. For adding a book\n\t\t2. for adding a student\n");
        printf ( "\t\t3. Issue a Book\n\t\t4. for Return Book\n\t\t5. List Books\n");
        printf ( "\t\t6. List Issued Books\n\t\t7. display students\n\t\t8. delete student \n\t\t9. Delete Book\n ");
		printf ( "\n \t\t\tPress'e' for Exit  \t\t\t\tPress'c' for Clear Screen  \t\t\t\tPress't' to export data \n");
        printf("\tchoice: ");
        fflush(stdin);
        char choice=getchar();


		switch(choice){

			case'1':
				AddBook();
			break;

			case'2':
				AddMember();
			break;

			case '9':{
				DeleteBook();
			break;}

			case '3':{
				IssueBook();
			break;}

			case '4':{
				ReturnBook();
				break;
				}

			case '5':{
				listbook();
			break;}

			case '7':
				listmembers();
			break;

			case '8':
				DeleteMember();
				break;

			case '6':
				listissued();
				break;


			case 'e':
				exit(1);
				break;
            case 'c':
                system("cls");
                break;
            case 't':
                //Export();
                //break;
               //system("clear");
        //puts("Press \n 1. To Export All Book list \n 2. To Export all Student List \n 3. To return to previous Menu\n");
//        fflush(stdin);
//        scanf("%c",&achoice);
//            switch(choice)
//        {
//                case '1':
//                {
//                    puts("Now exporting all the book records\n");
                    rewind(fp);
                   fr=fopen("Book list.txt","w+");
                    fprintf(fr,"Name \t\t Barcode \t\tAuthor \t\tPublication \t\tIssued Status \t\t Issued To \n");
                    while(fread(&b,recordsize1,1,fp)==1){
                            fprintf(fr,"-----------------------------------------------------------------------------------------------\n");
                            fprintf(fr,"%s \t\t  %s \t\t\t  %s \t\t\t  %s \t\t\t\t  %d \t\t  %s \n",b.bname,b.barcode,b.author,b.publication,b.issuedflag,b.issuedto);

                            }
                    puts("Exporting Book records, please wait\n");
                    for(int i=0;i<250;i++){
                    		printf(".");
                    		Sleep(10);
					}

                    if(fr==NULL){
                        puts("\nCan not export Any Record. Please try again\n");
                        }
                    else
                        puts("\nRecors exported successfully, check 'book list.txt'. \n");

                    fclose(fr);

					puts("Exporting student records, please wait\n");
                    for(int i=0;i<250;i++){
                    		printf(".");
                    		Sleep(10);
					}

                    rewind(fq);
                    fr=fopen("Student list.txt","w+");
                    fprintf(fr,"Name \t\t Student Id\t\tBooks issued \t\t Fine \n");
                    while(fread(&s,recordsize2,1,fq)==1){
                            fprintf(fr,"--------------------------------------------------------------------------------------\n");
                            fprintf(fr,"%s \t %s \t\t\t %d \t\t\t%d\n",s.name,s.stid,s.bookcount,s.fine);

                            }

                    if(fr==NULL){
                        puts("\nCan not export Any Record. Please try again\n");
                        }
                    else
                        puts("\nRecors exported successfully, check 'student list.txt'. \n");

                    fclose(fr);
                    fflush(stdin);
                    printf("\n\n\n\t\t\t\tPress any key to continue...");
                    getchar();

                    break;

//                }
//                case 'r':
//                    system("clear");
//                    //return;
//
//                default:
//                        puts("Select a correct choice\n");
//
//        }
//        break;

            case 's':
            /// list source code
                puts("ENterd in source code view\n");
                FILE *file;
                char c;
                file=fopen(__FILE__,"r");
                do{
                    c=getc(file);
                    printf("%c",c);
                    }
                while(c!=EOF);

                fclose(file);
                fflush(stdin);
                printf("\n\n\n\t\t\t\tPress any key to continue...");
                getchar();
            break;


			default:
			printf("Plese select the appropritate option");
			}

			}
		fflush(stdin);
		}


void AddBook(){
		fseek(fp,0,SEEK_END);
				another='y';
				while(another=='y')
				{
					printf("\n BOOK NAME");
					scanf("%s",&b.bname);
					printf("\n BARCODE-");
					scanf("%s",&b.barcode);
					printf("\n AUTHOR-");
					scanf("%s",&b.author);
					printf("\n PUBLICATION");

					//gets(b.publication);
					scanf("%s",&b.publication);
					fwrite(&b,recordsize1,1,fp);
					b.issuedflag=0;


					printf("\nBook successfully Added to the Database.\n");
					Sleep(500);
					printf("\n ENTER ANOTHER RECORD(y/n):");
					fflush(stdin);
					//another=getchar();
					scanf("%c",&another);
					///printf("\n\n\n");
				}
}
void AddMember(){
		
		fseek(fq,0,SEEK_END);
				another='y';
				while(another=='y')
				{
					printf("\n STUDENT NAME ");
					scanf("%s",&s.name);
					printf("\n STUDENT ID ");
					scanf("%s",&s.stid);

					fwrite(&s,recordsize2,1,fq);

					printf("\nStudent successfully Added to the Database.\n");
					Sleep(500);
					//flush(stdin);
					printf("\n ENTER ANOTHER RECORD(y/n): ");
					fflush(stdin);
					//another=getchar();
					scanf("%c",&another);
					///printf("\n\n\n");
				}
}

void listmembers(){

///display students
				printf("\t\t\t\t\t\tStudents list LIST\n\n");
				rewind(fq);
				printf("_______________________________________________________________________________________________________________________\n");
				printf("NAME\t\tSTUDENT ID \t\t ISSUED BOOKS \t\t Fine\n");
				while(fread(&s,recordsize2,1,fq)==1)
				{
					printf("\n-------------------------------------------------------------------------------------------\n");
					printf("%s\t\t%s\t\t\t   %d\t\t\t  %d",s.name,s.stid,s.bookcount,s.fine);
					printf("\n-------------------------------------------------------------------------------------------\n");
				}
				printf("\n PRESS ENTER FOR MAIN WINDOW:");
				fflush(stdin);
				///another=getchar();
                scanf("%c",&another);
}

void DeleteBook(){
		another='y';
					while(another=='y')
					{
						printf("\n ENTER THE BARCODE OF BOOK TO DELETE:  ");
						scanf("%s",&bcode);
						fpt=fopen("temp.DAT","wb");//create the temporary file
						rewind(fp);
						while(fread(&b,recordsize1,1,fp)==1)
						{
							if(strcmp(b.barcode,bcode)!=0)//if the entered record match
							{
								fwrite(&b,recordsize1,1,fpt);//move all the record except the deleted one
							}
						}
						fclose(fp);
						fclose(fpt);
						remove("DATA1.DAT");
						rename("temp.DAT","DATA1.DAT");
						fp=fopen("DATA1.DAT","rb+");
						printf("\nBook successfully Deleted from the Database.\n");
						Sleep(500);
						printf("DELETE ANOTHER REOCRD(yes/no):");
						fflush(stdin);
						///another=getchar();
						scanf("%c",&another);
					}
}
void DeleteMember(){
			another='y';
					while(another=='y')
					{
						printf("\n ENTER THE STUDENT ID TO DELETE  ");
						scanf("%s",&sid);
						fqt=fopen("temp2.DAT"," wb");//create the temporary file
						rewind(fq);
						while(fread(&s,recordsize2,1,fq)==1)
						{
							if(strcmp(s.stid,sid)!=0)//if the entered record match
							{
								fwrite(&s,recordsize2,1,fqt);//move all the record except the deleted one
							}
						}
						fclose(fq);
						fclose(fqt);
						remove("DATA2.DAT");
						rename("temp2.DAT","DATA2.DAT");
						fq=fopen("DATA2.DAT","rb+");
						printf("\nMember successfully Deleted from the Database.\n");
						Sleep(500);
						printf("DELETE ANOTHER REOCRD(yes/no):");
						fflush(stdin);
						///another=getchar();
						scanf("%c",&another);
					}
}
void IssueBook()
{
		rewind(fp);
		rewind(fq);
		printf("Enter the Barcode of book to be issued ");
					scanf("%s",&bcode);

					while(fread(&b,recordsize1,1,fp)==1)
						{
							if(strcmp(b.barcode,bcode)==0)//if the entered record match
								{
									if(b.issuedflag==1){
										printf("Book is already issued to another student, kindly return it and reissue it");
										Sleep(500);
									}
									else
									{

									printf("\n ENTER THE STUDENT ID ");
									scanf("%s",&sid);
									//rewind(fq);
									while(fread(&s,recordsize2,1,fq)==1)
										{
											if(strcmp(s.stid,sid)==0)//if the entered record match
												{
														b.issuedflag=1;
														for(int i=0;i<30;i++){

														b.issuedto[i]=s.name[i]; // to add name to book to whom it is issued
													}
														fseek(fp,-recordsize1,SEEK_CUR);
														fwrite(&b,recordsize1,1,fp);
														s.bookcount++;
														fseek(fq,-recordsize2,SEEK_CUR);
													    fwrite(&s,recordsize2,1,fq);
														
														printf("Book issued successfully to student %s\n",s.name);
														Sleep(500);
														return;}

											}

											}
											}


									}
}

void ReturnBook()
{
		printf("Enter the Barcode of book to be returned ");
					scanf("%s",&bcode);
					rewind(fp);
					while(fread(&b,recordsize1,1,fp)==1)
						{
							if(strcmp(b.barcode,bcode)==0)//if the entered record match
								{
									if(b.issuedflag==1)
									{

									rewind(fq);
									while(fread(&s,recordsize2,1,fq)==1)

										{
											if(strcmp(b.issuedto,s.name)==0){

													b.issuedflag=0;
													strcpy(b.issuedto," ");

													fseek(fp,-recordsize1,SEEK_CUR);
													fwrite(&b,recordsize1,1,fp);
													s.bookcount--;
													fseek(fq,-recordsize2,SEEK_CUR);
													fwrite(&s,recordsize2,1,fq);
													printf("Book successfully returned\n");
													Sleep(500);
													return;
										}
										}
									}
									else{

									printf("Book is already returned\n");
									Sleep(500);
									return ;
								}


								}}
								printf("Enter a correct barcode \n");
								Sleep(500);

}

void listbook()
{

printf("\t\t\t\t\t\tBooks list LIST\n\n");
				rewind(fp);
				printf("________________________________________________________________________________________________________________________\n");
				printf("NAME\t\tBAR CODE\tAUTHOR\t\tPUBLICATION\t\t ISSUED STATUS \t\t\t ISSUED TO\n");
				while(fread(&b,recordsize1,1,fp)==1)
				{
                    if(b.issuedflag==0)
                        strcpy(isIssued,"Un-Issued");
                    else
                        strcpy(isIssued,"Issued");

					printf("--------------------------------------------------------------------------------------------------------------------\n");
					printf("%s\t\t%s\t\t %s\t\t  %s\t\t\t   %s\t\t\t  %s \n",b.bname,b.barcode,b.author,b.publication,isIssued,b.issuedto);
					printf("--------------------------------------------------------------------------------------------------------------------\n");
				}
				printf("\n PRESS ENTER FOR MAIN WINDOW:");
				fflush(stdin);
				///another=getchar();
                scanf("%c",&another);

}
void listissued(){

	printf("\t\t\t\t\t\tBooks list LIST\n\n");
				rewind(fp);
				printf("________________________________________________________________________________________________________________________\n");
				printf("NAME\t\tBAR CODE\tAUTHOR\t\tPUBLICATION\t\tISSUED STATUS \t\t Issued To\n");
				while(fread(&b,recordsize1,1,fp)==1)

				{


					if(b.issuedflag==1){
                        if(b.issuedflag==0)
                        strcpy(isIssued,"Un-Issued");
                        else
                        strcpy(isIssued,"Issued");

					printf("--------------------------------------------------------------------------------------------------------------------\n");
					printf("%s\t\t%s\t\t  %s\t\t  %s\t\t\t %s\t\t\t%s \n",b.bname,b.barcode,b.author,b.publication,isIssued,b.issuedto);
					printf("-------------------------------------------------------------------------------------------------------------------\n");
			}

			}
				printf("\n PRESS ENTER FOR MAIN WINDOW:");
				fflush(stdin);
				///another=getchar();
                scanf("%c",&another);

}

/*void Export(){
        char choice;
        //system("clear");
        puts("Press \n 1. To Export All Book list \n 2. To Export all Student List \n 3. To return to previous Menu\n");
        fflush(stdin);
        scanf("%c",&choice);
            switch(choice)
        {
                case '1':
                {
                    puts("Now exporting all the book records\n");
                    rewind(fp);
                    fr=fopen("Book list.txt","rb+");  /// create a new text file
                    while(fread(&b,recordsize1,1,fp)==1){
                            fwrite(&b,recordsize1,1,fr);  /// write to the text file
                            }

                    if(fr==NULL){
                        puts("Can not export Any Record. Please try again\n");
                        }
                    else
                        puts("Recors exported successfully, check 'book list.txt'. \n");

                    fclose(fr);

                    break;
                }

                case '2':
                {
                puts("Now exporting all the Student records\n");
                    rewind(fq);
                    fr=fopen("Student list.txt","rb+");
                    while(fread(&s,recordsize2,1,fq)==1){
                            fwrite(&b,recordsize1,1,fr);
                            }

                    if(fr==NULL){
                        puts("Can not export Any Record. Please try again\n");
                        }
                    else
                        puts("Recors exported successfully, check 'student list.txt'. \n");

                    fclose(fr);

                    break;

                }
                case 'r':
                    system("clear");
                    return;

                default:
                        puts("Select a correct choice\n");

        }


}
*/
