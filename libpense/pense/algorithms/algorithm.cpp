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

#include "algorithm.h"

#include <stdexcept>

NAMESPACE_BEGIN( PENSE )
NAMESPACE_BEGIN( Algorithm )

Algorithm::Algorithm( const std::string& n, Object *p )
 : Object( n, p )
{
}

Algorithm::~Algorithm()
{
}

ConstParameterList
Algorithm::parameters() const
{
	return m_map;
}

bool
Algorithm::contains( std::string p )
{
	return m_map.count( p );
}

bool
Algorithm::assign( const std::string& p, double val )
{
	if( !contains( p ) ) return false;
	m_map[ p ] = val;
	return true;
}

double&
Algorithm::operator[]( const std::string& p )
{
	if( !contains( p ) ) throw std::range_error( p + ": no such parameter" );
	return m_map[ p ];
}

double
Algorithm::value( const std::string& p ) const
{
	return m_map.find( p )->second;
}

bool
Algorithm::addParameter( std::string p )
{
	if( contains( p ) ) return false;
	m_map[ p ] = 0;
	return true;
}

bool
Algorithm::remParameter( std::string p )
{
	return m_map.erase( p );
}

int
Algorithm::parameterCount() const
{
	return m_map.size();
}

std::string
Algorithm::toString() const
{
	std::ostringstream stream;
	stream << "[Algorithm][" << name() << "][" << parameterCount() <<
		  " parameters]";
	return stream.str();
}
NAMESPACE_END
NAMESPACE_END
