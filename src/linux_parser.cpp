#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
// is memory utilization (TotalMem - FreeMem) / TotalMem??
// finished
float LinuxParser::MemoryUtilization() { 
  string line;
  string key;
  // float value;
  float Total_mem, Free_mem, line_value;
  
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()){ 
    while (std::getline(filestream, line)){
      std::istringstream linestream(line);
      while (linestream >> key >> line_value){
        if (key == "MemTotal"){
          Total_mem = line_value;
        }
        else if (key == "MemFree"){
          Free_mem = line_value;
          }
      }
    }
    
  }
  return float (Total_mem-Free_mem)/Total_mem; 
}

// TODO: Read and return the system uptime
// Up_time = first number, Idle_time relevant??
// finished
long LinuxParser::UpTime() {
  string line;
  string Up_time; 
  string Idle_time;
  
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)){
      std::istringstream linestream(line);
      while (linestream >> Up_time >> Idle_time) {
        return std::stol(Up_time);
      }
    }
  }
  
  return 0;
  
}
      
    


// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  
  
  
  return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<float> LinuxParser::CpuUtilization(int pid) { 
  
  vector<float> cpuValues{};
  string line;
  float time = 0;
  string value;
  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      for (int i = 1; i <= kStarttime_; i++) {
        linestream >> value;
        if (i == kUtime_ || i == kStime_ || i == kCutime_ || i == kCstime_ || i == kStarttime_) {
          // read in clock ticks and convert to seconds
          // devide by clock ticks per second
          time = std::stof(value) / sysconf(_SC_CLK_TCK);
          cpuValues.push_back(time);
        }
      }
    }
  }
  return cpuValues;
}
  

// TODO: Read and return the total number of processes
//finished
int LinuxParser::TotalProcesses() { 
  
  string line;
  string key;
  string value;
  int Total_processes;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)){
      std::istringstream linestream(line);
      while (linestream >> key >> value){
        if (key == "processes"){
          Total_processes = stoi(value);
          return Total_processes;
        }
      }
    }
  }
    return Total_processes;
}

 
         

// TODO: Read and return the number of running processes
// finished
int LinuxParser::RunningProcesses() {
  string line;
  string key;
  int value;
  int Running_procs;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)){
      std::istringstream linestream(line);
      while (linestream >> key >> value){
        if (key == "procs_running"){
          Running_procs = value;
          return Running_procs;
        }
      }
    }
  }
   
  return Running_procs; 
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
// finished
string LinuxParser::Command(int pid[[maybe_unused]]) { 
  
  string value = "";
  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) + kCmdlineFilename);
  if (filestream.is_open()) {
    std::getline(filestream, value);
    return value;
  }
  return value;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
// unsure how to call pid??
//finished
string LinuxParser::Ram(int pid) {
  
  string line;
  string key, value;
  string mem_process;
  string pid_string;
  
  pid_string = to_string(pid);
    
  std::ifstream filestream(kProcDirectory + pid_string + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "VmSize:") {
          mem_process = value;
          return mem_process;
        }
      }
    }
  }
  return mem_process;
}

  




// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
// finished
string LinuxParser::Uid(int pid) {
  
  string line;
  string key, value;
  string user_id;
  string pid_string;
  
  pid_string = to_string(pid);
    
  std::ifstream filestream(kProcDirectory + pid_string + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "Uid") {
          user_id = value;
          return user_id;
        }
      }
    }
  }
  return user_id;
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
//finished
string LinuxParser::User(int pid) { 
  
  // read the user ID for this process
  string uid = Uid(pid);
  string line;
  string key;
  string value = "";
  string other;
  // find user name for this user ID in /etc/passwd
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> value >> other >> key) {
        if (key == uid) {
          return value;
        }
      }
    }
  }
  return value;
}
  
  


// TODO: Read and return the uptimeof a process
// REM OVE: [[maybe_unused]] once you define the function
//NOT finished

long LinuxParser::UpTime(int pid) {
  string line;
  long uptime = 0;
  string value;
  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      for (int i = 1; i <= kStarttime_; i++) {
        linestream >> value;
        if (i == kStarttime_) {
          // read the starttime value in clock ticks and convert to seconds
          // devide by clock ticks per second
          uptime = std::stol(value) / sysconf(_SC_CLK_TCK);
          return uptime;
        }
      }
    }
  }
  return uptime;
}


// Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  vector<string> cpuValues{};
  string line;
  string key;
  string vuser, vnice, vsystem, vidle, viowait, virq, vsoftirq, vsteal, vguest,
      vguest_nice;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> vuser >> vnice >> vsystem >> vidle >>
             viowait >> virq >> vsoftirq >> vsteal >> vguest >> vguest_nice) {
        if (key == "cpu") {
          cpuValues.push_back(vuser);
          cpuValues.push_back(vnice);
          cpuValues.push_back(vsystem);
          cpuValues.push_back(vidle);
          cpuValues.push_back(viowait);
          cpuValues.push_back(virq);
          cpuValues.push_back(vsoftirq);
          cpuValues.push_back(vsteal);
          cpuValues.push_back(vguest);
          cpuValues.push_back(vguest_nice);
          return cpuValues;
        }
      }
    }
  }
  return {};
}
                                                  
                                              