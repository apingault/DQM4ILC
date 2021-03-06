  /// \file DQMLCHelper.h
/*
 *
 * DQMLCHelper.h header template automatically generated by a class generator
 * Creation date : ven. avr. 15 2016
 *
 * This file is part of DQM4ILC libraries.
 * 
 * DQM4ILC is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * based upon these libraries are permitted. Any copy of these libraries
 * must include this copyright notice.
 * 
 * DQM4ILC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with DQM4ILC.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * @author Remi Ete
 * @copyright CNRS , IPNL
 */


#ifndef DQMLCHELPER_H
#define DQMLCHELPER_H

#include "EVENT/LCParameters.h"

namespace dqm4ilc
{

/** DQMLCHelper class
 */ 
class DQMLCHelper 
{
public:
	/** Copy all parameters from input parameters to target parameters
	 *  Existing parameters in target parameters are overridden.
	 */
	static void copyLCParameters( const EVENT::LCParameters &inputParameters , EVENT::LCParameters &targetParameters );
}; 

} 

#endif  //  DQMLCHELPER_H
