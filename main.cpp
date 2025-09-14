#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>
#include <unordered_set>
#include "Blurb.h"
#include "Similarity.h"
#include "CLI11.hpp"
#include "JsonService.h"
#include <nlohmann/json.hpp>
using namespace std;

static vector<string> shell_split(const string &line) {
    std::vector<std::string> out;
    std::string cur;
    bool in_single = false, in_double = false;

    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];

        if (in_single) {
            if (c == '\'') in_single = false; else cur.push_back(c);
        } else if (in_double) {
            if (c == '"') in_double = false;
            else if (c == '\\' && i + 1 < line.size()) { // simple escape in double quotes
                cur.push_back(line[++i]);
            } else {
                cur.push_back(c);
            }
        } else {
            if (std::isspace(static_cast<unsigned char>(c))) {
                if (!cur.empty()) { out.push_back(cur); cur.clear(); }
            } else if (c == '\'') {
                in_single = true;
            } else if (c == '"') {
                in_double = true;
            } else {
                cur.push_back(c);
            }
        }
    }
    if (!cur.empty()) out.push_back(cur);
    return out;
}
string run_wordmuse(const string& exePath, const string& term) {
    string cmd = "\"" + exePath + "\" " + term;
    string output;
    FILE* pipe = _popen(cmd.c_str(), "r");
    if (!pipe) return "";
    char buf[4096];
    while (fgets(buf, sizeof(buf), pipe)) output += buf;
    _pclose(pipe);
    return output;
}

int main() {

    cout << "Welcome to tyour Idea Tagger CLI Program!" << endl <<
            "Required for program: blurbs.json\n" <<
            "Type a command:\n" <<
            "--blurb <text>: Write a blurb of text!" << endl <<
            "--print: Print all your blurbs." << endl <<
            "--score: Get similarity score between your last 2 blurbs." << endl <<
            "--words: Get similar words for your last 1 blurb." << endl <<
            "--graph: Generate graph of all blurbs."  << endl <<
            "--quit: Save blurbs to JSON and quit program.\n";

    JsonService j;
    cout << 1 << endl;
    vector<Blurb> allBlurbs = {};
    cout << 2 << endl;
    vector<Blurb> newBlurbs = {};
    cout << 3 << endl;
    j.readInBlurbs(allBlurbs);
    cout << 4 << endl;
    Similarity sim;
    cout << 5 << endl;

    string line;
    while (true) {
        cout << "> ";
        getline(cin, line);
        if (line.empty()) continue;

        // 1) Tokenize with quote support
        std::vector<std::string> tokens = shell_split(line);

        // 2) Build argc/argv for CLI11 (or use parse_from if you prefer)
        int argc = static_cast<int>(tokens.size()) + 1;
        std::vector<char*> argv(argc);
        argv[0] = const_cast<char*>("program");
        for (size_t i = 0; i < tokens.size(); ++i)
            argv[i + 1] = const_cast<char*>(tokens[i].c_str());

        CLI::App app{"Interactive CLI for finding similarity between ideas."};
        string user_input;
        bool print = false;
        bool score = false;
        bool words = false;
        bool graph = false;
        bool quit = false;

        app.add_option("--blurb", user_input, "Prompt text");
        app.add_flag("--print", print, "Print all your blurbs.");
        app.add_flag("--score", score, "Get similarity score between your last 2 blurbs.");
        app.add_flag("--words", words, "Get similar words for your last 1 blurb.");
        app.add_flag("--graph", graph, "Generate graph of all blurbs.");
        app.add_flag("--quit", quit, "Save blurbs to JSON and quit program.");

        try {
            app.parse(argc, argv.data());

            if (!user_input.empty()) {
                cout << "You entered: " << user_input << "\n";
                string id = to_string(allBlurbs.size() + 1);
                Blurb a(id, user_input);
                newBlurbs.push_back(a);
                allBlurbs.push_back(a);
            }
                

            if (print) {
                cout << "All Blurbs:\n";
                for (Blurb b : allBlurbs) {
                    cout << b.id << ". " << b.text << endl;
                }
            }
            if (score) {
                if (allBlurbs.size() < 2) {
                    cout << "Not enough blurbs to run command." << endl;
                }
                else {
                    int first = allBlurbs.size() - 1;
                    int second = allBlurbs.size() - 2;

                    cout << "Comparing..." << endl;
                    cout << "Blurb #1: " << allBlurbs[first].text << endl;
                    cout << "Blurb #2: " << allBlurbs[second].text << endl;


                    cout << "Cosine score: " << sim.getCosine(allBlurbs[first], allBlurbs[second]) << endl;
                    cout << "Jaccard score: " << sim.getJaccard(allBlurbs[first], allBlurbs[second]) << endl;
                }
            }
            if (words) {
                
                if (allBlurbs.size() < 1) {
                    cout << "No blurbs." << endl;
                }
                else {
                    cout << "Finding similar words...\n";
                    Blurb b = allBlurbs[allBlurbs.size() - 1];
                    sim.preprocess(b);
                    string term = b.procText;
                    string stdoutText = run_wordmuse("wordmuse.exe", term);
                    cout << "Go output:\n" << stdoutText << "\n";
                }

                
            }
            if (graph) {
                if (allBlurbs.size() < 1) {
                    cout << "No blurbs." << endl;
                }
                else {            
                    cout << "Making graph...\n";

                }
            }
            if (quit) {
                cout << "Saving..." << endl;
                j.writeBlurbs(newBlurbs);
                cout << "Exiting...\n";
                break;
            }
            
        } 
        
        catch (const CLI::ParseError &e) {
            // This prints help/error text and returns an exit code
            int exitcode = app.exit(e);
            if (exitcode != 0) {
                // nonzero means it was a real error, not just --help
                std::cerr << "Error code: " << exitcode << "\n";
            }
            continue;
        }

    }

    return 0;
}


