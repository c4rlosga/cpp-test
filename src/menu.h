#ifndef MENU_H
#define MENU_H

class menu {
    public:
        menu();
        virtual ~menu();

        static int const MENU_QUIT    = 0;
        static int const MENU_LIST    = 1;
        static int const MENU_NEW     = 2;
        static int const MENU_EDIT    = 3;

        bool exists(int & option);
        void print_menu();
};

#endif // MENU_H
