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

#ifndef OBJECT_H_
#define OBJECT_H_

#include "global.h"

#include <string>
#include <iostream>
#include <sstream>

NAMESPACE_BEGIN( PENSE )

/**
 *  Base class for all objects.<br>
 * This class gives an identity to any classes dervice from it; a name and a
 * parent. Devices can be compared with virtual operator==, which can be 
 * reimplemented and used polymorphically.
 */
class Object {
public:
	/**
 	 * Constructs an object with name n
 	 * @param name object name
	 * @param p parent of this object
 	 */
	Object( const std::string& name = "Default Object", Object *p = NULL );

	/**
 	 * Destructs the object
 	 */
	virtual
	~Object();

	/**
 	 * Sets the object's name
 	 * @param name new name
 	 */
	void
	setName( std::string name );
		
	/**
 	 * Gets the object's name
 	 * @returns name of the object
	 */
	std::string
	name( void ) const;

	/**
	 * Sets the parent of tihs object
	 * @param p new parent object
	 */
	void
	setParent( Object* p );

	/**
	 * @return parent of this object
	 */
	Object*
	parent() const;


	/**
	 * Convenience method to avoid `obj.name() == std::string()'.
	 * Instead just `obj == std::string'
	 * @param n name to compare
	 * @return true if name n matches the name of this object
	 */
	virtual bool
	operator==( const std::string& n ) const;
	
	/**
	 * Convenience method to avoid `obj1.name() == obj2.name()'.
	 * Instead just `obj1 == obj2' is fine.
	 * @param o object to be compared too
	 * @return true if Object o has the same name with this object
	 */
	virtual bool
	operator==( const Object& o ) const;

	/**
	 * When any class exposed to a `std::cout<<' this method will be called
	 * and the std::string returned by this method will be printed to
	 * stdout.
	 * @return debug information
	 */
	virtual std::string
	toString() const;
private:
	//! Name of the object
	std::string	m_name;
	//! Parent of the object
	Object*		m_parent;
};

NAMESPACE_END

/**
 * `std::cout <<' overloading. When a Object is exposed to std::cout, it's
 * toString() method is called. For instance;
 * @code
 * Object foo( "obj name", 0L );
 * std::cout << foo << std::endl;
 * // will print "[Object][obj name]" to the stdout
 * @endcode
 */
std::ostream&
operator << ( std::ostream& ostr, const PENSE::Object& obj );

#endif
