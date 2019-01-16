//
// Created by oryakov on 1/6/19.
//

#include <fstream>
#include <vector>
#include "FileCasheManager.h"

bool FileCasheManager::isThereSolution(string problem) {
    bool res;
    //mutex1.lock();
    lock_guard<mutex> lock(mutex1);
    res = (bool) (probsAndSolutions.count(problem));
    //mutex1.unlock();
    return res;
}

string FileCasheManager::getSolution(string problem) {
    string res;
    //mutex1.lock();
    lock_guard<mutex> lock(mutex1);
    res = probsAndSolutions.at(problem);
    //mutex1.unlock();
    return res;
}

void FileCasheManager::saveSolution(string problem, string solution) {
    //mutex1.lock();
    lock_guard<mutex> lock(mutex1);
    probsAndSolutions.insert(pair<string, string> (problem, solution));
    writeSolutions();
    //mutex1.unlock();
}

void FileCasheManager::writeSolutions() {
    // writing on a text file
    if (probsAndSolutions.empty()) {
        return;
    }
    ofstream fileWriter("solutions.txt");
    if (fileWriter.is_open()) {
        for (map<string, string>::iterator it = probsAndSolutions.begin();
             it != probsAndSolutions.end(); ++it) {

            //fileWriter << "problem:";
            fileWriter << (it->first) << ";";
            //fileWriter << "solution:";
            fileWriter << (it->second) << ";\n";
        }
        fileWriter.close();
    } else cout << "Unable to open file";
}

void FileCasheManager::loadSolutions() {
    string problem, solution;
    vector<string> details = {problem, solution};
    string line;
    ifstream fileReader("solutions.txt");
    string delimiter = ";";
    string token;
    if (fileReader.is_open()) {
        while (fileReader.good()) {
            getline(fileReader, line);
            if (line.empty()) {
                break;
            }
            int pos = 0;
            int detailsIndex = 0;
            while ((pos = line.find(delimiter)) != string::npos) {
                token = line.substr(0, pos);
                details[detailsIndex] = token;
                ++detailsIndex;
                line.erase(0, pos + delimiter.length());
            }
//            if (probsAndSolutions.count(details[0])) {
//                continue;
//            }
            problem = details[0];
            solution = details[1];
            probsAndSolutions[problem] = solution;
        }
        fileReader.close();
    } else {
        return;
    }
}

FileCasheManager::FileCasheManager() {
    //mutex1.lock();
    lock_guard<mutex> lock(mutex1);
    loadSolutions();
    //mutex1.unlock();
}



