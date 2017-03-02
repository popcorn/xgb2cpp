#ifndef XGBOOST_CLASSIFIER_H  // To make sure you don't declare the function more than once by including the header multiple times.
#define XGBOOST_CLASSIFIER_H

#include <vector>

std::vector<float> xgb_classify(std::vector<float> &sample);

#endif
