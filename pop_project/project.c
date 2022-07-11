#include <stdio.h>
#include <stdlib.h >  	//to use free() and system()
#include <string.h >  	//to use strlen(), strcpy() and strcmp()
#include <conio.h >   	//to use getch() for esc button

//configure setting to print menu text in blue to stand out
#define blue_start "033[0;34m"	//color start
#define blue_end "033[0m"	//to flush out previous setting
#define menu(string) printf("%s %s %s", blue_start, string, blue_end)

//clearing the view
#define clear system("cls")

//temporary storing each files information
struct info
{
    int username;
    char labels[10][20];
    int lengths[10];
    char text[10][30];
}

        temp;

//repetitive for loop in used in make_box made as function
void print_char(int length, char c)
{
    for (int i = 0; i < length; ++i)
    {
        putchar(c);
    }
}

//prints a box with length of 1 *y, labeled with label and text written inside
/*
 ex:
           ------
    name: |fae   |
           ------
*/
void make_box(int y, char *label, void *text)
{
    putchar(' ');
    print_char(strlen(label) + 2, ' ');
    print_char(y *2, '-');
    putchar('\n');
    printf("%s: ", label);
    putchar('|');

    //if third input is empty, prints an empty box with label
    if (text == NULL)
    {
        print_char(y *2, '-');
    }
    else
    {
        printf("%s", text);
        print_char(y *2 - strlen(text), ' ');
    }

    putchar('|');
    putchar('\n');
    print_char(strlen(label) + 2, ' ');
    putchar(' ');
    print_char(y *2, '-');
}

//make box and print them until all information is displayed
void print_boxes(struct info strct)
{
    for (int i = 0; i < strlen(strct.lengths); ++i)
    {
        make_box(strct.lengths[i], strct.labels[i], strct.text[i]);
        putchar('\n');
    }
}

//homemade strtok!
void split(char *input, char **output)
{
    int i = 0, j = 0, k = 0;

    while (input[i] != '\n')
    {
        if (input[i] != ' ')
        {
            output[j][k++] = input[i];
        }
        else
        {
            j++;
            k = 0;
        }
    }

    output[j][k] = '\0';
}

//this function saves every user's data about boxes (using $, @ and ^ for easier access when searching)
/*
!!!note:
save_info() is used to store EVERY user's main data PERMANENTLY in the MAIN file
while temporary_save() is used to store ONE user's data TEMPORARILY in a STRUCT
*/
void save_info(int username, char **labels, int *lengths)
{
    FILE * fpointer;
    fpointer = fopen("infos.txt", "a");
    fprintf(fpointer, "%d\n", username);

    //entering data
    for (int i = 0; i < strlen(lengths); ++i)
    {
        //$ identifies start of length's info
        fprintf(fpointer, "$ %d ", lengths[i]);
        //@ identifies start of label's info
        fprintf(fpointer, "@ %s\n", labels[i]);
    }

    //^ identifies end of info
    fprintf(fpointer, "^");

    fclose(fpointer);
}

//finds desired file based on username and temporary saves its data into struct for later use IN THE MAIN FILE
void save_for_edit(int username)
{
    temp.username = username;
    int i = 0;
    FILE * fpointer;
    fpointer = fopen("infos.txt", "r");
    int tempnumber;

    //as declared before, $ identifies saved lengths and ^ identifies end of user info
    //each length and label is temporarily stored in a struct
    while (!feof(fpointer))
    {
        fscanf(fpointer, "%d", &tempnumber);
        if (tempnumber == username)
        {
            while (fgetchar() != '^')
            {
                if (fgetchar() == '$')
                {
                    fscanf(fpointer, "%d", &temp.lengths[i]);
                    fscanf(fpointer, "%s", temp.labels[i]);
                    i++;
                }
            }

            break;
        }
    }
}

//editing the current form by using the struct
void edit_form()
{
    int username;
    printf("enter your username.\n");
    scanf("%d", &username);
    //storing data to operate changes
    save_for_edit(username);

    menu("what can i do for you?\n1. add a new box.\n2. remove a box.\n3. rename a label.\n4. exit\n");

    int choice;
    scanf("%d", &choice);

    int i = 0;
    switch (choice)
    {
        case 1:	//add new box
            while (temp.lengths[i++])
            {;	//reaching the last index
            }

            puts("enter desired box length and label respectively\n");
            i++;	//next index
            scanf("%d", &temp.lengths[i]);
            scanf("%s", temp.labels[i]);
            //clear the view and print the updated result
            clear;
            print_boxes(temp);
            break;

        case 2:	//remove a label
            printf("name the label you want to be removed.\n");
            char tempremove[10];
            scanf("%s", tempremove);
            for (int j = 0; j < i; ++j)
            {
                //if input name and stored name are equal, empty data
                if (!strcmp(temp.labels[j], tempremove))
                {
                    free(temp.labels[j]);
                    free(&temp.lengths[j]);
                    i--;
                }
            }

            //clear the view and print the updated result
            clear;
            print_boxes(temp);
            break;

        case 3:	//rename a label
            printf("which label do you want to rename? and what's your desired name?(respectively)\n");
            char oldname[10];
            char newname[10];
            scanf("%s %s", oldname, newname);
            for (int j = 0; j < i; ++j)
            {
                //if input name and stored name are equal, empty data and add the new one
                if (!strcmp(temp.labels[j], oldname))
                {
                    free(temp.labels[j]);
                    strcpy(temp.labels[j], newname);
                }
            }

            //clear the view and print the updated result
            clear;
            print_boxes(temp);
            break;

        default:	//exit
            break;
    }
}

