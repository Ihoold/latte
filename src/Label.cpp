//
// Created by ihoold on 20.01.18.
//

#include <sstream>
#include "Label.hpp"

std::string Label::getCode() {
    std::stringstream ss;
    ss << "; <label>:" << labelNum << "\t \t \t; preds = ";
    for (auto pred : preds) {
        ss << ((pred == preds.front()) ? "%" : ", %" ) << pred;
    }
    return ss.str();
}

int Label::getLabelNum() {
    return labelNum;
}

void Label::addLabel(int i) {
    preds.push_back(i);
}

Label::Label(int num, std::vector<int> preds_) : preds(std::move(preds_)), labelNum(num) {}
