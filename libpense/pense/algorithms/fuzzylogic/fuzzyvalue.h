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

#ifndef FFUZZYVALUE_H_
#define FFUZZYVALUE_H_

#include <string>

#include "../../global.h"
#include "fobject.h"

#include <list>

NAMESPACE_BEGIN( PENSE )
NAMESPACE_BEGIN( Algorithm )
NAMESPACE_BEGIN( Fuzzy )

class Triangle;

/**
 *  This class defines a fuzzy value which consists of a double value
 *  which is degree of membership and a triangle which this value belongs to.
 */
class FuzzyValue : public Object {
protected:
	/** degree of the membership */
	double		degree;
	/** triangle which this fuzzy value belongs to */
	const Triangle*	triangle;
public:
	FuzzyValue( 	double degree, 
			const Triangle* triangle, 
			std::string name );
	~FuzzyValue();

	/**
	 * @returns membership degree
	 */
	double
	getDegree( void ) const
	{
		return degree;
	}

	/**
	 * @returns triangle which this fuzzy value belongs to
	 */
	const Triangle*
	getTriangle( void ) const
	{
		return triangle;
	}
};

typedef std::list<FuzzyValue> FuzzyValueList;

NAMESPACE_END
NAMESPACE_END
NAMESPACE_END

#endif
