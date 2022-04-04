#ifndef TIMER_2022_03_29
#define TIMER_2022_03_29

#include <iostream>
#include <chrono>
#include <vector>
using namespace std::chrono;

struct timer{
  system_clock::time_point start_time;
  std::vector<double> lap_time;

  timer(){
    start_time = system_clock::now();
  }

  void start(){
    start_time = system_clock::now();
  }

  double stop(){
    system_clock::time_point end = system_clock::now();
    double time = static_cast<double>(duration_cast<milliseconds>(end - start_time).count());
    return time;
  }

  void lapTime(){
    system_clock::time_point end = system_clock::now();
    double time = static_cast<double>(duration_cast<milliseconds>(end - start_time).count());
    lap_time.push_back(time);
    start_time = end;
  }

  double timeCheck(int i){
    if( lap_time.size() <= i ) return -1;
    return lap_time[i];
  }

  void print(){
    for(int i=0; i<(int)lap_time.size(); i++){
      std::cout << i+1 << ": " << lap_time[i] << "\n";
    }
  }

  void lapTimeClear(){
    lap_time.clear();
  }

  void allClear(){
    start();
    lap_time.clear();
  }

};
#endif
