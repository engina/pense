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

#include "object.h"

NAMESPACE_BEGIN( PENSE )

Object::Object( const std::string& n, Object *p )
{
	m_name = n;
	m_parent = p;
}

Object::~Object()
{
}

void
Object::setName( std::string n )
{
	m_name = n;
}

std::string
Object::name( void ) const
{
	return m_name;
}

void
Object::setParent( Object* p )
{
	m_parent = p;
}

Object*
Object::parent() const
{
	return m_parent;
}

bool
Object::operator==( const std::string& n ) const
{
	return ( name() == n );
}

bool
Object::operator==( const Object& o ) const
{
	return (name() == o.name() );
}

std::string
Object::toString() const
{
	std::ostringstream stream;
	stream << "[Object][" << name() << "]";
	return stream.str();
}

NAMESPACE_END

std::ostream&
operator << ( std::ostream& ostr, const PENSE::Object& obj )
{
	ostr << obj.toString();
	return ostr;
}
