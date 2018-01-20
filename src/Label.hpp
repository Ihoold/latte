//
// Created by ihoold on 20.01.18.
//

#ifndef INSTANT_LABEL_HPP
#define INSTANT_LABEL_HPP

#include <utility>
#include <vector>
#include <string>

class Label {
    int labelNum;
    std::vector<int> preds;
public:
    Label(int num, std::vector<int> preds_);
    std::string getCode();
    int getLabelNum();
};

#endif //INSTANT_LABEL_HPP
