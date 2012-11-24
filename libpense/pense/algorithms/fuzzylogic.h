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

#ifndef FUZZYLOGIC_ALGO_H_
#define FUZZYLOGIC_ALGO_H_

#include "../global.h"

#include "algorithm.h"

NAMESPACE_BEGIN( PENSE )
NAMESPACE_BEGIN( Algorithm )

NAMESPACE_BEGIN( Fuzzy )
class Triangle;
class InputTriangleSet;
class OutputTriangleSet;
NAMESPACE_END

/**
 * This class makes use of the FuzzyLogic framework which is in
 * $PENSE_SRC/pense/algorithms/fuzzylogic<br>
 * One can say that this is a wrapper class which derives from Algorithm to
 * form a valid PENSE algorithm.<br>
 * This Algorithm has a fixed parameter "input", and that's the only input
 * which is being evaluated. So, what programmer should do is to create
 * a fuzzy logic object, add input triangles, add output triangles,
 * assign an input value and evaluate it. Alternatively you can assign a value
 * within evaluate( double ) too.
 * @code
 * Algorithm::FuzzyLogic f;
 * f.addInputTriangle( 10.0, 20.0, "too slow" );
 * ...
 * f["input"] = 15.0;
 * f.evaluate();
 * @endcode
 * This Algorithm can be used for fuzzy logic controllers.
 */
class FuzzyLogic : public Algorithm
{
public:
	/**
	 * Creates a fuzzy logic algorithm.
	 * @param name name of this algorithm
	 * @param parent parent of this algorithm
	 */
	FuzzyLogic( const std::string& name = "default fuzzy logic algorithm",
		    Object* parent = 0L );

	/**
	 * Frees resources
	 */
	~FuzzyLogic();

	/**
	 * Adds an input triangle.<br>
	 * You can define a triangle by it's start point, end point and a name.
	 * You can think of these triangles as the triangles on the vertical axis.
	 * @param start start point of the triangle
	 * @param end end point of the triangle
	 * @param name name of the triangle
	 * @return true on success
	 */
	bool
	addInputTriangle( double start,
			  double end,
			  const std::string& name );

	/**
	 * @param  name of the triangle to be removed
	 * @return true on sucecss
	 */
	bool
	remInputTriangle( const std::string& name );

	/**
	 * Adds an output triangle.<br>
	 * You can think of ouput triangles as the triangles on the horizontal axis.
	 * @param start start point of the triangle
	 * @param end end point of the triangle
	 * @param name name of the triangle
	 * @param partner name of the input triangle which this output triangle
	 *                will be partner with.
	 * @return true on success
	 */
	bool
	addOutputTriangle( double start,
			   double end,
			   const std::string& name,
			   const std::string& partner );

	/**
	 * @param  name output triangles name to be removed
	 * @return true on success
	 */
	bool
	remOutputTriangle( const std::string& name );

	/**
	 * This fuzifies the input internally according to input triangles.
	 * Then defuzifies this fuzified value according to the output
	 * triangles and gives the crisp output.<br>
	 * The input value in this case is value of parameter "input".
	 * @return the crisp output value
	 */
	double
	evaluate();

	/**
	 * This updates the "input" parameters value and calls evaluate().
	 * @see evaluate()
	 * @param  val value to be evaluated
	 * @return the crisp output value
	 */
	double
	evaluate( double val );
private:
	//! Input triangles list
	Fuzzy::InputTriangleSet		*m_iSet;
	//! Output triangles list
	Fuzzy::OutputTriangleSet	*m_oSet;

};

NAMESPACE_END
NAMESPACE_END
#endif
