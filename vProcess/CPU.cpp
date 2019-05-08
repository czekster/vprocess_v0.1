/**
 * virtual process simulator (vprocess-v0.1)
 * Date: 08/05/2019
 * Author: Ricardo M. Czekster - rczekster@gmail.com
 * Description: class CPU implementation, mapping a central processing unit in the simulation
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

#include "CPU.hpp"
#include "Process.hpp"
#include "Utils.hpp"
#include "Logger.hpp"
#include "RandomGenerator.hpp"

CPU::CPU() {
   nextPID = 0;
   totalMemory = TOTAL_MEMORY;
   usedMemory = 0;
   // starts executing a certain amount of processes
   for (int i = 0; i < TOTAL_PROCESSES; i++) {
      createNative();
   }
   lossesByMemory = 0;
}

CPU::~CPU() {
   for (list<Process*>::iterator it = processes.begin(); it != processes.end(); ++it) {
      Process* proc = *it;
      delete proc;
   }
}

bool CPU::hasMemory() {
   return (((double)totalMemory - (double)usedMemory) > 0.0);
}

void CPU::addProcess(Process* p) {
   processes.push_back(p);
}

Process* CPU::getProcess(long pid) {
  for (list<Process*>::iterator it = processes.begin(); it != processes.end(); ++it) {
      Process* proc = *it;
      if (proc->getPid() == pid)
         return proc;
  }
  return (NULL);
}

void CPU::showProcesses(bool log2file, bool compact = false) {
  for (list<Process*>::iterator it = processes.begin(); it != processes.end(); ++it) {
      Process* proc = *it;
      if (log2file)
         logger->log(proc->toString(compact));
      else
         cout << proc->toString(compact) << endl;
  }
}

double CPU::getUsedMemory() {
   return usedMemory;
}

void CPU::useMemory(double amount) {
   usedMemory += amount;
}

void CPU::freeMemory(double amount) {
   usedMemory -= amount;
}

double CPU::getTotalMemory() {
   return totalMemory;
}

void CPU::setTotalMemory(double tm) {
   totalMemory = tm;
}

void CPU::setRandomGenerator(RandomGenerator* r) {
   randGen = r;   // saves reference to the random generator to use the same random seed
}

string CPU::memStats() {
   stringstream ss;
   int totExec = 0;
   int totInva = 0;
   int totFini = 0;
   for (list<Process*>::iterator it = processes.begin(); it != processes.end(); ++it) {
      Process* proc = *it;
      if (proc->getStatus() == PSTAT_EXECUTING)
         totExec++;
      else if (proc->getStatus() == PSTAT_FINISHED)
         totFini++;
      else if (proc->getStatus() == PSTAT_INVALID)
         totInva++;
   }
   ss << totExec << "\t" << totFini << "\t" << totInva << "\t" << lossesByMemory << "\n";
   return (ss.str());
}

string CPU::procStats() {
   stringstream ss;
   int totPvm = 0;
   int totVm = 0;
   int totNative = 0;
   for (list<Process*>::iterator it = processes.begin(); it != processes.end(); ++it) {
      Process* proc = *it;
      if (proc->getType() == PTYPE_PVM)
         totPvm++;
      else if (proc->getType() == PTYPE_VM)
         totVm++;
      else if (proc->getType() == PTYPE_NATIVE)
         totNative++;
   }
   ss << totPvm << "\t" << totVm << "\t" << totNative << "\n";
   return (ss.str());
}

uint CPU::getExecProcessesSize() {
   uint count = 0;
   for (list<Process*>::iterator it = processes.begin(); it != processes.end(); ++it) {
      Process* proc = *it;
      if (proc->getStatus() == PSTAT_EXECUTING)
         count++;
   }
   return (count);
}

/**
* Basic creation of any process
*/
Process* CPU::newProcess() {
   Process* process = new Process();
   process->setPid(nextPID++);
   process->setStatus(PSTAT_EXECUTING);
   return process;
}

/**
* Auxiliary method to randomly pick a process in the list of processes
*/
long CPU::randomProcessSelection() {
   long pid = -1;
   list<long> execprocs; // process under execution ONLY
   for (list<Process*>::iterator it = processes.begin(); it != processes.end(); ++it) {
      Process* proc = *it;
      if (proc->getStatus() == PSTAT_EXECUTING)
         execprocs.push_back(proc->getPid());
   }
   if (execprocs.size() > 0) {
      int choice = rand() % execprocs.size();
      list<long>::iterator itera = execprocs.begin();
      std::advance(itera, choice);
      pid = *itera;
   }
   return (pid);
}

