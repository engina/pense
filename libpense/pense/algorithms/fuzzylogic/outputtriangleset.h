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

#ifndef FOUTPUTTRIANGLESET_H_
#define FOUTPUTTRIANGLESET_H_

#include <list>

#include "../../global.h"
#include "triangleset.h"
#include "fuzzyvalue.h"

NAMESPACE_BEGIN( PENSE )
NAMESPACE_BEGIN( Algorithm )
NAMESPACE_BEGIN( Fuzzy )

/**
 *  Fuzzy Output Set, which includes fuzzy triangles for output.
 *  This class defuzifies the fuzified value and gave a crisp output.
 */
class OutputTriangleSet : public TriangleSet {
public:
	/**
	 * Creates a output triangle set
	 * @param name name of the set
	 */
	OutputTriangleSet( const std::string& name );

	/**
	 * Frees resources 
	 */
	~OutputTriangleSet();

	/**
 	*  Gives a crisp output.<br>
	*  This method can raise a std::runtime_error expection if no output
	*  triangles are matched to input triangles.
 	*  @param degrees is the list of fuzified input(s)
 	*  @return The crisp output value
 	*/ 
	double
	defuzify( const FuzzyValueList& degrees );
};

NAMESPACE_END
NAMESPACE_END
NAMESPACE_END

#endif
