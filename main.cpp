#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int main() {
  int numCows = 0, tStart = 0, tEnd = 0, totalTime = 0, timePassed = 0, maxTime;
  vector<pair<int, int>> schedule; //Storing all events in the schedule. List of different pairs: {time, lifeguard number}
  vector<int> timeWorked; //Storing the time worked alone for each lifeguard
  vector<int> currentlyWorking; //Storing which lifeguard(s) is currently working

  cout<<"Input:"<<endl; //Scan for N
  cin >> numCows;

  if(numCows > 100 || numCows < 1){ //Ensure that N is in the appropriate range
    cout <<"Invalid input!" <<endl;
    return 1;
  }

  for(int i = 0; i < numCows; i++){ //Scan for each lifeguard's start and end time. Runtime: O(N)
    cin >> tStart >> tEnd;
    schedule.push_back({tStart, i});
    schedule.push_back({tEnd, i});
    timeWorked.push_back(0);
  }

  sort(schedule.begin(), schedule.end()); //Sort events by the time they occur. Runtime: O(Nlog(N))

  currentlyWorking.push_back(schedule.at(0).second); //Earliest event runs first

  for(int j = 1; j < schedule.size(); j++){ //Iterate through all events in the schedule (after first). Runtime: O(N)
    timePassed = schedule.at(j).first-schedule.at(j-1).first; //Calculate time passed since last event.

    if(currentlyWorking.size() > 0){ //If there are lifeguards on duty, increment total amount of time covered.
      totalTime += timePassed;
    }

    if(currentlyWorking.size() == 1){ //If only one lifeguard is on duty, increment their particular time spent alone
      timeWorked.at(currentlyWorking.at(0)) += timePassed;
    } 
    
    if(find(currentlyWorking.begin(), currentlyWorking.end(), schedule.at(j).second) == currentlyWorking.end()){ //If the current lifeguard is not on duty, push to be working. "Clock in"
      currentlyWorking.push_back(schedule.at(j).second); // O(N)
    } else { //If the current lifeguard is on duty, and another event is detected in the schedule, they stop working. "Clock out"
      currentlyWorking.erase(find(currentlyWorking.begin(), currentlyWorking.end(), schedule.at(j).second)); //O(N)
    }

  }

  maxTime = totalTime - *min_element(timeWorked.begin(), timeWorked.end()); //Max tme that can still be covered is the total time minus the lifeguard who spent the least time alone.

  cout << "Output:\n"<<maxTime <<endl;


  return 0;
}

//Implementation runtime: O(N^2)
