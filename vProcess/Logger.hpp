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

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "Defs.hpp"

class Logger {
   public:
      Logger();
      Logger(string filename);
      ~Logger();
      template<typename T> void appendlog(string filename, uint instr, T msg);
      template<typename T> void log(T msg, bool line);
      template<typename T, typename U> void log(T msg1, U msg2);
   protected:
   private:
      string filename;
      uint counter;
      ofstream ofs;
      string currentDateTime();
};

// This is needed to be kept *HERE* due to template function use
// More information here: http://www.parashift.com/c++-faq-lite/separate-template-class-defn-from-decl.html
template<typename T>
void Logger::log(T msg, bool line = true) {
   if (line)
      ofs << "[" << setw(COLUMN_WIDTH) << fixed << setprecision(PRECISION) << (counter++) << "];" << msg << endl;
   else
      ofs << msg;// << " ";
}

/** \brief Prints two msgs in the same method
 *
 * \param T First message
 * \param U Second message
 * \return void
 *
 */
template<typename T, typename U>
void Logger::log(T msg1, U msg2) {
   ofs << "[" << setw(COLUMN_WIDTH) << fixed << setprecision(PRECISION) << (counter++) << "];" << msg1 << ";" << msg2 << endl;

}

/**
 * Opens a file to append message to a filename (parameters)
 */
template<typename T>
void Logger::appendlog(string filename, uint instr, T msg) {
   //cout << "chegou!" << filename << endl;
   ofstream output;
   stringstream ss;
   ss << LOG_DIR << "/" << filename << ".txt";
   output.open(ss.str().c_str(), ios::out | ios::app );
   //output.open("nome.txt", ios::app );
   output << instr << ";" << msg << endl;
   output.close();
}

#endif // LOGGER_HPP
