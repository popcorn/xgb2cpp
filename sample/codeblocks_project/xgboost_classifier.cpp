#include "xgboost_classifier.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

std::vector<float> xgb_classify(std::vector<float> &sample) {

  std::vector<float> sum (2, 0.0);

  if (sample[0] <127.5) {
    if (sample[1] <30.5) {
      if (sample[3] <45.4) {
        sum[0] += 0.848889;
      } else {
        sum[0] += -0.333333;
      }
    } else {
      if (sample[4] <26.95) {
        sum[0] += 0.870968;
      } else {
        sum[0] += 0.0727273;
      }
    }
  } else {
    if (sample[2] <29.95) {
      if (sample[5] <26.5) {
        sum[0] += 0.882353;
      } else {
        sum[0] += 0.162791;
      }
    } else {
      if (sample[6] <157.5) {
        sum[0] += -0.208791;
      } else {
        sum[0] += -0.73913;
      }
    }
  }


  if (sample[0] <127.5) {
    if (sample[1] <30.5) {
      if (sample[3] <45.4) {
        sum[1] += -0.848889;
      } else {
        sum[1] += 0.333333;
      }
    } else {
      if (sample[4] <26.95) {
        sum[1] += -0.870968;
      } else {
        sum[1] += -0.0727273;
      }
    }
  } else {
    if (sample[2] <29.95) {
      if (sample[5] <26.5) {
        sum[1] += -0.882353;
      } else {
        sum[1] += -0.162791;
      }
    } else {
      if (sample[6] <157.5) {
        sum[1] += 0.208791;
      } else {
        sum[1] += 0.73913;
      }
    }
  }


  if (sample[0] <106.5) {
    if (sample[1] <0.6595) {
      if (sample[3] <37.3) {
        sum[0] += 0.556873;
      } else {
        sum[0] += 0.0642629;
      }
    } else {
      if (sample[4] <4.5) {
        sum[0] += 0.198106;
      } else {
        sum[0] += -0.623913;
      }
    }
  } else {
    if (sample[2] <24.5) {
      if (sample[5] <192.5) {
        sum[0] += 0.211633;
      } else {
        sum[0] += 0.757859;
      }
    } else {
      if (sample[6] <42.2) {
        sum[0] += -0.066408;
      } else {
        sum[0] += -0.606597;
      }
    }
  }


  if (sample[0] <106.5) {
    if (sample[1] <0.6595) {
      if (sample[3] <37.3) {
        sum[1] += -0.556873;
      } else {
        sum[1] += -0.0642628;
      }
    } else {
      if (sample[4] <4.5) {
        sum[1] += -0.198106;
      } else {
        sum[1] += 0.623913;
      }
    }
  } else {
    if (sample[2] <24.5) {
      if (sample[5] <192.5) {
        sum[1] += -0.211633;
      } else {
        sum[1] += -0.757859;
      }
    } else {
      if (sample[6] <42.2) {
        sum[1] += 0.066408;
      } else {
        sum[1] += 0.606597;
      }
    }
  }


  return sum;
}

