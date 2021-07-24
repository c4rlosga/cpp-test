#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <ctime>
#include <iostream>
#include "menu.h"
#include <curl/curl.h>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;

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

        std::vector<std::string> test;
        
        test.push_back("test1");
        test.push_back("2test");
        test.push_back("test3");
        test.push_back("4test");
        test.push_back("5test");
        test.push_back("6test");
        test.push_back("7test");
        test.push_back("8test");
        test.push_back("9test");
        test.push_back("10test");
        
        if (option == menu::MENU_QUIT) {
            printf("Goodbye!\n");
            return 0;
        } else if (option == menu::MENU_LIST) {
            printf("can't list yet!\n");
        } else if (option == menu::MENU_EDIT) {
            printf("the current list of items is\n");
            for (int i = 0; i < test.size(); i++) {
                printf("item[%d]: contains the string '%s'\n", i, test.at(i).c_str());
            }

        } else if (option == menu::MENU_NEW) {
            printf("curlpp go eat shit\n");

            curl_global_init(CURL_GLOBAL_DEFAULT);
            auto curl = curl_easy_init();
            if (curl) {
                curl_easy_setopt(curl, CURLOPT_URL, "http://marf.xyz/archive?sql");
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
                // std::cout << "got header: " << header_string << std::endl;
                // std::cout << "response got: " << std::endl << response_string << std::endl;
                curl_easy_cleanup(curl);
                curl_global_cleanup();
                curl = NULL;
                if (response_string.length() > 0) {
                    json test = json::parse(response_string);
                    std::cout << "JSON dump is: " << std::endl << test.dump(4) << std::endl;
                    // std::cout << test["now"] << std::endl;
                    long int * epoch = new long int();
                    *epoch = test["now"];
                    std::time_t result = std::time(epoch);
                    std::cout << "Time converted from JSON is: " << std::asctime(std::localtime(&result)) << std::endl;
                }
                
                // std::cout << "header: " << header_string << std::endl;
                // std::cout << response_string << std::endl;
            }
        }
    }
}
