//
// Created by oryakov on 1/6/19.
//

#ifndef MILESTONE2_FILECASHEMANAGER_H
#define MILESTONE2_FILECASHEMANAGER_H

#include <map>
#include <mutex>
#include "CacheManager.h"

class FileCasheManager : public CacheManager<string, string> {

    map<string, string> probsAndSolutions;
    mutex mutex1;
public:
    FileCasheManager();

    virtual bool isThereSolution(string problem);

    virtual string getSolution(string problem);

    virtual void saveSolution(string problem, string solution);

    void writeSolutions();

    void loadSolutions();
};


#endif //MILESTONE2_FILECASHEMANAGER_H
