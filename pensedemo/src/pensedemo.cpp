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


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <pense/environment.h>
#include <pense/algorithms/polynomial.h>
#include <pense/algorithms/fuzzylogic.h>
#include <pense/devices/plants/dc_motor.h>

using namespace std;

int main(int argc, char *argv[])
{
	try
	{
	// Environment with frequency 1000, which is 1000 iterations/second
	PENSE::Environment env(1000);

	// Dummy voltage source.
	PENSE::Device::Device source( "Voltage source", &env );
	source.addAlgorithm( new PENSE::Algorithm::Polynomial( "input", "output" ) );
	source["input"] = 0;
	
	PENSE::Device::Plant::DCMotor motor( "DC motor", &env );
	motor.setLoad( "0.0000503" ); // 100x rotors intertia
	motor["k_e"] = 0.00737;
	motor["k_t"] = 3.96;
	motor["k_d"] = 0.15;
	motor["R"] = 2.16;
// 	motor.process(); 

	PENSE::Device::Device controller( "Fuzzy Logic Controller", &env );

	PENSE::Algorithm::FuzzyLogic f( "output" );
	f.addInputTriangle( 0, 200, "too slow" );
	f.addInputTriangle( 100, 450, "slow" );
	f.addInputTriangle( 400, 500, "a bit slow" );
	f.addInputTriangle( 450, 550, "about right" );
	f.addInputTriangle( 500, 700, "a bit fast" );;
	f.addInputTriangle( 600, 850, "fast" );
	f.addInputTriangle( 800, 1200, "too fast" );

	f.addOutputTriangle( 0.0, 1.0, "slow down quickly", "too fast" );
	f.addOutputTriangle( 0.5, 1.5, "slow down", "fast" );
	f.addOutputTriangle( 1.0, 2.0, "slow down slowly", "a bit fast" );
	f.addOutputTriangle( 1.5, 2.5, "don't change much", "about right" );
	f.addOutputTriangle( 2.0, 3.0, "speed up slowly", "a bit slow" );
	f.addOutputTriangle( 2.5, 3.5, "speed up", "slow" );
	f.addOutputTriangle( 3.0, 4.0, "speed up quickly", "too slow" );

	controller.addAlgorithm( &f, true );

	connect( &source, "output", &motor, "V" );
	connect( &motor, "w", &controller, "input" );
	connect( &controller, "output", &source, "input" );

	while(1)
	{
		env.process();
		source.printInfo();
		motor.printInfo();
		controller.printInfo();
	}

	}
	catch( const std::exception& e )
	{
		cerr << "Exception: " << e.what() << endl;
	}
	catch( ... )
	{
		cerr << "unexpected exception caught" << endl;
	}
	return EXIT_SUCCESS;
}
