#include "CO2_ordering_new.h"
#include <iostream>

std::vector<int> CO2_ordering_new(std::vector<int>& tags, int b) {
    std::vector<int> new_tags = tags;

    int temp = tags[b-1];

    // Shift the second element of each block to the next block
    for (int i = 1; i < b-2 ; i = i+2) {
        new_tags[i+2] = tags[i];
    }

    // Place the stored element from the last block into the first block
    new_tags[1] = temp;

    return new_tags;

}

//std::vector<int> CO2_ordering_new(std::vector<int>& tags, int it, int b) {
//    std::vector<int> ori_tags = tags;
//
//    if (it % 2 == 0) { // Even case
//        for (int i = 0; i <= b - 4; i += 2) {
//            if (i == 2) {
//                tags[i] = ori_tags[5];
//            } else if (i == 4) {
//                tags[i] = 4;
//                tags[5] = ori_tags[6];
//            } else {
//                tags[i] = ori_tags[i + 2];
//            }
//        }
//        tags[b - 2] = ori_tags[0];
//    } else { // Odd case
//        for (int i = 3; i < b; i += 2) {
//            tags[i] = ori_tags[i - 2];
//        }
//        tags[1] = ori_tags[b-1];
//    }
//
//    return tags;
//
//}
