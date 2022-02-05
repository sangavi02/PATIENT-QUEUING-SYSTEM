#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#define MAX 5

void clearInput(void);
void addNewpatient(void);
void listAll(void);
void deletepatient(void);
void modifypatient(void);
int findpatient(void);
int prompt(void);
int findnum (int);
void queue(void);
void insert();
void delete();
void display();
int queue_array[MAX];
int rear = - 1;
int front = - 1;
int no;

typedef struct patient {
    int number;
    int age;
    char name[20];
    char gender[10];
    char phone[15];
    char complaint[20];
    struct contact *next;
    int count;
    } patient;
patient *firstc,*currentc,*newc;

int cnum = 0;
int main()
{
    int a;
    FILE *datafile;
    char *filename = "contactdatabase.dat";
    char ch;
    firstc = NULL;
    datafile = fopen(filename,"r");

    if(datafile)
    {
	    firstc = (struct patient *)malloc(sizeof(struct patient));
	    currentc = firstc;
	    while(1)
     	    {
		    newc = (struct patient *)malloc(sizeof(struct patient));
		    fread(currentc,sizeof(struct patient),1,datafile);
		    if(currentc->next == NULL)
			    break;
		    currentc->next = newc;
            currentc->count=0;
		    currentc = newc;
	    }
	    fclose(datafile);
	    cnum = currentc->number;

    }

    do
    {
	fflush(stdin);
        puts("\nWelcome To The KMCH Hospital");

        puts("1 - Add a new patient");
	puts("2 - Delete a patient");
	puts("3 - List all patient ");
	puts("4 - Modify patient ");
	puts("5 - Find a patient ");
	puts("6 - Consult doctor");

    puts("Q - Save and quit\n");
        printf("\tYour choice:");
        ch = getchar();
	    ch = toupper(ch);
        switch(ch)
        {
            case '1':
                puts("Add a new patient\n");
	        fflush(stdin);
                addNewpatient();
                break;
	    case '2':
		puts("Delete a patient \n");
		deletepatient();
		break;
	    case '3':
		puts("List all patient \n");
		listAll();
		break;
	    case '4':
		puts("Modify a patient \n");
		modifypatient();
		break;
	    case '5':
		puts("Find a patient  \n");
		findpatient();
		break;
		case '6':
         puts("Consultation of doctor\n");
         puts(" Enter 1 to consult the doctor");
         puts(" Enter 2 to display consulted patient's acc no");
         scanf("%d",&a);
         switch(a)
         {
         case 1:
             {
            insert();
            break;
         }
         case 2:{
            delete();
            break;
         }}
            case 'Q':
                puts("\nSave and quit\n");
                default:
                break;
        }
    }
    while(ch != 'Q');

    currentc = firstc;

    if(currentc == NULL)
	    return(0);

    datafile = fopen(filename,"w");

    if(datafile == NULL)
    {
	    printf("Error writing to %s\n",filename);
	    return(1);
    }

    while(currentc != NULL)
    {
	    fwrite(currentc,sizeof(struct patient),1,datafile);
	    currentc = currentc->next;
    }
    fclose(datafile);
    return(0);
}

void addNewpatient(void)
{
    newc = (struct patient *)malloc(sizeof(struct patient));

    if(firstc==NULL)
        firstc = currentc = newc;

    else
    {
        currentc = firstc;

        while(currentc->next != NULL)currentc = currentc->next;

        currentc->next = newc;
        currentc = newc;
    }
     cnum++;
    printf("%27s: %5i\n","account number",cnum);
    currentc->number = cnum;

    printf("%27s: ","Enter patient name");
    gets(currentc->name);
    printf("%27s: ","Enter gender of the patient");
    gets(currentc->gender);
    printf("%27s: ","Enter patient Phone number");
    gets(currentc->phone);
    printf("%27s: ","Enter patient complaint");
    gets(currentc->complaint);
    printf("%27s: ","Enter age of the patient");
    scanf("%d",&currentc->age);
    printf("patient added!");
    currentc->count=0;

    currentc->next = NULL;
}