/**
* Microcode for the PROCESS VIRTUAL MACHINE (e.g. JVM/CLR)
*/
void CPU::createPVM() {
   if (hasMemory()) {
      Process* process = newProcess();
      process->setBound(PBOUND_CPU);
      process->setType(PTYPE_PVM);
      // set the number of instructions for this process
      process->setTotalInstructions(INITIAL_NUM_INSTR + randGen->nextUnif(TOTAL_NUM_INSTR));
      process->initProgramCounter();
      // set memory for this process and allocate in CPU
      process->setTotalMemory(INITIAL_PVM_MEM + randGen->nextUnif(MEMORY_PVM_PROC - MINIMUM_MEMORY, MEMORY_PVM_PROC));
      // alloc memory
      useMemory(process->getTotalMemory());
      // add process to the list of processes
      addProcess(process);
   } else lossesByMemory++;
}

/**
* Microcode for the creation of a NATIVE process (any process within the OS)
*/
void CPU::createNative() {
   if (hasMemory()) {
      Process* process = newProcess();
      process->setBound(PBOUND_CPU);
      process->setType(PTYPE_NATIVE);
      process->setTotalInstructions(INITIAL_NUM_INSTR + randGen->nextUnif(TOTAL_NUM_INSTR));
      process->initProgramCounter();  // assigns the PC == number of instructions, and then begins to decrement it
      // set memory for this process and allocate in CPU
      process->setTotalMemory(INITIAL_NAT_MEM + randGen->nextUnif(MEMORY_NAT_PROC - MINIMUM_MEMORY, MEMORY_NAT_PROC));
      useMemory(process->getTotalMemory());
      addProcess(process);
   } else lossesByMemory++;
}

/**
* Microcode for the creation of a VIRTUAL MACHINE process (an OS)
*/
void CPU::createVM() {
   if (hasMemory()) {
      Process* process = newProcess();
      process->setBound(PBOUND_CPU);
      process->setType(PTYPE_VM);
      double total = INITIAL_NUM_INSTR + randGen->nextUnif(TOTAL_NUM_INSTR);
      process->setTotalInstructions(total);
      process->initProgramCounter();
      // set memory for this process and allocate in CPU
      process->setTotalMemory(INITIAL_VM_MEM + randGen->nextUnif(MEMORY_VM_PROC - MINIMUM_MEMORY, MEMORY_VM_PROC));
      useMemory(process->getTotalMemory());
      addProcess(process);
   } else lossesByMemory++;
}

/**
* Microcode for the execution of a PROCESS EXECUTION event (a process executing inside the Physical Machine)
*/
void CPU::runProcExec() {
   for (int i = 0; i < TOTAL_CPU_CORES; i++) {
      long pid = randomProcessSelection();
      if (pid != -1) {  // if PID is valid
         Process* proc = getProcess(pid);
         // randomly chooses how many instructions were processed in this event
         double total = randGen->nextUnif(EXEC_NUM_INSTR - MINIMUM_INSTR, EXEC_NUM_INSTR);
         proc->decProgramCounter(total);
         // if the process has reached the pc==0, it has finished execution
         if (proc->isFinished()) {
            stringstream ss;
            ss << "proc " << pid << " has finished!" << endl;
            auxlogger->log(ss.str());
            proc->setStatus(PSTAT_FINISHED);
            // free memory
            freeMemory(proc->getTotalMemory());
            proc->setTotalMemory(0);
         }
      }
   }
}

/**
* Microcode for the execution of a PROCESS DEPARTURE event (a process exiting the Physical Machine)
*/
void CPU::runProcDepart() {
   long pid = randomProcessSelection();
   if (pid != -1) {  // if PID is valid
      Process* proc = getProcess(pid);
      proc->setStatus(PSTAT_FINISHED);
      // free memory
      freeMemory(proc->getTotalMemory());
      proc->setTotalMemory(0);
   }
}

/**
* Microcode for the execution of a PROCESS in INVALID state event (a process that is operating erroneously)
*/
void CPU::runProcInv() {
   long pid = randomProcessSelection();
   if (pid != -1) {  // if PID is valid
      Process* proc = getProcess(pid);
      proc->setStatus(PSTAT_INVALID);
      // free memory
      freeMemory(proc->getTotalMemory());
      proc->setTotalMemory(0);
   }
}


