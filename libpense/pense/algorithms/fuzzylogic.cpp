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

#include "fuzzylogic.h"
#include "fuzzylogic/triangle.h"
#include "fuzzylogic/inputtriangleset.h"
#include "fuzzylogic/outputtriangleset.h"

NAMESPACE_BEGIN( PENSE )
NAMESPACE_BEGIN( Algorithm )

FuzzyLogic::FuzzyLogic( const std::string& name, Object* parent )
 : Algorithm( name, parent ),
   m_iSet( new Fuzzy::InputTriangleSet( "standard input" ) ),
   m_oSet( new Fuzzy::OutputTriangleSet( "standart output" ) )
{
	addParameter( "input" );
}

FuzzyLogic::~FuzzyLogic()
{
	delete m_iSet;
	delete m_oSet;
}

bool
FuzzyLogic::addInputTriangle(	double s,
				double e,
				const std::string& n )
{
	return m_iSet->add( new Fuzzy::Triangle( s, e, n, "" ) );
}

bool
FuzzyLogic::remInputTriangle( const std::string& name )
{
	return m_iSet->remove( name );
}

bool
FuzzyLogic::addOutputTriangle(	double s,
				double e,
				const std::string& n,
				const std::string& p )
{
	return m_oSet->add( new Fuzzy::Triangle( s, e, n, p ) );
}

bool
FuzzyLogic::remOutputTriangle( const std::string& name )
{
	return m_oSet->remove( name );
}

double
FuzzyLogic::evaluate()
{
	return m_oSet->defuzify( m_iSet->fuzify( value( "input" ) ) );
}

double
FuzzyLogic::evaluate( double x )
{
	assign( "input", x );
	return evaluate();
}

NAMESPACE_END
NAMESPACE_END
