#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool btsearch(const AvailabilityMatrix& avail, size_t dailyNeed, 
              size_t maxShifts, DailySchedule& sched, 
              size_t row, size_t col, vector<size_t>& numShift){
    size_t days = avail.size();
    size_t workers = avail[0].size();
    if(row == days) return true;
    else{
        size_t nextRow = row;
        size_t nextCol = col + 1;
        if(nextCol == dailyNeed){
            nextCol = 0;
            nextRow++;
        }
        for(size_t i = 0; i < workers; i++){
            bool assigned = false;
            for(size_t j = 0; j < col; j++){
                if(sched[row][j] == i){
                    assigned = true;
                    break;
                }
            }   
            if(avail[row][i] && numShift[i] < maxShifts){
                if(assigned == false){
                    sched[row][col] = i;
                    numShift[i]++;
                    bool btresult = btsearch(avail, dailyNeed, maxShifts, 
                                             sched, nextRow, nextCol, numShift);
                    if(btresult == true) return true;
                    else{
                        sched[row][col] = INVALID_ID;
                        numShift[i]--;
                    }
                }
            }
        }
    }
    return false;
}

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    if(avail[0].size() == 0U){
        return false;
    }
    size_t days = avail.size();
    size_t workers = avail[0].size();
    sched.clear();
    sched.resize(days, vector<Worker_T>(dailyNeed, INVALID_ID));
    vector<size_t> numShift(workers, 0);
    return btsearch(avail, dailyNeed, maxShifts, sched,
                    0, 0, numShift);
}

