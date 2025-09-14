#ifndef JsonService_H
#define JsonService_H

#include <iostream>
#include <vector>
#include "Blurb.h"
#include <nlohmann/json.hpp>

using nlohmann::json;
using namespace std;

class JsonService {
public:
    json doc;

    JsonService();
    ~JsonService();

    void readInBlurbs(vector<Blurb>& allBlurbs);
        //read in all blurbs from JSON into vector
        //!!!Called when program starts

    void writeBlurbs(vector<Blurb>& newBlurbs);
        //writes all blurbs from newBlurbs to json
        //!!!called with Close or Save from CLI

    void graphToJSON();
        //writes graphs to JSON
        //writes them with an id
    
    Blurb getBlurb(int id, vector<Blurb> allBlurbs);

    vector<Blurb> getLastTwoBlurbs(vector<Blurb> allBlurbs);


};

#endif 