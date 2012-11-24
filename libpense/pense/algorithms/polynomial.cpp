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

#include "polynomial.h"

#include <stdexcept>
#include <matheval.h>

NAMESPACE_BEGIN( PENSE )
NAMESPACE_BEGIN( Algorithm )

Polynomial::Polynomial( const std::string& e, const std::string& n, Object *p )
 : Algorithm( n, p )
{
	char* f = strdup( e.c_str() );
	m_e = evaluator_create( f );
	free( f );
	if( !m_e )
	{
		throw std::invalid_argument( e + ": invalid polynomial" );
	}
	
	parse_parameters();
}

Polynomial::~Polynomial()
{
	evaluator_destroy( m_e );
}

double
Polynomial::evaluate()
{
	char **names = NULL;
	double *values = NULL;
	int i;
	ConstParameterList pl = parameters();
	ParameterList::const_iterator it;
	for( i = 0, it = pl.begin(); it != pl.end(); ++it, i++ )
	{
		names = (char**)realloc( names, sizeof( *names ) * ( i + 1 ) );
		values = (double*)realloc( values, sizeof( double ) * ( i + 1 ) );
		names[i] = (char*)malloc( ( (*it).first ).length() + 1 );
		strcpy( names[i], ( (*it).first ).c_str() );
		values[i] = (*it).second;
	}

	double result;
	result = evaluator_evaluate( m_e, pl.size(), names, values );

	for( i-- ; i != -1; i-- )
	{
		free( names[i] );
	}
	free( values );
	free( names );
	return result;
}

double
Polynomial::evaluate( int count, char** names, double *values )
{
	return evaluator_evaluate( m_e, count, names, values );
}

double
Polynomial::evaluate_x( double x )
{
	assign( "x", x );
	return evaluator_evaluate_x( m_e, x );
}

double
Polynomial::evaluate_x_y( double x, double y )
{
	assign( "x", x );
	assign( "y", y );
	return evaluator_evaluate_x_y( m_e, x, y );
}

double
Polynomial::evaluate_x_y_z( double x, double y, double z )
{
	assign( "x", x );
	assign( "y", y );
	assign( "z", z );
	return evaluator_evaluate_x_y_z( m_e, x, y, z );
}

void
Polynomial::parse_parameters()
{
	char** names;
	int i, count;

	evaluator_get_variables( m_e, &names, &count);
	for( i = 0; i < count; i++)
		addParameter( names[i] );
}

std::string
Polynomial::equation() const
{
	return std::string( evaluator_get_string( m_e ) );
}

std::string
Polynomial::toString() const
{
	std::ostringstream stream;
	stream << "[Polynomial][" << name() << "][" << equation() << "][" <<
		   parameterCount() << " parameters]";
	return stream.str();
}

NAMESPACE_END
NAMESPACE_END
