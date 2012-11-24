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
#include "triangle.h"

#include <cmath>

NAMESPACE_BEGIN( PENSE )
NAMESPACE_BEGIN( Algorithm )
NAMESPACE_BEGIN( Fuzzy )

Triangle::Triangle( double s,
		    double e,
		    const std::string& n,
		    const std::string& p )
 : Object( n ),
   m_start( s ),
   m_end( e )
{
	update();
	m_height = 0;
	m_set = NULL;
	setPartner( p );
}

Triangle::~Triangle()
{
}

void
Triangle::update()
{
	m_width = m_end - m_start;
	m_middle = ( m_end + m_start ) / 2.0;
}

bool
Triangle::contains( double i ) const
{
	return ( i > start() && i < end() );
}

double
Triangle::degree( double i ) const
{
	if( i < start() || i > end() )
	{
		return 0;
	}
	else
	{
		return ( 1 - ( std::abs( i - m_middle ) / ( m_width / 2.0 ) ) );
	}
}

void
Triangle::setStart( double s )
{
	m_start = s;
	update();
}

void
Triangle::setEnd( double e )
{
	m_end = e;
	update();
}

void Triangle::setMiddle( double m )
{
	double diff;
	diff = m - m_middle;
	m_start += diff;
	m_end += diff;
	m_middle = m;
}

void Triangle::incMiddle( double x )
{
	m_start += x;
	m_end += x;
	m_middle += x;
}

void Triangle::decMiddle( double x )
{
	incMiddle( -x );
}

void Triangle::setWidth( double w )
{
	double half;
	half = w / 2.0;
	m_start = m_middle - half;
	m_end = m_middle + half;
}

void Triangle::expand( double e )
{
	double half;
	half = e / 2.0;
	m_start -= half;
	m_end += half;
	m_width = m_end - m_start;
}

void Triangle::shrink( double s )
{
	expand( -s );
}

double Triangle::calcArea( double h )
{
	return ( m_area = h * m_width / 2.0 );
}

void Triangle::setPartner( const std::string& n )
{
	m_partnerName = n;
}

const TriangleSet* Triangle::of()
{
	return m_set;
}

const std::string&
Triangle::partner() const
{
	return m_partnerName;
}

void
Triangle::printInfo() const
{
	std::cout << "Triangle[" << name() << "][ start: " << start()
		  << ", end: " << end() << ", middle: " << middle()
		  << ", width: " << width() << "]" << std::endl;
}
NAMESPACE_END
NAMESPACE_END
NAMESPACE_END
