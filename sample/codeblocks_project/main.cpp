// g++ -c xgboost_classifier.cpp -o xgb_c.o
// g++ -c xgboost_regressor.cpp -o xgb_r.o
// g++ -std=c++11 main.cpp -I./ -o test xgb_c.o xgb_r.o
// ./test

#include <iostream>
#include "xgboost_classifier.h"
#include "xgboost_regressor.h"
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

    // Regression test
    cout << "Start regression." << endl;
    
    test_sample = {
        -0.0016666666666666904, -0.0668518518518519, 0.018124999999999978,
       0.10351851851851848, -0.013125000000000024, 0.09703703703703699,
       0.021249999999999977, -0.06129629629629634, -0.024583333333333356,
       -0.07240740740740745, 1.250996173937358, 1.5632783693080987,
       0.3273181103443364, 0.23735363332356418, 1.6726289334343811,
       1.2316100868318476, 0.20377132592362593, 1.027838760908221,
       1.9099825667579455, 0.2446893370421753, 1.3379751193714342,
       1.5589281971761841, 0.24330398118549879, 1.315624215990686,
       1.5826644564136092, 1.4901161193847656e-08, 1.4901161193847656e-08,
       3.141592638688632, 1.3185890322659237, 0.3346538140629468,
       1.4883498072609227, 1.8065823504935967, 0.2877854550824648,
       1.0472248480137314, 1.6726289334343811, 1.027838760908221,
       0.44112495924719125, 1.3379751193714342, 1.315624215990686,
       0.48799331822767306, 0.03125, 0.006481481481481481,
       0.04583333333333333, 0.011111111111111112, 0.9662725445360024,
       1.4702680482603403, 1, 1, 1, 1
    };

    float reg_result = xgb_regress(test_sample);
    cout << "Regression result:" << reg_result << endl;

    return 1;
}
