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

#include "fuzzyvalue.h"

NAMESPACE_BEGIN( PENSE )
NAMESPACE_BEGIN( Algorithm )
NAMESPACE_BEGIN( Fuzzy )

/**
 * This is the object that holds a fuzified value. A fuzzified value consists
 * of two information; degree of membership, the triangle which the membership
 * belongs.
 * @param d degree of membership
 * @param t triangle which the fuzzified value belongs to
 * @param n object name
 */
FuzzyValue::FuzzyValue( double d, const Triangle* t, std::string n )
 : Object( n )
{
	degree = d;
	triangle = t; 
}

/**
 * Destructor
 */
FuzzyValue::~FuzzyValue()
{
}

NAMESPACE_END
NAMESPACE_END
NAMESPACE_END
