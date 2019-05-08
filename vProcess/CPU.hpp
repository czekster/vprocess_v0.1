/**
 * virtual process simulator (vprocess-v0.1)
 * Date: 08/05/2019
 * Author: Ricardo M. Czekster - rczekster@gmail.com
 * Description: class CPU header
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

#ifndef CPU_HPP
#define CPU_HPP

#include "Defs.hpp"

class CPU {
   public:
      CPU();
      ~CPU();
      void addProcess(Process* p);
      Process* getProcess(long pid);
      void showProcesses(bool log2file, bool compact);
      double getTotalMemory();
      void setTotalMemory(double tm);
      double getUsedMemory();
      void useMemory(double amount);
      void freeMemory(double amount);
      void setRandomGenerator(RandomGenerator* r);
      long randomProcessSelection();
      uint getExecProcessesSize();
      bool hasMemory();
      string memStats();                // memory statistics
      string procStats();               // process statistics
      // microcodes for CPU
      void createPVM();
      void createNative();
      void createVM();
      void runProcExec();
      void runProcDepart();
      void runProcInv();
   protected:
   private:
      list<Process*> processes;         // list of processes in the system
      double totalMemory;                // maps the total amount of memory
      double usedMemory;                 // saves the amount of memory being used
      long nextPID;                     // next PID number for this CPU
      RandomGenerator* randGen;         // a reference to the same random generator in the simulator
      Process* newProcess();            // basic creation of any process in the CPU
      int lossesByMemory;
};

#endif // CPU_HPP
