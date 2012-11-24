/***************************************************************************
 *   Copyright (C) 2005 by Engin AYDOGAN   *
 *   engin@bzzzt.biz   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "pwm.h"

#include "../../algorithms/polynomial.h"
#include "../outputnode.h"

#include <math.h>

#include <stdexcept>

NAMESPACE_BEGIN( PENSE )
NAMESPACE_BEGIN( Device )
NAMESPACE_BEGIN( Controller )

PWM::PWM( const std::string& n, Environment* e )
 : Device( n, e ), m_process( 0 )
{
	// dummy
// 	addAlgorithm( new Algorithm::Polynomial( "input", "output" ), true );
	addOutputNode( new OutputNode( "output" ), true );
	addOutputNode( new OutputNode( "cycles" ) );
	addOutputNode( new OutputNode( "process" ) );
}

PWM::~PWM()
{
}

void
PWM::setCycles( uint c )
{
	m_cycles = c;
}

uint
PWM::cycles() const
{
	return m_cycles;
}

void
PWM::setAlgorithm( Algorithm::Algorithm* a )
{
	try
	{
	remAlgorithm( "a" );
	}
	catch( ... )
	{
	}
	a->setName( "a" );
	addAlgorithm( a, false );
}

Algorithm::Algorithm*
PWM::algorithm()
{
	return Device::algorithm( "a" );
}

void
PWM::process()
{
	// calculate new increase in PWM signal cycles
	outputNode( "a" )->emit( Device::algorithm( "a" )->evaluate() );
	// add it to the current cycles value, note that this can be a negative value
	m_cycles += static_cast<int>( outputNode( "a" )->value() );
	// make sure the cycles are in the range; 0 < cycles < 100
	m_cycles = std::max<int>( m_cycles, 0 );
	m_cycles = std::min<int>( m_cycles, 100 );
	outputNode( "cycles" )->emit( m_cycles );
	outputNode( "process" )->emit( m_process );
	// get frequency of the environment
	double frequency = (*this)["f"].value();
	if( frequency < 100 )
	{
		throw std::logic_error( "PWM Controller can't work with a "
					"frequency less than 100" );
	}
	// make sure iteration counting doesn't exceed frequency, reset
	m_process %= static_cast<int>(frequency);
	// see if we should give on or off signal
	double cycle_freq = 100.0 / static_cast<double>(m_cycles);
	double tolerence = fmod( cycle_freq, 1.0 );
		fprintf( stderr, "Process: %d ON Freq: %f Tolerence: %f ", m_process, 100.0/(double)m_cycles, tolerence );
	if( fmod( (double)(m_process++), cycle_freq ) <= tolerence )
	{
		fprintf( stderr, "ON\n" );
		outputNode( "output" )->emit( 1 );
	}
	else
	{
		fprintf( stderr, "OFF\n" );
		outputNode( "output" )->emit( 0 );
	}
}

NAMESPACE_END
NAMESPACE_END
NAMESPACE_END
