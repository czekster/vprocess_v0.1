/**
 * virtual process simulator (vprocess-v0.1)
 * Date: 08/05/2019
 * Author: Ricardo M. Czekster - rczekster@gmail.com
 * Description: header of class Process
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

#ifndef PROCESS_HPP
#define PROCESS_HPP

#include "Defs.hpp"

class Process {
   public:
      Process();
      ~Process();
      ulong getTotalInstructions();
      void setTotalInstructions(ulong ti);
      ulong getTotalMemory();
      void setTotalMemory(ulong tm);
      void initProgramCounter();
      long getPid();
      void setPid(long p);
      long getProgramCounter();
      void setProgramCounter(long pc);
      void decProgramCounter(long pc);   // decrements the PC register by pc units
      bool isFinished();                 // returns true if the Program Counter is greater or equal to zero, i.e.,
                                         //         the program is finished
      void setBound(procbound b);
      proctype getType();
      void setType(proctype t);
      procstatus getStatus();
      void setStatus(procstatus s);
      string toString(bool compact = false);
      string getLoggerName();            // returns the filename of this process (to log)
   protected:
   private:
      long pid;                          // process unique identifier
      long programCounter;               // represents the register program counter - to know which instruction is the next
      ulong totalInstructions;           // total number of instructions
      ulong totalMemory;                 // total allocated memory
      procbound bound;                   // CPU-bound or IO-bound process
      proctype type;                     // process type
      procstatus status;                 // process status: executing, finished, invalid
      string typeStr(proctype t);        // return process type as a string
      string statusStr(procstatus s);    // return process status as a string
      string boundStr(procbound b);      // return process bound as a string
};

#endif // PROCESS_HPP
