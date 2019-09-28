#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  // constructor to initialize Process with the read process-ID from filesystem
  Process(int pid);
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization() const;                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  // TODO: Declare any necessary private members
 private:
  int processId_;
  std::string user_;
  std::string command_;
  float cpuUsage_;
  std::string ram_;
  long uptime_;
  
    enum ProcessCPUStates {
    kUtime_ = 0,
    kStime_,
    kCutime_,
    kCstime_,
    kStarttime_
  };

  // calculate the CPU utilization of this process and save in cpuUsage_
  void calculateCpuUsage();
  // determine the user name that generated this process and save in user_
  void determineUser();
  // determine the command that generated this process and save in command_
  void determineCommand();
  // determine the memory utilization of that process and save in ram_
  void determineRam();
  // determine the age of this process and save in uptime_
  void determineUptime();
};
 



#endif