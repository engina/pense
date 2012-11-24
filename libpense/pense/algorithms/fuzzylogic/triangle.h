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

#ifndef FTRIANGLE_H_
#define FTRIANGLE_H_

#include <string>

#include "../../global.h"
#include "fobject.h"

NAMESPACE_BEGIN( PENSE )
NAMESPACE_BEGIN( Algorithm )
NAMESPACE_BEGIN( Fuzzy )

class TriangleSet;

/**
 *  This class represents a fuzzy triangle which is defined by it's
 *  starting, ending points and partner triangle.
 */
class Triangle : public Object {
public:
	/**
	 *  Contructs a fuzzy triangle.
	 *  @param start start point coordinate
	 *  @param end end point coordinate
	 *  @param name name of the triangle
	 *  @param partner name of the partner triangle
	 */
	Triangle( double start,
		  double end,
		  const std::string& name = "default triangle name",
		  const std::string& partner = "default triangle partner" );

	/**
 	 * Destructs the object.
 	 */
	~Triangle();

	/**
	 *
	 * @return which triangle set this triangle belongs to
	 */
	const TriangleSet*
	of( void );
	
	/**
	 * Sets the partner triangle. Partner triangle is the triangle which corresponds
	 * to one triangle in the other set which is input or output.
	 * @param name
	 */
	void
	setPartner( const std::string& name );
	
	/**
	 * Tells the name of the partner triangle.
	 * @return name of the partner triangle
	 */
	const std::string&
	partner( void ) const;

	/**
	 * Sets the triangle set which this triangle belongs to
	 * @param set triangle set
	 */
	void
	setSet( const TriangleSet *set );

	/**
	 * Tells starting point coordinate of the triangle
	 * @return starting point coordinate
	 */
	double
	start( void ) const
	{
		return m_start;
	}
	
	/**
	 * Tells ending point coordinate of the triangle
	 * @return ending point coordinate
	 */
	double
	end( void ) const
	{
		return m_end;
	}

	/**
	 * Tells middle point cordinate of the triangle which is<br>
	 * ( starting_point + ending_point ) / 2
	 * @return middle point coordinate
	 */
	double
	middle( void ) const
	{
		return m_middle;
	}
	
	/**
	 * Tells the width size of the triangle base.
	 * @return width of the triangle
	 */
	double
	width( void ) const
	{
		return m_width;
	}
	
	/**
	 * Sets the starting point coordinate of the triangle.
	 * @param start starting point coordinate
	 */
	void
	setStart( double start );
	
	/**
	 * Sets the ending point coordinate of the triangle.
	 * @param end ending point coordinate
	 */
	void
	setEnd( double end );

	/**
	 * Sets the middle point coordinate. This method automagically adjusts the
	 * starting and ending points' coordinate as necessary.
	 * @param middle point
	 */
	void
	setMiddle( double middle );

	/**
	 * Increase middle point by x
	 */
	void
	incMiddle( double x );

	/**
	 * Decreases middle point by x
	 */
	void
	decMiddle( double x );
	
	/**
	 * Sets the width. This method automagically adjusts the starting
	 * and ending points' coordinate.
	 * @param width width
	 */
	void
	setWidth( double width );

	/**
	 * Expands the triangle and automagivally adjusts the starting and
	 * ending points' coordinates, keeping the niddle point coordinates
	 * constant ofcourse.
	 * @param x expand x unit
	 */
	void
	expand( double x );

	/**
	 * Shrinks the triangle and automagically adjusts the starting and
	 * ending points' coordinates, keeping the middle point coordinate
	 * constant ofcourse.
	 * @param x shrink x unit
	 */ 
	void
	shrink( double x );
	
	/**
	 * Calculates the area (weight)  of the triangle with provided height h.
	 * @param height height
	 * @returns the area
	 */
	double
	calcArea( double height );

	/**
	 * Tells the area of the triangle.
	 * @returns area of the triangle.
	 */
	double
	area( void ) const
	{
		return m_area;
	}

	/**
	 * This method tells you the membership degree of a value for a
	 * triangle.
	 * @param v value to be evaluated
	 * @return the membership value
	 */
	double
	degree( double v ) const;

	/**
	 * @param  v value to be evaluted
	 * @return true if v is between start and end points of this triangle
	 */
	bool
	contains( double v ) const;

	/**
	 * Prints debug information, not for production release.
	 */
	void
	printInfo() const;
protected:
	/**
	 * Updates the positions, width etc.
	 */
	void
	update();
private:
	/** starting point of the triangle */
	double			m_start;
	/** ending point of the triangle */
	double			m_end;
	/** middle point of the triangle */
	double			m_middle;
	/** width of the triangle */
	double			m_width;
	/** height of the triangle */
	double			m_height;
	/** area of the triangle */
	double			m_area;
	/** partner triangle's name */
	std::string		m_partnerName;
	/** partner triangle object reference */
	const Triangle		*m_partner;
	/** the reference to triangle set which this triangle belongs to */
	const TriangleSet	*m_set;
};

NAMESPACE_END
NAMESPACE_END
NAMESPACE_END

#endif
