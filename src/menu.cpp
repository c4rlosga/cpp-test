#include "menu.h"
#include <stdio.h>


static constexpr int MENU_OPTIONS[] = {menu::MENU_QUIT, menu::MENU_LIST, menu::MENU_NEW, menu::MENU_EDIT};
static constexpr char* MENU_STRINGS[] = {"Quit", "List all notes", "Create a new note", "Edit a note"};


menu::menu() {
    //ctor
}

menu::~menu() {
    //dtor
}

void menu::print_menu() {
    for (int i = 0; i < sizeof(MENU_OPTIONS) / sizeof(MENU_OPTIONS[0]); i++) {
        printf("%d) %s\n", MENU_OPTIONS[i], MENU_STRINGS[i]);
    }
}

bool menu::exists(int & option) {
    for (int i = 0; i < sizeof(MENU_OPTIONS) / sizeof(MENU_OPTIONS[0]); i++) {
        if (MENU_OPTIONS[i] == option)
            return true;
    }

    return false;
}
