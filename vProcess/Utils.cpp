/**
 * virtual process simulator (vprocess-v0.1)
 * Date: 08/05/2019
 * Author: Ricardo M. Czekster - rczekster@gmail.com
 * Description: class Utils implementation of standalone methods
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

#include "Utils.hpp"
#include "Logger.hpp"

/** \brief Utils constructor
 *
 */
Utils::Utils() {

}

Utils::~Utils() {

}

/** \brief Converts a double to a string with ',' instead of '.' (used in Brazil)
 *
 * \param value Double value
 * \return string with formatted double
 *
 * (this is a *static* method - see Utils.hpp for more information)
 */
string Utils::formatDouble(double value) {
   ostringstream strs;
   strs << value;
   string str = strs.str();
   replace(str.begin(), str.end(), '.', ',');
   return str;
}

/**
 * Build a string with the current date, formatted YYYYMMDDHMS - year(Y) month(M) day (D) hour (H) minute (M) seconds (S)
 */
string Utils::currentDateTime() {
   time_t     now = time(0);
   struct tm  tstruct;
   char       buf[80];
   tstruct = *localtime(&now);
   // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
   //       for more information about date/time format
   strftime(buf, sizeof(buf), "%Y%m%d%H%M%S", &tstruct);
   strcat(buf,".txt");
   return buf;
}

/**
 * Build a string with the current date, formatted DD-MM-YYYY H_M_S - year(Y) month(M) day (D) hour (H) minute (M) seconds (S)
 */
string Utils::currentDateTimeHuman() {
   time_t     now = time(0);
   struct tm  tstruct;
   char       buf[80];
   tstruct = *localtime(&now);
   // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
   //       for more information about date/time format
   strftime(buf, sizeof(buf), "%d-%m-%Y %H_%M_%S", &tstruct);
   strcat(buf,".txt");
   return buf;
}

/**
 * Return the current time
 */
double Utils::now() {
   time_t timer;
   time(&timer);
   return (timer);
}

/**
 * Write the simulation details
 */
void Utils::writeExecDetails(ulong totalEvts, double* rates) {
   string date = Utils::currentDateTimeHuman();
   stringstream ss;
   ss << LOG_DIR << "/" << "_exec_details_" << date;
   cout << "will write=" << ss.str() << endl;
   ofstream ofs;
   ofs.open(ss.str().c_str());
   ofs << "total_events=" << totalEvts << endl;
   ofs << "EVT_PA_PVM=" << rates[EVT_PA_PVM] << endl;
   ofs << "EVT_PA_NATIVE=" << rates[EVT_PA_NATIVE] << endl;
   ofs << "EVT_PA_VM=" << rates[EVT_PA_VM] << endl;
   ofs << "EVT_PE=" << rates[EVT_PE] << endl;
   ofs << "EVT_PD=" << rates[EVT_PD] << endl;
   ofs << "EVT_PI=" << rates[EVT_PI] << endl;
   ofs << "TOTAL_SIM_EXECUTIONS=" << TOTAL_SIM_EXECUTIONS << endl;
   ofs << "TOTAL_NUM_INSTR=" << TOTAL_NUM_INSTR << endl;
   ofs << "INITIAL_NUM_INSTR=" << INITIAL_NUM_INSTR << endl;
   ofs << "EXEC_NUM_INSTR=" << EXEC_NUM_INSTR << endl;
   ofs << "MINIMUM_INSTR=" << MINIMUM_INSTR << endl;
   ofs << "TOTAL_MEMORY (GB)=" << TOTAL_MEMORY/1024/1024/1024 << endl;
   ofs << "MINIMUM_MEMORY (KB)=" << MINIMUM_MEMORY/1024 << endl;
   ofs << "MEMORY_PVM_PROC (MB)=" << MEMORY_PVM_PROC/1024/1024 << endl;
   ofs << "INITIAL_PVM_MEM (KB)=" << INITIAL_PVM_MEM/1024 << endl;
   ofs << "MEMORY_VM_PROC (MB)=" << MEMORY_VM_PROC/1024/1024 << endl;
   ofs << "INITIAL_VM_MEM (KB)=" << INITIAL_VM_MEM/1024 << endl;
   ofs << "MEMORY_NAT_PROC (KB)=" << MEMORY_NAT_PROC/1024 << endl;
   ofs << "INITIAL_NAT_MEM (KB)=" << INITIAL_NAT_MEM/1024 << endl;
   ofs << "TOTAL_CPU_CORES=" << (int)TOTAL_CPU_CORES << endl;
   ofs << "TOTAL_PROCESSES=" << TOTAL_PROCESSES << endl;
   ofs.close();
}



