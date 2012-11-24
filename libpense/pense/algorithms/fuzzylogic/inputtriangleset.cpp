/***************************************************************************
 *   Copyright (C) 2004 by Engin AYDOGAN                                   *
 *   engin@bzzzt.biz                                                       *
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

#include "inputtriangleset.h"
#include "triangle.h"
#include "fuzzyvalue.h"

NAMESPACE_BEGIN( PENSE )
NAMESPACE_BEGIN( Algorithm )
NAMESPACE_BEGIN( Fuzzy )

InputTriangleSet::InputTriangleSet ( const std::string &n )
 : TriangleSet( n )
{
}

InputTriangleSet::~InputTriangleSet()
{
}

FuzzyValueList
InputTriangleSet::fuzify( double input )
{
	FuzzyValueList fl;
	TriangleList::const_iterator it;

	for( it = triangles.begin(); it != triangles.end(); ++it ){
		if( (*it)->contains( input ) ){
			fl.push_back( FuzzyValue( (*it)->degree(  input ), (*it), (*it)->name() ) );
		}
	}

	it = triangles.begin();
	if( input <= (*it)->start() ){
		fl.push_back( FuzzyValue( 1, (*it), (*it)->name() ) );
	}

	TriangleList::const_reverse_iterator rit = triangles.rbegin();
	if( input >= (*rit)->end() ){
		fl.push_back( FuzzyValue( 1, (*rit), (*rit)->name() ) );
	}

	return fl;
}

NAMESPACE_END
NAMESPACE_END
NAMESPACE_END