void listAll(void)
{
    if(firstc==NULL)
        puts("There are no patients to display!");

    else
    {
	    printf("%6s %-20s  %6s %-20s %-15s %-15s\n","Acct#","Name","Age","Gender" ,"complaint","Phone");
        puts("------ -------------------- ------- -------------- ------------------ ------------------");

        currentc=firstc;

        do
        {

                printf("%6d: %-20s %6d %-20s %-15s %-20s\n",
                currentc->number,
                currentc->name,
                currentc->age,
                currentc->gender,
                currentc->complaint,
                currentc->phone);

        }

        while((currentc=currentc->next) != NULL);
    }
}
 void deletepatient(void)
{
    int record;
    struct patient *previousa;
    if(firstc==NULL)
    {
        puts("There are no patients to delete!");
	return;
    }

    listAll();
    printf("Enter account number of patient to delete: ");
    scanf("%d",&record);
    currentc = firstc;

    while(currentc != NULL)
    {
        if(currentc->number == record)
	{
	    if(currentc == firstc)
		firstc=currentc->next;
	    else
		previousa->next = currentc->next;
        free(currentc);
	    printf("contact %d deleted!\n",record);
	    return;
	}

	else
	{
        previousa = currentc;
	    currentc = currentc->next;
	}
    }
    printf("account %d not found!\n",record);
 }
 void modifypatient(void)
{
    int record, result;
    if(firstc==NULL)
    {
        puts("There are no patients to modify!");
	return;
    }

    listAll();
    printf("Enter patient account number to modify or change: ");
    scanf("%d",&record);
    result = findnum(record);

    if( result >0 ){
	    printf("Contact %d:\n",currentc->number);
	    printf("Name: %s\n",currentc->name);
	    if(prompt())
		    gets(currentc->name);
        printf("Age: %d\n",currentc->age);
	    if(prompt())
		    gets(currentc->age);
        printf("Gender: %s\n",currentc->gender);
	    if(prompt())
		    gets(currentc->gender);
        printf("complaint: %s\n",currentc->complaint);
	    if(prompt())
		    gets(currentc->complaint);
	    printf("Phone: %s\n",currentc->phone);
	    if(prompt())
		    gets(currentc->phone);

	    return;
	}
    printf("account %d was not found!\n",record);
}
 int findnum (int recordnum)
{
    int record;
    record = recordnum;
    currentc = firstc;
    while(currentc != NULL)
    {

        if(currentc->number == record)
	     {
           return 1;
         }

	else
	{
	    currentc = currentc->next;
	}
    }
    return -1;
}
 int findpatient(void)
{
     char buff[20];

     if(firstc==NULL)
	{
        puts("There are no accounts to find!");
	    return 1;
    }

    printf("Enter patient name: ");
    fflush(stdin);
    gets(buff);

    currentc = firstc;
    while(currentc != NULL)
    {
        if( strcmp(currentc->name, buff) == 0 )
	    {
			printf("%6s %-20s  %6s %-20s %-15s %-15s\n","Acct#","Name","Age","Gender","Complaint","Phone");

            printf("%6d: %-20s %6d %-20s %-15s %-20s\n",
            currentc->number,
            currentc->name,
            currentc->age,
            currentc->gender,
            currentc->complaint,
            currentc->phone);


			return 0;
	    }
		else
		{
			currentc = currentc->next;
		}
    }
    printf("patient %s was not found!\n",buff);
          return 1;
}

int prompt(void)
{
	char ch;
    fflush(stdin);
	printf("Update? (Y to update any other key to not)");
	ch = getchar();
	ch = toupper(ch);
	fflush(stdin);
	if(ch == 'Y')
	{
		printf("Enter new value: ");
		return(1);
	}
	else
		return(0);
}
void insert()
{
int no;
if(rear ==  MAX- 1)
printf("Queue Overflow \n");
else
{
if(front== - 1)
front = 0;
printf("enter the patient acc no : ");
scanf("%d", &no);
rear = rear + 1;
queue_array[rear] = no;
printf("consult Dr. M.Muthu krishnan Room no:1");
}
}
void delete()
{
if(front == - 1 || front > rear)
{
printf("There is no patient to remove \n");
return;
}
else
{
printf("\nThe acc number of patient who has consulted doctor : %d\n", queue_array[no]);
front = front + 1;
}
}





