
#ifndef BLURB_H
#define BLURB_H
#include <iostream>
#include <vector>
using namespace std;

struct Blurb {

    Blurb() {}

    Blurb(string i, string t) {
        id = i;
        text = t;
        isPreprocessed = false;
    }

    ~Blurb() {}

    string id;
    string text;
    vector<string> text_as_vector;
    string procText;
    bool isPreprocessed;
};

#endif