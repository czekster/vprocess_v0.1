/**
 * virtual process simulator (vprocess-v0.1)
 * Date: 08/05/2019
 * Author: Ricardo M. Czekster - rczekster@gmail.com
 * Description: main file
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

#include "Defs.hpp"
#include "Logger.hpp"
#include "Simulator.hpp"
#include "Utils.hpp"

// *global* logger (all classes should be able to write in the log file)
Logger* logger;

// an auxiliary logger, it will create a log for every execution (see below)
Logger* auxlogger;

// another logger, to save distinct process data
Logger* proclogger;

// another logger, to save memory data
Logger* memlogger;

int main(int argc, char* argv[]) {

   // instantiates the logger (for tracing everything into a file situated in the project folder)
   logger = new Logger();

   // Time = 1/Rate <=> Rate = 1/Time
   double rates[MAX_EVENTS];
   rates[EVT_PA_PVM]    = (double)1/150; //50
   rates[EVT_PA_NATIVE] = (double)1/250; //20
   rates[EVT_PA_VM]     = (double)1/400; //100
   rates[EVT_PE]        = (double)1/5; //5
   rates[EVT_PD]        = (double)1/100; //100
   rates[EVT_PI]        = (double)1/1500; //1500

   double totalEvents = 10000;
   Utils::writeExecDetails(totalEvents, rates);

   cout << "--- vprocess-simulator ---" << endl;   // project header message
   for (uint x = 0; x < TOTAL_SIM_EXECUTIONS; x++) {
      stringstream ss;
      ss << LOG_DIR << "/" << "exec_" << setw(3) << setfill('0') << x << ".txt";
      auxlogger = new Logger(ss.str());
      auxlogger->log("#EXECUTING FINISHED INVALID LOSSES-MEMORY\n", false);
      ss.str(string()); // clears ss

      ss << LOG_DIR << "/" << "mem_" << setw(3) << setfill('0') << x << ".txt";
      memlogger = new Logger(ss.str());
      memlogger->log("#USED-MEMORY\n", false);
      ss.str(string()); // clears ss

      ss << LOG_DIR << "/" << "proc_" << setw(3) << setfill('0') << x << ".txt";
      proclogger = new Logger(ss.str());
      proclogger->log("#PVM\tVM\tNAT\n", false);

      // simulator instance - it will run for X events in the system
      Simulator* simulator = new Simulator();
      simulator->run(totalEvents, rates, x);

      delete simulator;
      delete auxlogger;
      delete memlogger;
   }

   delete logger;

   return 0;
}
