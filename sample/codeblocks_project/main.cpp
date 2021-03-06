#include <iostream>
#include "xgboost_classifier.h"
#include <chrono>
#include <math.h>

using namespace std;

std::vector<float> get_probabilities(std::vector<float> &log_probabilities) {
    float sum = 0;

    std::vector<float> probabilities (log_probabilities.size(), 0);

    for (std::vector<float>::const_iterator i = log_probabilities.begin(); i != log_probabilities.end(); ++i) {
        sum += exp(*i);
    }

    for (unsigned int i = 0; i < log_probabilities.size(); i++) {
        probabilities[i] = exp(log_probabilities[i]) / sum;
    }

    return probabilities;
}

int main()
{

    // Number of features we have in our samples (PIMA INDIANS DIABETES)
    int FEATURE_NUMBER = 8;

    std::vector<float> test_sample(8, 0);
    std::vector<float> result = xgb_classify(test_sample);
    result = get_probabilities(result);
    cout << "TEST SAMPLE (ALL ZEROS)" << endl;
    cout << "class 0 probability: " << result[0] << endl;
    cout << "class 1 probability: " << result[1] << endl << endl;

    // Generate random samples to test classifier speed
    std::vector<std::vector<float>> samples;
    int NUM_SAMPLES = 10000;

    for (int i = 0; i < NUM_SAMPLES; i++) {
        std::vector<float> sample (FEATURE_NUMBER, 0);
        for (unsigned int j = 0; j < sample.size(); j++) {
            sample.at(j) = rand() % 2;
        }
        samples.push_back(sample);
    }

    cout << "Starting classification." << endl;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    // Classify all samples
    for (unsigned int i = 0; i < samples.size(); i++) {
        std::vector<float> res = xgb_classify(samples[i]);
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    float time_diff = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / (float) 1000; // Now it's in miliseconds
    std::cout << "Classified " << NUM_SAMPLES << " samples in " << time_diff << " miliseconds." << std::endl;
    std::cout << time_diff / NUM_SAMPLES << "ms per sample." << std::endl;

    return 1;
}
