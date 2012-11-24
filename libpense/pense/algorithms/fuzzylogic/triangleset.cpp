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
#include "triangleset.h"

NAMESPACE_BEGIN( PENSE )
NAMESPACE_BEGIN( Algorithm )
NAMESPACE_BEGIN( Fuzzy )

TriangleSet::TriangleSet( const std::string& n )
 : Object( n )
{
}

TriangleSet::~TriangleSet()
{
	TriangleList::iterator it;
	for( it = triangles.begin(); it != triangles.end(); ++it )
	{
		delete *it;
	}
}

bool
TriangleSet::contains( const std::string& n ) const
{
	TriangleList::const_iterator it;
	for( it = triangles.begin(); it != triangles.end(); ++it )
	{
		if( (*it)->name() == n )
			return true;
	}
	return false;
}

bool TriangleSet::add( Triangle* t )
{
	// Triangle names have to be unique
	if( contains( t->name() ) )
		return false;
	triangles.push_back( t );
	return true;
}

bool TriangleSet::remove( const std::string& name )
{
	TriangleList::iterator it;
	for( it = triangles.begin(); it != triangles.end(); ++it )
	{
		if( (*it)->name() == name )
			delete *it;
	}
	return false;
}

Triangle* TriangleSet::get( const std::string& name )
{
	TriangleList::iterator it;
	for( it = triangles.begin(); it != triangles.end(); ++it )
	{
		if( (*it)->name() == name )
			return *it;
	}
	return NULL;
}

NAMESPACE_END
NAMESPACE_END
NAMESPACE_END
