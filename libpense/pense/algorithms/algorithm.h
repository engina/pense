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

#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include "../global.h"

#include "../object.h"

#include <map>

NAMESPACE_BEGIN( PENSE )
NAMESPACE_BEGIN( Algorithm )

/**
 * Parameter list type
 */
typedef std::map< std::string, double > ParameterList;

/**
 * Safe parameter list type that you can use in your programs.<
 * @code
 * ConstParameterList pl = myAlgo.parameters();
 * @endcode
 * is equal to:
 * @code
 * const ParameterList &pl = myAlgo.parameters();
 * @endcode
 * or
 * @code
 * const std::map< std::string, double > &pl = myAlgo.parameters();
 * @endcode
 */
typedef const ParameterList& ConstParameterList;

/**
 * All algorithms should be derived from this class. <br>
 * For instance, polynomials, fuzzy logic algorithms.<br>
 * @see Polynomail for an example.
 */
class Algorithm : public Object
{
public:

	/**
	 * Algorithm c-tor
	 * @param name name of the algorithm object
	 * @param p parent of this algorithm object, usually a Device
	 */
	Algorithm( const std::string& name = "Default Algorithm", Object *p = NULL );

	/**
	 * Destroys the matheval object and frees resources
	 */
	~Algorithm();

	/**
	 * 
	 * @return list of parameters of this eqation
	 */
	ConstParameterList
	parameters() const;

	/**
	 * 
	 * @param var variable name to look up
	 * @return true if the variable exists, false otherwise
	 */
	bool contains( std::string var );

	/**
	 * 
	 * @param p parameter name to assign value to
	 * @param val value to assign to the variable
	 * @return true on success, false if there is no such variable
	 */
	bool
	assign( const std::string& p, double val );

	/**
	 *
	 */
	double&
	operator[]( const std::string&p );

	/**
	 * Returns the current value of any parameter.<br>
	 * Note that this method doesn't do error checking.
	 * @param p parameters name
	 * @return value of the parameter
	 */
	double
	value( const std::string& p ) const;

	/**
	 * @return the result of the equation with the current parameter values
	 */
	virtual double
	evaluate() = 0;


	/**
	 * @return how many parameters in the algorithm
	 */
	int
	parameterCount() const;

	/**
	 * @return debug information
	 */
	virtual std::string
	toString() const;

protected:
	/**
	 * Adds a parameter to the algorithm's parameter list.
	 * @param p parameter name to be added
	 */
	bool
	addParameter( std::string p );

	/**
	 * Removes a parameter from the parameters list
	 * @param p parameter name to be removed
	 * @return true on success, false if there is no such parameter
	 */
	bool
	remParameter( std::string p );

private:
	/**
	 * Parameter list as std::map< std::string, double >
	 */
	ParameterList m_map;
	
};

NAMESPACE_END
NAMESPACE_END

#endif
