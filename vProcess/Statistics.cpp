/**
 * virtual process simulator (vprocess-v0.1)
 * Date: 08/05/2019
 * Author: Ricardo M. Czekster - rczekster@gmail.com
 * Description: class Statistics implementation - saves interesting simulation statistics
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

#include "Statistics.hpp"
#include "Logger.hpp"
#include "Utils.hpp"

/** \brief Statistics constructor
 *
 */
Statistics::Statistics() {
   stats = new double[TOTAL_STATISTICS];
   for (int i = 0; i < TOTAL_STATISTICS; i++)
      stats[i] = 0.0;
}

Statistics::~Statistics() {
   delete stats;
}

void Statistics::setStat(int idx, double value) {
   stats[idx] = value;
}

void Statistics::print(int iter) {
   stringstream ss;
   ss << "#Statistics;" << iter;
   logger->log(ss.str());
   for (int i = 0; i < TOTAL_STATISTICS; i++) {
      switch(i) {
         case STAT_TOTAL_TIME:
            logger->log("STAT_TOTAL_TIME", Utils::formatDouble(stats[i]));
            break;
         case STAT_TOTAL_EVENTS:
            logger->log("STAT_TOTAL_EVENTS", stats[i]);
            break;
         case STAT_EVT_PA_PVM:
            logger->log("STAT_EVT_PA_PVM", stats[i]);
            break;
         case STAT_EVT_PA_NATIVE:
            logger->log("STAT_EVT_PA_NATIVE", stats[i]);
            break;
         case STAT_EVT_PA_VM:
            logger->log("STAT_EVT_PA_VM", stats[i]);
            break;
         case STAT_EVT_PE:
            logger->log("STAT_EVT_PE", stats[i]);
            break;
         case STAT_EVT_PD:
            logger->log("STAT_EVT_PD", stats[i]);
            break;
         case STAT_EVT_PI:
            logger->log("STAT_EVT_PI", stats[i]);
            break;
         case STAT_AVERAGE_MEM:
            logger->log("STAT_AVERAGE_MEM", Utils::formatDouble(stats[i]));
            break;
         case STAT_AVERAGE_PROCS:
            logger->log("STAT_AVERAGE_PROCS", stats[i]);
            break;
         case STAT_EXECUTION_TIME:
            logger->log("STAT_EXECUTION_TIME", stats[i]);
            break;
      }
   }
}




