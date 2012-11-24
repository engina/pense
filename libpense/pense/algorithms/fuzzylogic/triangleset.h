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

#ifndef FTRIANGLESET_H_
#define FTRIANGLESET_H_

#include <string>

#include "../../global.h"
#include "fobject.h"

#include <vector>

NAMESPACE_BEGIN( PENSE )
NAMESPACE_BEGIN( Algorithm )
NAMESPACE_BEGIN( Fuzzy )

class Triangle;
typedef std::vector< Triangle* > TriangleList;

/**
 *  Fuzzy set, contains fuzzy triangles.
 */
 
class TriangleSet : public Object {
public:
	/**
	 * This is the base class that will be used for object
	 * which will contain triangles.
	 */
	TriangleSet( const std::string& name );
	
	/**
	 * Destructor, deletes the list.
	 */
	virtual
	~TriangleSet();
	
	/**
	 * Adds a triangle to the set.
	 * @param triangle triangle to be added.
	 */
	virtual bool
	add( Triangle *triangle );
	
	/**
	 * Removes a triangle from the set.<br>
	 * Note: This method should tell if it was successful.
	 * @param name of triangle to be removed.
	 * @return true on success
	 */
	virtual bool
	remove( const std::string& name );

	/**
	 * Returns the triangle named name
	 */
	virtual Triangle*
	get( const std::string& name );

	/**
	 * @param name of the triangle to be searched
	 * @return true if triangle exists
	 */
	bool
	contains( const std::string& name ) const;

protected:
	/** triangle object container */
	TriangleList	triangles;
};

NAMESPACE_END
NAMESPACE_END
NAMESPACE_END

#endif
