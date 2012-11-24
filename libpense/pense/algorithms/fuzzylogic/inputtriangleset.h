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

#ifndef FINPUTTRIANGLESET_H_
#define FINPUTTRIANGLESET_H_

#include "../../global.h"
#include "triangleset.h"
#include "fuzzyvalue.h"

#include <list>

NAMESPACE_BEGIN( PENSE )
NAMESPACE_BEGIN( Algorithm )
NAMESPACE_BEGIN( Fuzzy )


/**
 *  Fuzzy Input Set, which includes fuzzy triangles for inputs.
 *  This class can fuzify the input.
 */
class InputTriangleSet : public TriangleSet {
public:
	/**
	 * Creates input triang set
	 * @param name name of the set
	 * @return 
	 */
	InputTriangleSet( const std::string& name );

	/**
	 * Frees resources
	 */
	~InputTriangleSet();

	/**
 	* Fuzifies the measured input data.
 	* @param input measured input value
 	* @return fuzzy value list
 	*/
	FuzzyValueList
	fuzify( double input );
};

NAMESPACE_END
NAMESPACE_END
NAMESPACE_END

#endif
