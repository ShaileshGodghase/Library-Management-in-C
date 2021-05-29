#include<stdio.h>
#include<conio.h>
#include<process.h>
#include<time.h>
#include<string.h>

void format_date(char ndate[])
{
	 char t;

	 // swapping index 0 and 3
	 t = ndate[0];
	 ndate[0] = ndate[3];
	 ndate[3] = t;

	 //swapping index 1 and 4
	 t = ndate[1];
	 ndate[1] = ndate[4];
	 ndate[4] = t;
}

void replace_space_with_tab(char ar[])
{
	int i=0;
	while(ar[i] != '\0')
	{
		if(ar[i] == ' ')
		{
		ar[i] = '\t';
		}
		i++;
	}
}

void replace_space(char ar[])
{
	int i =0;
	while(ar[i] != '\0')
	{
		if(ar[i] == 32)
		{
		ar[i] = '_';
		}
		i++;
	}
}


int search_book_num_in_line(char original_str[],char bknum[])
{
// in this function we will check the presence of bknum[] into original_str[]
// only by comparing first five characters of original_str[]
// i.e. from 0 to 4 only

// returns 1 if present else return 0

	int len,flag=1,i;
	len = strlen(bknum);
	for(i=0;i<len;i++)
	{
		if(original_str[i] != bknum[i])
		{
		flag=2;
		break;
		}
	}

	return flag==1?1:0;

}

int contains_not(char original_str[])
{
// in this function we will check whether original_str[] contains NOT or not.
// only compare last three characters
// length - 3

// return 1 if NOT is present else return 0

	int len;
	len = strlen(original_str);

	return original_str[len-3]=='N' && original_str[len-2] == 'O' && original_str[len-1] == 'T' ? 1 : 0 ;

}


void assign_ret_date(char original_str[])
{
// retrieve current date and over-write on NOT

	char rdate[15];
	int len;
	_strdate(rdate);
	format_date(rdate);

	len = strlen(original_str);
	original_str[len-3] = '\0';

	strcat(original_str,rdate);

}

void write_to_temp_file(char data_to_write[])
{
// write data_to_write into a temp file
	FILE *fp;
	int i;
	fp = fopen("temp_f.txt","a");
	i=0;
	while(data_to_write[i] != '\0')
	{
		fputc(data_to_write[i],fp);
		i++;
	}
	fclose(fp);
}


void copy_file_data(char *source_file_name, char *desti_file_name)
{
	FILE *fpr, *fpw;
	char ch;

	fpr = fopen(source_file_name,"r");
	fpw = fopen(desti_file_name,"w");

	do
	{
	ch = fgetc(fpr);
		if(ch!=EOF)
		{
		fputc(ch,fpw);
		}
	}while(ch!=EOF);

	fclose(fpr);
	fclose(fpw);
}


void search_content(char search_data[])
{
	FILE *fp;
	int flag=1,i,j,k,len,ind,ret;
	char bookdata[100],newdata[25],ch;


	fp = fopen("all_bks.txt","r");
	len = strlen(search_data);

	if(fp==NULL)
	{
	printf("File yet not created\n");
	}
	else
	{
		do
		{
			i=0;
			flag = 1;
			do
			{
				ch = fgetc(fp);
				if(ch!='\n')
				{
					bookdata[i] = ch;
					i++;
				}
				if(ch==EOF)
				{
				break;
				}
			}while(ch!='\n');

			bookdata[i] = '\0';
			// replace_space(bookdata);
			// i contains length of bookdata

			for(j=0;j<i-len;j++)
			{
				k=j;
				ind=0;

				while(k<j+len)
				{
				newdata[ind] = bookdata[k];
				ind++;
				k++;
				}

				newdata[ind] = '\0';
				replace_space(newdata);
				replace_space(search_data);

				ret = strcmp(newdata,search_data);

				if(ret==0)
				{
					replace_space_with_tab(bookdata);
					printf("%s\n",bookdata);
				}
			}
		}while(ch!=EOF);
		fclose(fp);
	} //end of else
}

void add_new_book()
{
	long bnum;
	char bauthor[25];
	char *btitle[25];
	char *bpubli[25];
	FILE *fp;

	printf("Enter Book number\n");
	scanf("%5ld",&bnum);
	fflush(stdin);

	printf("Enter book title\n");
	gets(btitle);
	fflush(stdin);

	printf("Enter Book author\n");
	gets(bauthor);
	fflush(stdin);

	printf("Enter Book publication\n");
	gets(bpubli);
	fflush(stdin);

	replace_space(btitle);
	replace_space(bauthor);
	replace_space(bpubli);

	fp = fopen("all_bks.txt","a");
	fprintf(fp,"%ld %s %s %s\n",bnum,btitle,bauthor,bpubli);
	fclose(fp);

	printf("Book Data Saved..!\n");
}

void add_new_student()
{
	// ho gaya

}

