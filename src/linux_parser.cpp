#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

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
  return (Total_mem-Free_mem)/Total_mem; 
}

// TODO: Read and return the system uptime
// Up_time = first number, Idle_time relevant??
long LinuxParser::UpTime() {
  string line;
  float Up_time; 
  float Idle_time;
  int final_uptime;
  
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> Up_time >> Idle_time;
  }
  final_uptime = int(Up_time);
  return long(final_uptime);
  
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
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  
  string line;
  string key;
  string value;
  int Total_processes;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)){
      std::istringstream linestream(line);
      while (linestream >> key >> value){
        if (key == "processes"){
          Total_processes = stoi(value);
        }
      }
    }
  }
    return Total_processes;
}

 
         

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string line;
  string key;
  string value;
  int Running_procs;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)){
      std::istringstream linestream(line);
      while (linestream >> key >> value){
        if (key == "procs_running"){
          Running_procs = stoi(value);
        }
      }
    }
  }
   
  return Running_procs; 
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { 
  
  string command;
  
  return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
// unsure how to call pid??
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
        }
      }
    }
  }
  return mem_process;
}

  




// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
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
        }
      }
    }
  }
  return user_id;
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  
  string line;
  string key1, key2;
  string value;
  string user_process;
  string user_id = LinuxParser::Uid(pid);
  
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ":", " ");
      std::istringstream linestream(line);
      while (linestream >> value >> key1 >> key2) {
        if (key2 == user_id) {
          std::replace(line.begin(), line.end(), " ", ":");
          user_process = value;
        }
      }
    }
  }
  return user_process;
}
  
  
  


// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }