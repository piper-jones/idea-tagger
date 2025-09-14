#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include<cctype>
#include <cmath>
#include "Blurb.h"
#include "Similarity.h"
using namespace std;

    Similarity::Similarity() {}
    Similarity::~Similarity() {}

    
    //takes text, preprocceses it, assigns it to blurb.text_as_vector
    void Similarity::preprocess(Blurb &blurb) {
        vector<string> processed_text;
        string processed_string;

        string text = blurb.text;
        stringstream ss(text);
        string word;

        while (ss >> word) {
            for (int i = word.size() - 1; i >= 0; --i) {
                //Get rid of special characters
                if (!isalnum(word[i])) {
                    word.erase(i, 1);
                }
                else {
                    //Make all text lowercase
                    word[i] = tolower(word[i]);
                }
            }
            if (kFillerWords.find(word) == kFillerWords.end()) {
                processed_text.push_back(word);
                processed_string += word + "+";
            }
        }
        blurb.text_as_vector = processed_text;
        processed_string.pop_back();
        blurb.procText = processed_string;
        blurb.isPreprocessed = true;
    }

    float Similarity::getJaccard(Blurb& blurb_A, Blurb& blurb_B) {

        
        if (!blurb_A.isPreprocessed) preprocess(blurb_A);
        if (!blurb_B.isPreprocessed) preprocess(blurb_B);

        unordered_set<string> union_set;

        //Add all words from first blurb.
        for (string s : blurb_A.text_as_vector) {
            union_set.insert(s);
        }

        unordered_set<string> first_set = union_set;
        unordered_set<string> second_set;

        for (string s : blurb_B.text_as_vector) {
            //Make sure all words are in the union set
            union_set.insert(s);
            second_set.insert(s);
        }

        unordered_set<string> intersection_set;

        for (auto x : first_set) {
            //If the number is not also in the second blurb, remove it
            if (second_set.find(x) != second_set.end()) {
                intersection_set.insert(x);
            }
        }

        float u = union_set.size();
        float i = intersection_set.size();

        float sim_score = i / u;

        return sim_score;
    }

    float Similarity::getCosine(Blurb& blurb_A, Blurb& blurb_B) {
        

        if (!blurb_A.isPreprocessed) preprocess(blurb_A);
        if (!blurb_B.isPreprocessed) preprocess(blurb_B);

        unordered_map<string, int> freq_A;
        unordered_map<string, int> freq_B;

        for (string s : blurb_A.text_as_vector) { freq_A[s]++; }
        for (string s : blurb_B.text_as_vector) { freq_B[s]++; }

        vector<int> vector_count_A;
        vector<int> vector_count_B;

        for (auto pair : freq_A) {
            string word = pair.first;
            int freq = pair.second;
            //If the word is in both blurbs
            if (freq_B.count(word)) {
                vector_count_A.push_back(freq);
                vector_count_B.push_back(freq_B[word]);
            }
            else {
                vector_count_A.push_back(freq);
                vector_count_B.push_back(0);
            }
        }

        for (auto pair : freq_B) {
            string word = pair.first;
            int freq = pair.second;
            //If the word is in both blurbs
            if (freq_A.count(word)) {
                continue;
            }
            else {
                vector_count_A.push_back(0);
                vector_count_B.push_back(freq);
            }
        }

        float dot_product = 0;
        float magnitude_A = 0;
        float magnitude_B = 0;

        for (int i = 0; i < vector_count_A.size(); ++i) {
            float a = vector_count_A[i];
            float b = vector_count_B[i];

            dot_product += (a * b);

            magnitude_A += pow(a, 2);
            magnitude_B += pow(b, 2);
        }

        magnitude_A = sqrt(magnitude_A);
        magnitude_B = sqrt(magnitude_B);

        float sim_score = dot_product / (magnitude_A * magnitude_B);

        return sim_score;
    }

    const std::unordered_set<std::string> Similarity::kFillerWords = {
        // Articles & Determiners
        "a","an","the","this","that","these","those",

        // Pronouns
        "i","me","my","mine","you","your","yours","he","him","his",
        "she","her","hers","it","its","we","us","our","ours",
        "they","them","their","theirs",

        // Prepositions
        "about","at","by","for","from","in","of","on","to","with",

        // Conjunctions & Connectors
        "and","or","but","so","because","if","while","although","though","as",

        // Auxiliary & Helper Verbs
        "am","is","are","was","were","be","been","being",
        "do","does","did","have","has","had",
        "will","would","can","could","shall","should","may","might","must",

        // Other common fillers
        "not","no","yes","okay","ok","just","really","very","like",
        "kind of","sort of"
    };