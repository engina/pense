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
#include <pense/devices/controllers/pwm.h>
#include <pense/devices/outputnode.h>

using namespace std;

int main(int argc, char *argv[])
{
	try
	{
	PENSE::Environment env;
	PENSE::Device::Controller::PWM pwmController( "PWM Controller", &env );

	// No increase/decrease in output signal's frequency
	pwmController.setAlgorithm( new PENSE::Algorithm::Polynomial( "0" ) );

	int frequency, cycles;
	
	cout << "System frequency: ";
	cin >> frequency;
	env.setFrequency( frequency );

	cout << "PWM output percentage: ";
	cin >> cycles;
	pwmController.setCycles( cycles );

	cout << env << endl;

	int i = 0;
	double result = 0;
	while( i++ < env.frequency() )
	{
		pwmController.process();
		result += pwmController.value();
	}

	cout << result << " ON output pulse" << endl;
	cout << "If the result is the frequency*(cycles/100), then it sounds correct." << endl;

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
