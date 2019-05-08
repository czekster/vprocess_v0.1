/**
 * virtual process simulator (vprocess-v0.1)
 * Date: 08/05/2019
 * Author: Ricardo M. Czekster - rczekster@gmail.com
 * Description: class Logger header
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

#ifndef UTILS_HPP
#define UTILS_HPP

#include "Defs.hpp"

class Utils {
   public:
      Utils();
      ~Utils();
      static string formatDouble(double value);
      static string currentDateTime();             // returns the current date and time - used in Logger to create the file
      static string currentDateTimeHuman();        // returns the current date and time - in a human readable format
      static double now();                         // returns the current time, as an unformatted number
      static void writeExecDetails(ulong totalEvts, double* rates);    // save a file with simulation parameters
   protected:
   private:
};

#endif // UTILS_HPP
