//
// Created by Kirill on 12/18/2020.
//

#include <chrono>
#include <iostream>
#include "tset.h"

int main() {
    for (int i = 100; i < 1000000000; i *= 10) {
        TSet *set = new TSet(i);
        auto start_time = std::chrono::steady_clock::now();
        for (int j = 0; j < 99; ++j) {
            set->InsElem(j);
        }
        auto end_time = std::chrono::steady_clock::now();
        auto insert = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);

        start_time = std::chrono::steady_clock::now();
        for (int j = 0; j < 99; ++j) {
            set->DelElem(j);
        }
        end_time = std::chrono::steady_clock::now();
        auto delet = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
        std::cout << "set of " << i << " elements   [insert - " << insert.count() << "ns] " << " [delete - "
                  << delet.count() << "ns] \n";

    }

    return 1;
}