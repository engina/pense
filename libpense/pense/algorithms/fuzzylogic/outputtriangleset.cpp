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

#include "object.h"
#include "outputtriangleset.h"
#include "fuzzyvalue.h"
#include "triangle.h"

#include <stdexcept>

NAMESPACE_BEGIN( PENSE )
NAMESPACE_BEGIN( Algorithm )
NAMESPACE_BEGIN( Fuzzy )

OutputTriangleSet::OutputTriangleSet( const std::string& n )
 : TriangleSet( n )
{
}

OutputTriangleSet::~OutputTriangleSet()
{
}

double OutputTriangleSet::defuzify( const FuzzyValueList& degrees )
{
	int i = 0;
	double xx, mx, nm = 0, nx = 0;
	FuzzyValueList::const_iterator d;
	TriangleList::const_iterator it;
	for( d = degrees.begin(); d != degrees.end(); ++d ){
		for( it = triangles.begin(); it != triangles.end(); it++ ){
			if( (*it)->partner() == (*d).name() ){
				i++;
				mx = (*it)->calcArea( (*d).getDegree() );
				xx = (*it)->middle();
				nx = ( ( nx - xx ) * nm / ( mx + nm ) ) + xx;
				nm += mx;
			}
		}
	}
	if( !i )
	{
		throw std::runtime_error( "No matching output triangles for given fuzzy values!" );
	}
	return nx;
}

NAMESPACE_END
NAMESPACE_END
NAMESPACE_END