void issue_book()
{
	char idate[50];
	long bnum;
	char enr_num[15];
	FILE *fp;

	_strdate(idate);  // this function fills current date into 'idate'
	format_date(idate);

	printf("Enter Book number : ");
	scanf("%ld",&bnum);
	fflush(stdin);

	printf("Enter Student's Enrollment number : ");
	gets(enr_num);
	fflush(stdin);

	fp = fopen("issue_bk.txt","a");
	fprintf(fp,"%ld %s %s NOT\n",bnum,enr_num,idate);
	printf("Book Issued..!");

	fclose(fp);
}

void ret_book()
{
// we will retrieve line-by-line data from file "issue_bk.txt"
// and each line is sent to search_book_num_in_line(original_line,booknum)
// if this function returns 1 means this line has expected book number
// now check whether the same line ends with NOT or not
// if it ends with NOT then update the line's contents apply return date to it

	FILE *fp = NULL;
	char issuedata[200],ret_bknum[10];
	int i,a,b,flag=1;
	char ch;

	printf("Enter book number : ");
	gets(ret_bknum);
	fflush(stdin);

	fp = fopen("issue_bk.txt","r");

	if(fp==NULL)
	{
	printf("File yet not created\n");
	}
	else
	{
		do
		{
			i=0;
			do
			{
				ch = fgetc(fp);
				if(ch!='\n')
				{
					issuedata[i] = ch;
					i++;
				}
				if(ch==EOF)
				{
				break;
				}
			}while(ch!='\n');
			issuedata[i] = '\0';

			a = search_book_num_in_line(issuedata,ret_bknum);
			if(a==1)
			{
				b = contains_not(issuedata);
			}

			if(a==1 && b==1)
			{
			//means this line contains ret_bknum and also has NOT
			// now send this line to update ret_date instead of NOT
			assign_ret_date(issuedata);
			}

			// now write this issuedata wali line to a temp file
			write_to_temp_file(issuedata);
		}while(ch!=EOF);
		fclose(fp);
	}
		copy_file_data("temp_f.txt","issue_bk.txt");

		// now truncate temp_f.txt
		// so that next time it starts appending with new blank contents
		fp = fopen("temp_f.txt","w");
		fclose(fp);

}


int show_all_books(int show_data)
{
	FILE *fp;
	char bkdata[200];
	int i,linecount=0;
	char ch;

	fp=NULL;
	fp = fopen("all_bks.txt","r");

	if(fp==NULL)
	{
	printf("File yet not created\n");
	}
	else
	{
		do
		{
			i=0;
			do
			{
				ch = fgetc(fp);
				if(ch!='\n')
				{
					bkdata[i] = ch;
					i++;
				}
				if(ch==EOF)
				{
				break;
				}
			}while(ch!='\n');
			bkdata[i] = '\0';

			if(show_data==1)
			{
				// now replace space with spaces with '\t'
				replace_space_with_tab(bkdata);

				printf("%s\n\n",bkdata);

				if(linecount%12 == 0)
				{
					printf("\nPress Any key for Next Page.... ");
					getch();
					clrscr();
					printf("\n");
				}
			}

			linecount++;

		}while(ch!=EOF);
		fclose(fp);
	}
	return linecount;
}


void backup_data()
{
	// we only copy all three files into a temp file

	copy_file_data("all_bks.txt","cpy_bks.txt");
	copy_file_data("all_stds.txt", "cpy_stds.txt");
	copy_file_data("issue_bk.txt","iss_cpy.txt");
}


void search_book()
{
	int ch;
	char search_data[25];

	printf("1 - Search by Book Number\n");
	printf("2 - Search by Book Title\n");
	printf("3 - Search by Book Author\n");
	printf("4 - Search by Publication House\n");
	printf("Provide your choice : ");
	scanf("%d",&ch);
	fflush(stdin);

	switch(ch)
	{
	case 1: printf("Enter Book number to search : ");
		gets(search_data);
		fflush(stdin);
		search_content(search_data);
		break;
	case 2: printf("Enter Book Title to search : ");
		gets(search_data);
		fflush(stdin);
		search_content(search_data);
		break;
	case 3: printf("Enter Author Name to search : ");
		gets(search_data);
		fflush(stdin);
		search_content(search_data);
		break;
	case 4: printf("Enter Publication House to search : ");
		gets(search_data);
		fflush(stdin);
		search_content(search_data);
		break;
	default:printf("Invalid choice\n");

	} //end of switch case
}


void main()
{
	int ch,bkcount;
	clrscr();

	do
	{
	printf("\n1 - To add new  Book\n");
	printf("2 - Show all Books\n");
	printf("3 - Issue Book\n");
	printf("4 - Search Book\n");
	printf("5 - Backup Data\n");
	printf("6 - Total Book Count\n");
	printf("7 - EXIT\n");
	scanf("%d",&ch);

	switch(ch)
	{
	case 1: add_new_book();
		break;
	case 2: show_all_books(1);
		break;
	case 3: issue_book();
		break;
	case 4 :search_book();
		break;
	case 5: backup_data();
		break;
	case 6: bkcount = show_all_books(0);
		printf("Total books : %d\n",bkcount);
		break;
	case 7: exit(0);
	} //end of switch case
	}while(1);

	getch();
}




