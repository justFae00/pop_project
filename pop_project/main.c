#include "project.h"

int main() {
    menu("what can i do for you?\n1. creat a new form.\n2. edit an existing form.\n3. open a form.\n4. exit\n");
    int choice;

    scanf("%d", &choice);
    while (choice != 4){
        switch (choice) {
            case 1:   //creat a new form
                //clear the menu options
                clear;
                creat_form();
                //clear the view and reprint the menu options
                clear;
                menu("what can i do for you?\n1. creat a new form.\n2. edit an existing form.\n3. open a form.\n4. exit\n");
                break;

            case 2:    //edit the current form (only textboxes)
                clear;
                edit_form();
                clear;
                menu("what can i do for you?\n1. creat a new form.\n2. edit an existing form.\n3. open a form.\n4. exit\n");
                break;

            case 3:   //different operations on each box from each user
                clear;
                open_form();
                clear;
                menu("what can i do for you?\n1. creat a new form.\n2. edit an existing form.\n3. open a form.\n4. exit\n");
                break;

            default:   //exit
                break;

        }

        //when done with switch, program works and takes input unless it's 4 (exit)
        scanf("%d", &choice);
    }
    return 0;
}