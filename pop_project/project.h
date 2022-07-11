#ifndef POP_PROJECT_PROJECT_H
#define POP_PROJECT_PROJECT_H

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
void print_char(int length, char c);

//prints a box with length of 1 *y, labeled with label and text written inside
/*
 ex:
           ------
    name: |fae   |
           ------
*/
void make_box(int y, char *label, void *text);

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
void split(char *input, char **output);

//this function saves every user's data about boxes (using $, @ and ^ for easier access when searching)
/*
!!!note:
save_info() is used to store EVERY user's main data PERMANENTLY in the MAIN file
while temporary_save() is used to store ONE user's data TEMPORARILY in a STRUCT
*/
void save_info(int username, char **labels, int *lengths);

//finds desired file based on username and temporary saves its data into struct for later use IN THE MAIN FILE
void save_for_edit(int username);

//editing the current form by using the struct
void edit_form();

//checks whether input id has been used before (based on main data file)
//returns flag: if flag = 1 => user must enter a new username, flag = 0 => it's fine
int check_id(int username);

//creating a new form
void creat_form();

//save individual file data for later use
void temporary_save(int username, struct info temporary);

//make a new file with username as name, filled with input data
void make_file(int username, struct info strct);

//add text to a box
void add(int username);

//remove specific label and its textbox
void remove_(int username);

//update a label's text
void update(int username);

//printing a menu to show these operations: add, edit, remove and update
void open_form();

#endif	//POP_PROJECT_PROJECT_H