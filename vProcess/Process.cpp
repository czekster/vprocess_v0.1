/**
 * virtual process simulator (vprocess-v0.1)
 * Date: 08/05/2019
 * Author: Ricardo M. Czekster - rczekster@gmail.com
 * Description: class Process implementation
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

#include "Process.hpp"

Process::Process() {
   programCounter = 0;
}

Process::~Process() {

}

long Process::getPid() {
   return pid;
}

void Process::setPid(long p) {
   pid = p;
}

void Process::setBound(procbound b) {
   bound = b;
}

void Process::setType(proctype t) {
   type = t;
}

proctype Process::getType() {
   return type;
}

void Process::setStatus(procstatus s) {
   status = s;
}

procstatus Process::getStatus() {
   return status;
}

long Process::getProgramCounter() {
   return programCounter;
}

void Process::setProgramCounter(long pc) {
   programCounter = pc;
}

void Process::decProgramCounter(long pc) {
   programCounter -= pc;
}

bool Process::isFinished() {
   return (programCounter <= 0);
}

ulong Process::getTotalInstructions() {
   return totalInstructions;
}

void Process::setTotalInstructions(ulong ti) {
   totalInstructions = ti;
}

void Process::initProgramCounter() {
   programCounter = totalInstructions;
}

ulong Process::getTotalMemory() {
   return totalMemory;
}

void Process::setTotalMemory(ulong tm) {
   totalMemory = tm;
}

/** Auxiliary function to create a unique log file for each process. Useful to follow execution. */
string Process::getLoggerName() {
   stringstream ss;
   ss << "pid" << pid;
   return ss.str();
}

/** Returns the type as a string according to the enumeration (Defs.hpp)
*/
string Process::typeStr(proctype t) {
   switch(t) {
      case PTYPE_PVM:    return "PVM";
      case PTYPE_NATIVE: return "NAT";
      case PTYPE_VM:     return "VM";
   }
   // if it reaches here, it is invalid
   return ("PTYPE INV");
}

/** Returns the type as a string according to the enumeration (Defs.hpp)
*/
string Process::statusStr(procstatus s) {
   switch(s) {
      case PSTAT_EXECUTING: return "EXEC";
      case PSTAT_FINISHED:  return "FINI";
      case PSTAT_INVALID:   return "INVA";
   }
   // if it reaches here, it is invalid
   return ("PSTAT INV");
}

/** Returns the type as a string according to the enumeration (Defs.hpp)
*/
string Process::boundStr(procbound b) {
   switch(b) {
      case PBOUND_CPU: return "CPU-B";
      case PBOUND_IO:  return "IO-B";
   }
   // if it reaches here, it is invalid
   return ("PBOUND INV");
}

string Process::toString(bool compact) {
   stringstream aux;
   if (compact == false) {
      aux << "[Process]" << endl;
      aux << "PID=" << pid << endl;
      aux << "PC=" << programCounter << endl;
      aux << "Total Memory=" << totalMemory << endl;
      aux << "Total Instructions=" << totalInstructions << endl;
      aux << "Process Bound=" << boundStr(bound) << endl;
      aux << "Process Type=" << typeStr(type) << endl;
      aux << "Process Status=" << statusStr(status) << endl;
      aux << "--" << endl;
   } else {
      //PID;PC;instr;bound;type;status
      aux << pid << ";"
          << programCounter << ";"
          << totalMemory << ";"
          << totalInstructions << ";"
          << boundStr(bound) << ";"
          << typeStr(type) << ";"
          << statusStr(status) << ";";
   }
   return aux.str();
}



