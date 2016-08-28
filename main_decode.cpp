/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: Devin
 *
 * Created on March 28, 2016, 1:18 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include "ahdecode.h"
 
/*
 *
 */
int main(int argc, char** argv) {
    std::string str;
    std::shared_ptr<Tree> tree;
    if (argc == 1) {
        while (std::getline(std::cin, str)) {
            tree = std::make_shared<Tree>(str);
            tree->Build(argc);
        }
        
    }
    else if (argc == 2) {
        std::string string_argv = argv[1];
        if (string_argv.compare("-s") == 0) {
            while (std::getline(std::cin, str)) {
                tree = std::make_shared<Tree>(str);
                tree->Build(argc);
            }
        }
    }
    return 0;
}

