#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct STUDENT {
    int ID;
    char name[100];
    double score;
} STD;

typedef struct GRADES { //This struct to facilitate printing to the record file//
    double quiz;
    double assign;
    double mid;
    double prac;
    double final;
} grades;


//Ascending order of ID's function//
void ascending(STD DATA[29],int n) {

    STD tempid;
    for(int j=0;j<29;j++) {
        for (int i = 0; i <29 ; ++i) {
            if(DATA[i].ID > DATA[j].ID) {
                tempid = DATA[i];
                DATA[i] = DATA[j];
                DATA[j] = tempid;
            }
        }
    }
}

// Here's the ascending order of ID's by recursive function//
/*void ascending(STD DATA[29],int n) { //By recursive function//

    int i,j,temp;
    i=n;
    if(i>0)
    {
        for(j=0;j<n-1;j++)
        {
            if(DATA[j].ID>DATA[j+1].ID)
            {
                temp=DATA[j].ID;
                DATA[j].ID=DATA[j+1].ID;
                DATA[j+1].ID=temp;
            }
        }
        ascending(DATA,n-1);
    }
    else
    {
        return;
    }
}
*/
//-----------------------------------------------------------//
//descending order of scores function//
void descending (STD DATA[29]) {

    int i;
    STD a;

    for (int j = 0; j < 29; ++j) {
        for (i = 0; i < 29; ++i) {

            if (DATA[i].score < DATA[j].score) {
                a = DATA[i];
                DATA[i].score = DATA[j].score;
                DATA[j] = a;
            }
        }
    }
}

//Alphabetical order of names function//
void ascendingstr(STD DATA[29])
{
    int i;
    STD tempname;

    for (int j = 0; j < 29; ++j) {
    for (i = 0; i <29; i++) {

            if (strcmp(DATA[i].name, DATA[j].name) > 0) {
                tempname = DATA[i];
                DATA[i] = DATA[j];
                DATA[j] = tempname;
            }
        }
    }
}

//Splitting the data and making the calculations function//
void split_cal(char lines[100]  , int i, STD DATA[29], grades scores[5], FILE *out) {

    char *token;                        //I used (sscanf) to assign every value in the new file after printing//
    token = strtok(lines, ",");
    sscanf(token, "%d", &DATA[i].ID);
    token = strtok(NULL, ",");
    strcpy(DATA[i].name, token);
    token = strtok(NULL, ",");
    sscanf(token, "%lf", &scores[i].assign);
    token = strtok(NULL, ",");
    sscanf(token, "%lf", &scores[i].quiz);
    token = strtok(NULL, ",");
    sscanf(token, "%lf", &scores[i].mid);
    token = strtok(NULL, ",");
    sscanf(token, "%lf", &scores[i].prac);
    token = strtok(NULL, ",");
    sscanf(token, "%lf", &scores[i].final);

    DATA[i].score =
            ((scores[i].assign * 0.15) +
            (scores[i].quiz * 0.15) +
            (scores[i].mid * 0.25) +
            (scores[i].prac * 0.1) +
            (scores[i].final * 0.35)) ;
    //---------------------------------------//
    //printing in the file record.txt//
    //PS: printing to the record is done after finishing all the requirements in the lists in main function//

    fprintf(out , "%d ", DATA[i].ID);
    fputs(DATA[i].name, out);
    fprintf(out, "%0.2f \n", DATA[i].score);
}

int main() {
    STD DATA[29];
    grades scores[5];
    int entelement;
    int entid;
    char entname[100];
    char tvalue; 
    int element;
    char lines[100];
    char file[10];
    FILE *in, *out;

    printf("Enter file name to read from\nThe Name of file is :");
    gets(file);

    in = fopen(file, "r");
    out = fopen("record.txt", "w");

    if (in == NULL) {
        printf("No file in such name\n");
        exit(0);
    }

    for (int k = 0; k <29; ++k) {
        int i =0;
        while (fgets(lines, 100, in) != NULL) { //of each line of char's//
            split_cal(lines,i ,DATA,scores,out);
            ++i;
        }
    }

    printf("Please choose from this list what you want to display\n1.Sorting data according to ascending ID's\n2.Sorting data according to descending scores"
           "\n3.Sorting data according to ascending alphabetical\n10. Exit");

    scanf("%d",&element);

    if(element == 1)
    {
        int n;
        ascending(DATA,n);
        for (int i = 0; i <29 ; ++i) {
            printf("%d\n",DATA[i].ID);
        }
    }
    else if(element == 2)
    {
        descending(DATA);

        for (int i = 0; i <29; ++i) {
            printf("%0.2f\n", DATA[i].score);
        }
    }
    else if(element == 3)
    {
        ascendingstr(DATA);
        for (int m= 0; m <29 ; ++m) {
            puts(DATA[m].name);
        }
    }
    else if (element ==10)
    {
        exit(10);
    }
    else
        printf("Error Input !");

    fclose(in);
    fclose(out);
    //-----------------------------------------------------------------------------------------------------------------//

    printf("Please choose from 4 and 5 your option :\n 4. to type student's ID and get his/her score\n 5. to type student's name to get his/her score\n"
           " 6. to exit");

scanf("%d",&entelement);

// WE CAN USE "FLAGS" HERE TO GET OUT OF THE LOOPING OUTPUTS, BUT THIS ALSO WORKS//
    if (entelement == 4) {
        printf("Add student ID:\n");
        scanf("%d", &entid);

        for (int l = 0; l < 29; ++l) {
            if (entid == DATA[l].ID) {
                printf("The score of %d is %0.1f\n", DATA[l].ID, DATA[l].score);
                break;
            }
        }
    }


    else if(entelement==5) {
        scanf("%c", &tvalue); //here I used scanf to clear all the read variables by gets//
        
        printf("Add student name:\n");
        gets(entname);
        for (int i = 0; i < 30; ++i) {
            if (strcmp(entname, DATA[i].name) == 0) {
                printf("The score is %0.2f", DATA[i].score);
                break;
            }
        }
    }

   else  if(element==6)
    {
        exit(6);
    }
   else
       printf("ERROR INPUT");

    return 0;
}
