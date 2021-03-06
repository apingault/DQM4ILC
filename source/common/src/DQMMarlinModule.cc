  /// \file DQMMarlinModule.cc
/*
 *
 * DQMMarlinModule.cc source template automatically generated by a class generator
 * Creation date : lun. mars 7 2016
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

// -- dqm4ilc headers
#include "dqm4ilc/DQMMarlinModule.h"
#include "dqm4ilc/DQMMarlin.h"

// -- dqm4hep headers
#include "dqm4hep/DQMModuleApi.h"
#include "dqm4hep/DQMLogging.h"
#include "dqm4hep/DQMEvent.h"

namespace dqm4ilc
{

DQMMarlinModule::DQMMarlinModule() :
		DQMAnalysisModule()
{
	/* nop */
}

//-------------------------------------------------------------------------------------------------

DQMMarlinModule::~DQMMarlinModule() 
{
	/* nop */
	if(m_pMarlin)
		delete m_pMarlin;
}

//-------------------------------------------------------------------------------------------------

dqm4hep::StatusCode DQMMarlinModule::readSettings(const dqm4hep::TiXmlHandle xmlHandle)
{
	m_pMarlin = new DQMMarlin();

	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, dqm4hep::DQMXmlHelper::readParameterValue(xmlHandle,
			"MarlinSteeringFile", m_marlinSteeringFile));

	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, this->userReadSettings(xmlHandle) );

	return dqm4hep::STATUS_CODE_SUCCESS;
}

//-------------------------------------------------------------------------------------------------

dqm4hep::StatusCode DQMMarlinModule::initModule()
{
    // initialize marlin
    try
    {
    	m_pMarlin->init(m_marlinSteeringFile);

    }
    catch(EVENT::Exception &exception)
    {
    	LOG4CXX_ERROR( dqm4hep::dqmMainLogger, "Couldn't initialize marlin application : " << exception.what());
    	return dqm4hep::STATUS_CODE_FAILURE;
    }
    catch(...)
    {
    	LOG4CXX_ERROR( dqm4hep::dqmMainLogger, "Couldn't initialize marlin application ! Unknown exception !" );
    	return dqm4hep::STATUS_CODE_FAILURE;
    }

    RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, this->userInitModule() );

	return dqm4hep::STATUS_CODE_SUCCESS;
}

//-------------------------------------------------------------------------------------------------

dqm4hep::StatusCode DQMMarlinModule::startOfRun(dqm4hep::DQMRun *pRun)
{
	return this->userStartOfRun( pRun );
}

//-------------------------------------------------------------------------------------------------

dqm4hep::StatusCode DQMMarlinModule::startOfCycle()
{
	return this->userStartOfCycle();
}

//-------------------------------------------------------------------------------------------------

dqm4hep::StatusCode DQMMarlinModule::processEvent(dqm4hep::DQMEvent *pEvent)
{
	EVENT::LCEvent *pLCEvent = pEvent->getEvent<EVENT::LCEvent>();

	if( ! pLCEvent )
	{
		LOG4CXX_ERROR( dqm4hep::dqmMainLogger, "Wrong event type ! Expected EVENT::LCEvent *" );
		return dqm4hep::STATUS_CODE_INVALID_PARAMETER;
	}

	try
	{
		// process event in the marlin framework
		m_pMarlin->processEvent( pLCEvent );

		// process event in the dqm4hep framework
		THROW_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, this->userProcessEvent( pLCEvent ) );
	}
	catch(dqm4hep::StatusCodeException &exception)
	{
		LOG4CXX_ERROR( dqm4hep::dqmMainLogger, "While processing event, StatusCodeException caught : " << exception.toString() );
		return exception.getStatusCode();
	}
	catch(EVENT::Exception &exception)
	{
		LOG4CXX_ERROR( dqm4hep::dqmMainLogger, "While processing event, EVENT::Exception caught : " << exception.what() );
		return dqm4hep::STATUS_CODE_FAILURE;
	}
	catch(...)
	{
		LOG4CXX_ERROR( dqm4hep::dqmMainLogger, "While processing event, unknown exception caught" );
		return dqm4hep::STATUS_CODE_FAILURE;
	}

	return dqm4hep::STATUS_CODE_SUCCESS;
}

//-------------------------------------------------------------------------------------------------

dqm4hep::StatusCode DQMMarlinModule::endOfCycle()
{
	return this->userEndOfCycle();
}

//-------------------------------------------------------------------------------------------------

dqm4hep::StatusCode DQMMarlinModule::endOfRun(dqm4hep::DQMRun *pRun)
{
	return this->userStartOfRun( pRun );
}

//-------------------------------------------------------------------------------------------------

dqm4hep::StatusCode DQMMarlinModule::endModule()
{
	// end module in marlin framework
	m_pMarlin->end();

	// end module in dqm4hep framework
	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, this->userEndModule());

	return dqm4hep::STATUS_CODE_SUCCESS;
}

} 

