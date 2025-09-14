#include <iostream>
#include <vector>
#include <fstream>
#include "Blurb.h"
#include "JsonService.h"
#include <nlohmann/json.hpp>
using nlohmann::json;
using namespace std;

    JsonService::JsonService() {}
    JsonService::~JsonService() {}

    void JsonService::readInBlurbs(vector<Blurb>& allBlurbs) {
        cout << 1 << endl;
        {
            std::ifstream ifs("blurbs.json");
            if (ifs.good()) {
                ifs >> doc;
            }
        }
        cout << 2 << endl;
        auto it = doc.find("blurbs");
        if (it == doc.end() || !it->is_array()) {
            cout << "No Blurbs currently in JSON" << endl;
            return;
        }
        cout << 3 << endl;
        allBlurbs.reserve(it->size());
        for (const auto& item : *it) {
            if (!item.is_object()) continue;     
            cout << 4 << endl;
            Blurb b(item.value("id",   std::string{}), 
                    item.value("text", std::string{}));
            if (!b.id.empty()) allBlurbs.push_back(std::move(b));
        }
    }

    void JsonService::writeBlurbs(vector<Blurb>& newBlurbs) {
        if (newBlurbs.empty()) {
            return;
        }

        {   std::ifstream in("blurbs.json");
            if (in) in >> doc;
        }

        if (!doc.contains("blurbs") || !doc["blurbs"].is_array())
            doc["blurbs"] = json::array();

        for (Blurb b : newBlurbs) {
            doc["blurbs"].push_back({ {"id", b.id}, {"text", b.text} });
        }

        ofstream out("blurbs.json");
        out << setw(2) << doc << '\n';
        
    }

    void JsonService::graphToJSON() {}
        //writes graphs to JSON
        //writes them with an id

    Blurb JsonService::getBlurb(int id, vector<Blurb> allBlurbs) {
        return allBlurbs[id];
    }

    vector<Blurb> JsonService::getLastTwoBlurbs(vector<Blurb> allBlurbs) {
        if (allBlurbs.size() < 2) {
            cout << "Not enough blurbs to compare." << endl;
            return {};
        }
        return {allBlurbs[allBlurbs.size() - 1], allBlurbs[allBlurbs.size() - 2]};
    }


        //writes graphs to JSON
        //writes them with an id



