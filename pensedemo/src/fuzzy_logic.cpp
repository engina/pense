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

#include <pense/algorithms/fuzzylogic.h>


using namespace std;

int main(int argc, char *argv[])
{
	try
	{

	PENSE::Algorithm::FuzzyLogic f( "fuzzy logic" );

	while(1)
	{
		int start, end;
		std::string name;
		cout << "Input triangle [start end name] (-1 to next step): ";
		cin >> start;
		if( start == -1 ) break;
		cin >> end;
		cin >> name;
		cout << "$ Adding input triangle[" << start << "," << end << "," << name << "]" << endl;
		f.addInputTriangle( start, end, name );
	}

	while(1)
	{
		int start, end;
		std::string name, partner;
		cout << "Output triangle [start end name partner] (-1 to next step): ";
		cin >> start;
		if( start == -1 ) break;
		cin >> end;
		cin >> name;
		cin >> partner;
		cout << "$ Adding output triangle[" << start << "," << end << "," << name << "," << partner << "]" << endl;
		f.addOutputTriangle( start, end, name, partner );
	}
	cout << "Now, the fun part. Enter input values to evaluate." << endl;
	while(1)
	{
		double input;
		cout << "Input: ";
		cin >> input;
		cout << "Result: " << f.evaluate( input ) << endl;
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
