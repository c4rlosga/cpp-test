#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "menu.h"
#include <curl/curl.h>

size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}

int main(int argc, const char* argv[]) {
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
        } else if (option == menu::MENU_NEW) {
            printf("curlpp go eat shit\n");

            curl_global_init(CURL_GLOBAL_DEFAULT);
            auto curl = curl_easy_init();
            if (curl) {
                curl_easy_setopt(curl, CURLOPT_URL, "https://marf.xyz/archive?sql");
                curl_easy_setopt(curl, CURLOPT_PORT, 8081L);
                curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
                curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
                curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
                curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);

                std::string response_string;
                std::string header_string;
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
                curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

                curl_easy_perform(curl);
                std::cout << response_string;
                curl_easy_cleanup(curl);
                curl_global_cleanup();
                curl = NULL;
                
                // std::cout << "header: " << header_string << std::endl;
                // std::cout << response_string << std::endl;
            }
        }
    }
}
