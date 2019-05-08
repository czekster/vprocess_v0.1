/**
 * virtual process simulator (vprocess-v0.1)
 * Date: 08/05/2019
 * Author: Ricardo M. Czekster - rczekster@gmail.com
 * Description: class RandomGenerator implementation, to produce pseudorandom numbers
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

#include "RandomGenerator.hpp"
#include "Logger.hpp"

/** \brief RandomGenerator constructor
 *
 */
RandomGenerator::RandomGenerator() {
   srand(time(NULL)); // this should be called just ONCE in the entire project!
}

RandomGenerator::~RandomGenerator() {

}

/**
 * returns a number from the uniform distribution
 */
ulong RandomGenerator::nextUnif(ulong limit) {
   return (rand() % limit);
}

/**
 * returns a number from the uniform distribution between v1 and v2
 */
ulong RandomGenerator::nextUnif(ulong v1, ulong v2) {
   if (v2 - v1 <= 0)
      return (0);
   return (v1 + (rand() % (v2 - v1 + 1)));
}

/**
 * returns a number from the exponential distribution
 */
double RandomGenerator::nextExp(double rate) {
   // draw a number between 0 and 1
   double u = rand()/(double)RAND_MAX;
   // compute the function according to the rate (parameter)
   return (-1*log(1-u)) / (rate); // if u is uniform, so is (1-u)
}


