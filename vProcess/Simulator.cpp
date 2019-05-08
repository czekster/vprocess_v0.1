/**
 * virtual process simulator (vprocess-v0.1)
 * Date: 08/05/2019
 * Author: Ricardo M. Czekster - rczekster@gmail.com
 * Description: class Simulator implementation, where the simulation is run
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

#include "Simulator.hpp"
#include "RandomGenerator.hpp"
#include "Logger.hpp"
#include "Utils.hpp"
#include "CPU.hpp"
#include "Event.hpp"
#include "Statistics.hpp"

Simulator::Simulator() {
   globalClock = 0.0;
   randGen = new RandomGenerator();
   cpu = new CPU();
   cpu->setTotalMemory(TOTAL_MEMORY); // set main memory for CPU
   cpu->setRandomGenerator(randGen);  // passes the same seed across all simulation!
   statistics = new Statistics();
}

Simulator::~Simulator() {
   delete randGen;
   delete cpu;
   for (list<Event*>::iterator it = events.begin(); it != events.end(); ++it) {
      Event* evt = *it;
      delete evt;
   }
   delete statistics;
}

/** \brief This is the main method for the simulator.
 *
 * \param ulong totalEvts total number of events that the simulation must run
 * \param double* rates an array of rates, of size MAX_EVENTS
 * \return void
 *
 */
void Simulator::run(ulong totalEvts, double* rates, int iter) {
   ulong evt = 0;
   discreteevent nextEvent;
   double when;
   double avgmem = 0;   // average amount of memory
   double avgprocs = 0; // average number of processes
   ulong logmemorycounter = 0;
   time_t now = time(NULL);

   // I will count every event to save to the statistics later
   int events_count[MAX_EVENTS];
   for (int i = 0; i < MAX_EVENTS; i++)
      events_count[i] = 0;

   //memlogger->log(cpu->getTotalMemory());
   //cout << "total=" << cpu->getExecProcessesSize() << endl << endl;

   do {
      auxlogger->log(cpu->memStats(), false);
      proclogger->log(cpu->procStats(), false);

      stringstream ssl;
      ssl << cpu->getUsedMemory() << "\n";
      memlogger->log(ssl.str(), false);

      nextEvent = draw(rates, &when);
      Event* event; // saves the event and puts in the list of events
      // process the next EVENT, reflecting on the other objects
      //      ---  execute EVENT MICROCODE  ---      //
      switch (nextEvent) {
         case EVT_PA_PVM:      // process virtual machine
            cpu->createPVM();
            event = new Event(EVT_PA_PVM, when);
            events_count[EVT_PA_PVM]++;
            break;
         case EVT_PA_NATIVE:   // native process
            cpu->createNative();
            event = new Event(EVT_PA_NATIVE, when);
            events_count[EVT_PA_NATIVE]++;
            break;
         case EVT_PA_VM:       // virtual machine (another OS)
            cpu->createVM();
            event = new Event(EVT_PA_VM, when);
            events_count[EVT_PA_VM]++;
            break;
         case EVT_PE:          // process execution
            cpu->runProcExec();
            event = new Event(EVT_PE, when);
            events_count[EVT_PE]++;
            break;
         case EVT_PD:          // process departure
            cpu->runProcDepart();
            event = new Event(EVT_PD, when);
            events_count[EVT_PD]++;
            break;
         case EVT_PI:          // process is in invalid state
            cpu->runProcInv();
            event = new Event(EVT_PI, when);
            events_count[EVT_PI]++;
            break;
         default:              // error because next event does not exist (it should not enter here)
            logger->log("[ERROR]: nextEvent is nonexistent");
      }
      avgmem += cpu->getUsedMemory();
      avgprocs += cpu->getExecProcessesSize();

      if (logmemorycounter++ % LOG_MEMORY_COUNTER == 0) {
         //auxlogger->log(Utils::formatDouble((double)cpu->getUsedMemory()/cpu->getTotalMemory()));
         stringstream ss;
         //ss << Utils::formatDouble((double)cpu->getUsedMemory());// << ";"
         ss << Utils::formatDouble((double)cpu->getExecProcessesSize());
         //auxlogger->log(ss.str());
      }

      //
      addEvent(event);
      // updates simulator global clock
      globalClock += when;
      //logger->log(Utils::formatDouble(globalClock), eventStr(nextEvent));
      evt++;
      if (evt % 100 == 0) {
         cout << "\rRunning " << (iter+1) << " iteration of " << TOTAL_SIM_EXECUTIONS << "... "
              << "Event=" << setw(10) << setfill(' ') << left << evt << flush;
      }
   } while (evt < totalEvts);
   statistics->setStat(STAT_TOTAL_TIME, globalClock);
   statistics->setStat(STAT_TOTAL_EVENTS, totalEvts);
   for (int i = 0; i < MAX_EVENTS; i++) {
      switch(i) {
         case EVT_PA_PVM:    statistics->setStat(STAT_EVT_PA_PVM, events_count[EVT_PA_PVM]); break;
         case EVT_PA_NATIVE: statistics->setStat(STAT_EVT_PA_NATIVE, events_count[EVT_PA_NATIVE]); break;
         case EVT_PA_VM:     statistics->setStat(STAT_EVT_PA_VM, events_count[EVT_PA_VM]); break;
         case EVT_PE:        statistics->setStat(STAT_EVT_PE, events_count[EVT_PE]); break;
         case EVT_PD:        statistics->setStat(STAT_EVT_PD, events_count[EVT_PD]); break;
         case EVT_PI:        statistics->setStat(STAT_EVT_PI, events_count[EVT_PI]); break;
      }
   }
   statistics->setStat(STAT_EXECUTION_TIME, time(NULL) - now);
   statistics->setStat(STAT_AVERAGE_MEM, avgmem/totalEvts);
   statistics->setStat(STAT_AVERAGE_PROCS, avgprocs/totalEvts);
   statistics->print(iter);
   //cpu->showProcesses(true, true); // parameters: a) log2file b) compact mode on
}

string Simulator::eventStr(discreteevent e) {
   switch(e) {
      case EVT_PA_PVM:    return "PVM";
      case EVT_PA_NATIVE: return "NAT";
      case EVT_PA_VM:     return "VM";
      case EVT_PE:        return "PE";
      case EVT_PD:        return "PD";
      case EVT_PI:        return "PI";
   }
   return ("INV");  // if it reached here, an error has occurred...
}

/** \brief Selects the event from all possible discrete events to be drawn
 *
 * \param rates The array of rates - one rate for each event
 * \param when The time which the event happens - it will be accumulated in the global clock
 * \return discreteevent that occurred
 *
 */
discreteevent Simulator::draw(double* rates, double* when) {
   // I must discover *which* event happens: so I will draw all and see the random time
   //     the time with the least value will be chosen
   double values[MAX_EVENTS];
   values[0] = randGen->nextExp(rates[0]);
   double first = values[0];
   int firstAt = 0;
   for (int i = 1; i < MAX_EVENTS; i++) {
      values[i] = randGen->nextExp(rates[i]);
      if (values[i] < first) {
         first = values[i];
         firstAt = i;
      }
   }
   // saves the time for the event (when it happens)
   *when = first;
   return (discreteevent)firstAt;
}

void Simulator::addEvent(Event* e) {
   events.push_back(e);
}

void Simulator::showEvents() {
  for (list<Event*>::iterator it = events.begin(); it != events.end(); ++it) {
      Event* event = *it;
      cout << event->toString() << endl;
  }
}