//checks whether input id has been used before (based on main data file)
//returns flag: if flag = 1 => user must enter a new username, flag = 0 => it's fine
int check_id(int username)
{
    //flag is 0 by default, if it turns to 1, it means this username cannot be used
    int flag = 0;

    FILE * fpointer;
    fpointer = fopen("infos.txt", "r");
    //first line is the first username, other usernames are located after ^ character
    int *usernames = malloc(sizeof(int) *50);
    fscanf(fpointer, "%d", &usernames[0]);
    int i = 1;

    while (!feof(fpointer))
    {
        char c = fgetchar();
        if (c == '^')
        {
            fscanf(fpointer, "%d", &usernames[i++]);
        }
    }

    usernames[i] = '\0';
    fclose(fpointer);

    //now that we have all usernames stored, it's time to search
    for (int j = 0; j < strlen(usernames); ++j)
    {
        if (usernames[j] == username)
        {
            flag = 1;
            break;
        }
    }

    return flag;
}

//creating a new form
void creat_form()
{
    clear;

    int username;
    printf("enter a numeric code. (as your username)\n");
    scanf("%d", &username);
    if (check_id(username))
    {
        while (!check_id(username))
        {
            //not accepting username, until it's new
            printf("this username has been used before. enter another one.\n");
            scanf("%d", &username);
        }
    }

    //allocating pointers to store lengths and labels
    int *tempnumber = malloc(sizeof(int) *10);
    char **tempstring = malloc(sizeof(char) *10);
    for (int i = 0; i < 10; ++i)
    {
        tempstring[i] = malloc(sizeof(char) *20);
    }

    int exit;
    int i = 0;
    printf("enter desired box length and label respectively\nenter esc to exit\n");

    //taking input to make box until esc (ANSI = 27) is pressed
    do {
        scanf("%d", &tempnumber[i]);
        getchar();
        gets(tempstring[i]);
        //print textbox with every new input
        make_box(tempnumber[i], tempstring[i], NULL);
        i++;
        putchar('\n');
        exit = getch();
    } while (exit != 27);

    //append new data to the main file
    save_info(username, tempstring, tempnumber);
}

//save individual file data for later use
void temporary_save(int username, struct info temporary)
{
    FILE * fpointer;

    //make file's name: username + .txt
    char filename[20];
    strcpy(filename, (const char *) username);
    strcpy(filename, ".txt");
    fpointer = fopen(filename, "r");	//in read mode

    char line[250];	//line temporary save
    int i = 0;
    while (fgets(line, 250, fpointer))
    {
        char line2[10][20];	//sorted 2D data: first index => label and second index => text
        split(line, line2);
        strcpy(temporary.labels[i], line2[0]);
        strcpy(temporary.text[i], line2[1]);
        i++;
    }

    fclose(fpointer);
}

//make a new file with username as name, filled with input data
void make_file(int username, struct info strct)
{
    //store data in the main file
    save_for_edit(username);

    //make file's name: username + .txt
    char filename[20];
    strcpy(filename, (const char *) username);
    strcpy(filename, ".txt");

    FILE * fpointer;
    fpointer = fopen(filename, "w");	//in write mode

    //enter previously saved data from struct to file
    for (int i = 0; i < strlen(temp.lengths); ++i)
    {
        fprintf(fpointer, "%s ", strct.labels[i]);
        fprintf(fpointer, "%s\n", strct.text[i]);
    }

    fclose(fpointer);
}

//add text to a box
void add(int username)
{
    //first store the data based on username
    save_for_edit(username);

    printf("which box do you want to fill? (enter the label)\n");
    char templabel[20];
    scanf("%s", templabel);

    for (int i = 0; i < strlen(temp.lengths); ++i)
    {
        //when found the desired label, add text input
        if (!strcmp(templabel, temp.labels[i]))
        {
            strcpy(temp.text[i], templabel);
            break;
        }
    }

    //save the new data
    make_file(username, temp);

    //clear and print updated data
    clear;
    print_boxes(temp);
}

//remove specific label and its textbox
void remove_(int username)
{
    struct info strct;

    //save data based on username
    temporary_save(username, strct);
    printf("which label do you want to be removed?\n");
    char label[30];
    scanf("%s", label);

    for (int i = 0; i < strlen(strct.lengths); ++i)
    {
        //when found the desired label, delete it
        if (!strcmp(label, strct.labels[i]))
        {
            free(strct.labels[i]);
            free(strct.text[i]);
            free(&strct.lengths[i]);
            break;
        }
    }

    //save the new data
    make_file(username, strct);

    //clear and print updated data
    clear;
    print_boxes(strct);
}

//update a label's text
void update(int username)
{
    struct info strct;
    //save data based on username
    temporary_save(username, strct);
    printf("which label do you want to be updated?\n");
    char label[30];
    scanf("%s", label);
    printf("enter your new text.\n");
    char text[30];
    scanf("%s", text);

    for (int i = 0; i < strlen(strct.lengths); ++i)
    {
        //when found the desired label, delete current data and enter the new one
        if (!strcmp(label, strct.labels[i]))
        {
            free(strct.text[i]);
            strcpy(strct.text[i], label);
            break;
        }
    }

    //save the new data
    make_file(username, strct);

    //clear and print updated data
    clear;
    print_boxes(strct);
}

//printing a menu to show these operations: add, edit, remove and update
void open_form()
{
    printf("enter your username.\n");
    int username;
    scanf("%d", &username);

    menu("what can i do for you?\n1. add.\n2. remove.\n3. update.\n4. exit\n");

    int choice;
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:	//add
            add(username);
            break;
        case 2:	//remove
            remove_(username);
            break;
        case 3:	//update
            update(username);
            break;
        default:	//exit
            break;
    }
}