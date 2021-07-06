#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "menu.h"


int main(int argc, const char* argv[])
{
    fprintf(stderr, "stderr: get this number %d\n", 5);
    menu* main = new menu();
    main->print_menu();

    int option;
    while (true) {
        printf("Choose an option: ");
        scanf("%d", &option);
        printf("Got option: %d\n", option);

        if (!main->exists(option)) {
            printf("Invalid option.\n");
            continue;
        }

        if (option == menu::MENU_QUIT) {
            printf("Goodbye!\n");
            return 0;
        } else if (option == menu::MENU_LIST) {
		printf("can't list yet!\n");
        }
    }
}
