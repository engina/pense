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

#include "dc_motor.h"
#include "../outputnode.h"
#include "../../algorithms/polynomial.h"

#include <stdexcept>

NAMESPACE_BEGIN( PENSE )
NAMESPACE_BEGIN( Device )
NAMESPACE_BEGIN( Plant )

DCMotor::DCMotor( const std::string& name, Environment* p )
 : Device( name, p )
{
	// stall torque
	addAlgorithm( new Algorithm::Polynomial( "(k_t*V)/R", "T_s" ), false );
	// final angular velocity (maximum)
	addAlgorithm( new Algorithm::Polynomial( "(k_t*V)/(k_e*R)", "w_f" ), false );
	// acceleration
	addAlgorithm( new Algorithm::Polynomial( "((T_s/J)*(1-w/w_f))*(1/f)", "w/dt" ), false );
	// deceleration when V = 0
	addAlgorithm( new Algorithm::Polynomial( "-(w*k_d)", "-w/dt" ), false );
	// angular velocity itself -- primary algo
	addAlgorithm( new Algorithm::Polynomial( "w", "w" ), true );
}

DCMotor::~DCMotor()
{
}

void
DCMotor::setLoad( const std::string& e )
{
	try
	{
	remAlgorithm( "J" );
	}
	catch( ... )
	{
	}
	Algorithm::Polynomial *p = new Algorithm::Polynomial( e, "J" );
	addAlgorithm( p );
	connect( this, "J", this, "J" );
	connect( this, "T_s", this, "T_s" );
	connect( this, "w_f", this, "w_f" );
}

void
DCMotor::process()
{
	outputNode("J")->emit( algorithm( "J" )->evaluate() );
	outputNode("T_s")->emit( algorithm( "T_s" )->evaluate() );
	outputNode("w_f")->emit( algorithm( "w_f" )->evaluate() );
	outputNode("w/dt")->emit( algorithm( "w/dt" )->evaluate() );
	outputNode("-w/dt")->emit( algorithm( "-w/dt" )->evaluate() );
	if( (*this)["V"].value() != 0.0 )
	{
		(*this)["w"] += outputNode( "w/dt" )->value();
	}
	else
	{
		(*this)["w"] += outputNode("-w/dt")->value();
	}
	outputNode("w")->emit( algorithm("w")->evaluate() );
}

NAMESPACE_END
NAMESPACE_END
NAMESPACE_END
