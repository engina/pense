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

#ifndef POLYNOMIAL_H_
#define POLYNOMIAL_H_

#include "../global.h"

#include "algorithm.h"

#include <map>

NAMESPACE_BEGIN( PENSE )
NAMESPACE_BEGIN( Algorithm )

/**
 * This class holds an equation parsed by libmatheval.
 * @code
 * #include <polynomial.h>
 * #include <stdexcept>
 * #include <iostream>
 * 
 * using namespace std;
 
 * int main( void )
 * {
 *	try
 *	{
 *		// Create an Polynomial object for equation "x*y*z"
 *		PENSE::Polynomial p( "x*y*z" );
 *
 *		// Evaluate the equation for values of x = 1, y = 2, z = 3
 *		cout << p.evaluate_x_y_z( 1, 2, 3 ) << endl;
 *
 *		// See if a variable name exists or not
 *		cout << "x exist: " << ( p.contains( "x" ) ? "yes" : "no" ) << endl; // this will print yes
 *		cout << "k exist: " << ( p.contains( "k" ) ? "yes" : "no" ) << endl; // this will print no
 *
 *		// Assign variable values
 *		p.assign( "x", 2 );
 *		p.assign( "y", 3 );
 *		p.assign( "z", 4 );
 *
 *		// Evaluate equation with the new assigned values
 *		cout << p.evaluate() << endl;
 *
 *		// Here's the parameter list of the equation, in this case; x, y, z
 *		PENSE::Polynomial::ConstParameterList pl = p.parameters();
 *
 *		// iterator which has both variable name and the very current value
 *		PENSE::Polynomial::ParameterList::const_iterator it;
 *
 *		// Evaluate the equation for values of x = 1, y = 2, z = 3 again
 *		cout << p.evaluate_x_y_z( 1, 2, 3 ) << endl;
 *
 *		// And iterate through the parameter list which we've fetched above. Note that it'll print
 *		// x = 1
 *		// y = 2
 *		// z = 3
 *		// Because evaluate_x, evaluate_x_y and evaluate_x_y_z update those values upon
 *		// evaluation
 *
 *		for( it = pl.begin(); it != pl.end(); ++it )
 *		{
 *			cout << (*it).first << "=" << (*it).second << endl;
 *		}
 *	}
 *	// If we've provided an invalid equation like "x****y", this exception would be raised
 *	catch( std::invalid_argument const& e )
 *	{
 *		cerr << "Invalid equation:" << e.what() << endl;
 *	}
 *	return 0;
 * }
 * @endcode
 */
class Polynomial : public Algorithm
{
public:

	/**
	 * Creates a equation object from given equation
	 * @param eq equation
	 * @param name name of the polynomial
	 * @param p parent object
	 */
	Polynomial( const std::string& eq,
		    const std::string& name = "Default Polynomial Algorithm",
		    Object* p = NULL );

	/**
	 * Destroys the matheval object and frees resources
	 */
	~Polynomial();

	/**
	 * 
	 * @return the result of the equation with the current parameter values 
	 */
	double
	evaluate();

	/**
	 * 
	 * @param count number of parameters you're passing
	 * @param names parameter list
	 * @param values value list
	 * @return evaluated result of the equation
	 */
	double
	evaluate( int count, char** names, double *values );

	/**
	 * This function will calculate the equation for the value of
	 * x provided by user. The value of "x" will be updated in
	 * the parameter list also. Which means;
	 * @code
	 * myPolynomial.assign( "x", 3 );
	 * cout << myPolynomial.evaluate() << endl;
	 * // is same with
	 * cout << myPolynomial.evaluate_x( 3 ) << endl;
	 * @endcode
	 * @param x value of the parameter x
	 * @return evaluated result of the equation
	 */
	double
	evaluate_x( double x);

	/**
	 * @see evaluate_x
	 * @param x value of the parameter x
	 * @param y value of the parameter y
	 * @return evaluated result of the equation
	 */
	double
	evaluate_x_y( double x, double y );

	/**
	 * @see evaluate_x
	 * @param x value of the parameter x
	 * @param y value of the parameter y
	 * @param z value of the parameter z
	 * @return evaluated result of the equation
	 */
	double
	evaluate_x_y_z( double x, double y, double z );

	/**
	 * @return the current equation in string representation
	 */
	std::string
	equation() const;

	/**
	 * @return debug information
	 */
	virtual std::string
	toString() const;
protected:
	/**
	 * Parses parameters of an equation, for example x*(y^z) has three
	 * parameters; x, y, z.
	 */
	void
	parse_parameters();

	/**
	 * This holds the matheval object
	 */
	void*	m_e;
};

NAMESPACE_END
NAMESPACE_END

#endif
