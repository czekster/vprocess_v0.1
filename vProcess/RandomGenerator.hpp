/**
 * virtual process simulator (vprocess-v0.1)
 * Date: 08/05/2019
 * Author: Ricardo M. Czekster - rczekster@gmail.com
 * Description: class RandomGenerator header
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

#ifndef RANDOMGENERATOR_HPP
#define RANDOMGENERATOR_HPP

#include "Defs.hpp"

class RandomGenerator {
   public:
      RandomGenerator();
      ~RandomGenerator();
      ulong nextUnif(ulong limit);        // draws a number from the UNIFORM distribution between 0 and limit
      ulong nextUnif(ulong v1, ulong v2); // draws a number from the UNIFORM distribution between v1 and v2
      double nextExp(double rate);        // draws a number from the EXPONENTIAL distribution between 0 and 1
   protected:
   private:
};

#endif // RANDOMGENERATOR_HPP
