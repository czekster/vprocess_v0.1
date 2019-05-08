/**
 * virtual process simulator (vprocess-v0.1)
 * Date: 08/05/2019
 * Author: Ricardo M. Czekster - rczekster@gmail.com
 * Description: definition file, containing all simulation project types, headers and cross-references
 *
 */

/*
This is vProcess - an accompanying software for the paper entitled 
"Opportunities and challenges when introducing interdisciplinarity 
issues in systems engineering courses: a case study with a constrained 
project time frame".
https://dx.doi.org/10.13140/RG.2.2.29133.90081

Copyright (C) 2019-?  Ricardo M. Czekster
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation,
Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
*/

#ifndef __DEFS_HPP__
#define __DEFS_HPP__

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
#include <unistd.h> // for usleep

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <list>
#include <string>

using namespace std;

typedef unsigned int uint;
typedef unsigned long ulong;

class Process;
class Simulator;
class CPU;
class Event;
class Logger;
class RandomGenerator;
class Utils;
class Statistics;

extern Logger* logger;
extern Logger* auxlogger;
extern Logger* memlogger;
extern Logger* proclogger;

/** Project constants - maps to enum discreteevent (defined below) */
const char MAX_EVENTS           = 6;        // total number of events in this DES
const char PRECISION            = 0;        // used to print large values without precision (if set to 0)
const char COLUMN_WIDTH         = 10;       // used in Logger = column width
const string LOG_DIR            = "logs";   // used by the logger to create lots of files of logging
const uint LOG_MEMORY_COUNTER   = 1;        // when to output memory
const uint TOTAL_SIM_EXECUTIONS = 10;

// instructions constants
const uint TOTAL_NUM_INSTR   = 100000;      // total number of instructions for a process
const uint INITIAL_NUM_INSTR = 10000;       // the minimum size for every process
const uint EXEC_NUM_INSTR    = 1000;        // maximum number of executed instructions per event
const uint MINIMUM_INSTR     = 500;         // minimum number of instructions that ARE executed

// CPU internals
const double TOTAL_MEMORY     = 444.0 * 1024.0 * 1024.0 * 1024.0; // 2 gigabytes

const double MINIMUM_MEMORY   = 100.0 * 1024.0;                   // MEMORY size variation for each new process

const double MEMORY_PVM_PROC  = 5.0 * 1024.0 * 1024.0;            // from 0 to 5 megabytes of memory for PVM processes
const double INITIAL_PVM_MEM  = 1.0 * 1024.0;

const double MEMORY_VM_PROC   = 10.0 * 1024.0 * 1024.0;           // from 0 to 10 additional Mb of memory for PVM processes
const double INITIAL_VM_MEM   = 20.0 * 1024.0 + 60.0 * 1024.0;    // 20 Mb for the VMM + 60 Mb for the actual VM

const double MEMORY_NAT_PROC  = 500.0 * 1024.0;                   // from 0 to 1 megabyte of memory for PVM processes
const double INITIAL_NAT_MEM  = 50.0 * 1024.0 * 1024.0;

const char TOTAL_CPU_CORES   = 1;                         // cores, to execute several processes in parallel
const int TOTAL_PROCESSES   = 100;                        // # of initial processes that the CPU starts executing NATIVE processes

/** Project statistics */
const char TOTAL_STATISTICS    = 12;
//--------------------------------//
const char STAT_TOTAL_TIME     =  0;
const char STAT_TOTAL_EVENTS   =  1;
//--------------------------------//
const char STAT_EVT_PA_PVM     =  2;
const char STAT_EVT_PA_NATIVE  =  3;
const char STAT_EVT_PA_VM      =  4;
const char STAT_EVT_PE         =  5;
const char STAT_EVT_PD         =  6;
const char STAT_EVT_PI         =  7;
//--------------------------------//
const char STAT_AVERAGE_MEM    =  8;    // average memory for the CPU considering all processes (divided by total events)
const char STAT_AVERAGE_PROCS  =  9;    // average number of processes in the CPU (divided by total events)
const char STAT_EXECUTION_TIME = 10;    // simulation execution time (in SECONDS)




/** Process bound characteristic */
enum procbound {
   PBOUND_IO,           // IO-bound process
   PBOUND_CPU           // CPU-bound process
};

/** Process type within the simulation */
enum proctype {
   PTYPE_PVM,            // process virtual machine (e.g. application server, JVM or CLR)
   PTYPE_NATIVE,         // native process, or service
   PTYPE_VM              // virtual machine manager process (e.g. VirtualBox or VMware)
};

/** Process status */
enum procstatus {
   PSTAT_EXECUTING,      // process is still executing (it has not finished its number of instructions)
   PSTAT_FINISHED,       // process is finished
   PSTAT_INVALID         // process is invalid, with error, or other erroneous situation
};

/** System discrete events for the simulation */
enum discreteevent {
   EVT_PA_PVM = 0,       // process arrival of a process virtual machine
   EVT_PA_NATIVE = 1,    // process arrival of a native process
   EVT_PA_VM = 2,        // process arrival of a virtual machine manager process
   EVT_PE = 3,           // process execution event
   EVT_PD = 4,           // process departure event
   EVT_PI = 5            // process in invalid state event
};

#endif // __DEFS_HPP__
