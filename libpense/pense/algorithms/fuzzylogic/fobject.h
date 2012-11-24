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

#ifndef FOBJECT_H_
#define FOBJECT_H_

#include "../../global.h"
#include <string>

NAMESPACE_BEGIN( PENSE )
NAMESPACE_BEGIN( Algorithm )
NAMESPACE_BEGIN( Fuzzy )


/**
 *  Base class for all Fuzzy objects.<br>
 *  This is not PENSE::Object on purpose, this is the Fuzzy Logic framework
 *  itself, hence it is a seperate concept. It'll be used in an
 *  PENSE::Algorithm as a utulity.
 */

class Object {
private:
	std::string		m_name;
public:
	/**
	 * Constructs an object with name n
	 * @param name object name
	 */
	Object( const char* name );

	/**
	 * Constructs an object with name n
	 * @param name object name
	 */
	Object( const std::string& name );

	/**
	 * Destructs the object
	 */
	virtual			~Object();

	/**
	 * Sets the object's name
	 * @param name new name
	 */
	void
	setName( const std::string& name );
		
	/**
 	 * Gets the object's name
 	 * @returns name of the object
	 */
	const std::string&
	name( void ) const;
};

NAMESPACE_END
NAMESPACE_END
NAMESPACE_END

#endif
