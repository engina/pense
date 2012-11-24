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
#include <pense/devices/plants/dc_motor.h>
#include <pense/devices/outputnode.h>

using namespace std;

int main(int argc, char *argv[])
{
	try
	{
	PENSE::Environment env;
	PENSE::Device::Plant::DCMotor motor( "DC motor", &env );
	motor.setLoad( "0.0000000503" );
	motor["k_e"] = 0.00737;
	motor["k_t"] = 3.96;
	motor["k_d"] = 0.15;
	motor["R"] = 2.16;
	int i = 0;
	double v;
	cout << "Input voltage: ";
	cin >> v;
	motor["V"] = v;
	motor.process();
	while( motor != motor.outputNode( "w_f" )->value() )
	{
		cout << "iterating: " << i++ << endl;
		motor.process();
		motor.printInfo();
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
