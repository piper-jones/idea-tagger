#ifndef SIMILARITY_H
#define SIMILARITY_H

#include <string>
#include <vector>
#include <unordered_set>
#include "Blurb.h"

class Similarity {
public:
    Similarity();
    ~Similarity();

    void preprocess(Blurb &blurb);

    float getJaccard(Blurb& blurb_A, Blurb& blurb_B);
    float getCosine (Blurb& blurb_A, Blurb& blurb_B);

private:
    // Declare only; define in Similarity.cpp
    static const std::unordered_set<std::string> kFillerWords;
};

#endif // SIMILARITY_H
