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

#include "inputnode.h"

#include "algorithms/algorithm.h"
#include "outputnode.h"
#include <stdexcept>

NAMESPACE_BEGIN( PENSE )
NAMESPACE_BEGIN( Device )

InputNode::InputNode( const std::string& n, Algorithm::Algorithm* p )
 : Node( n, (Object*)p )
{
}

InputNode::~InputNode()
{
}

bool
InputNode::connect( OutputNode* n )
{
	return Node::connect( n );
}

bool
InputNode::disconnect( OutputNode* n )
{
	return Node::disconnect( n );
}

bool
InputNode::connect( Node* n, bool )
{
	OutputNode* i;
	if( ( i = dynamic_cast< OutputNode* >( n ) ) )
	{
		return Node::connect( i );
	}
	else
	{
		return false;
	}
}

double
InputNode::operator=( double v )
{
	omit( v );
	return v;
}

double
InputNode::operator+=( double v )
{
	omit( m_val + v );
	return m_val;
}

void
InputNode::emit( double )
{
	throw std::logic_error( "Input nodes shouldn't emit signal." );
}

void
InputNode::omit( double v )
{
	m_val = v;
	if( parent() )
	{
		Algorithm::Algorithm* d = static_cast< Algorithm::Algorithm* >( parent() );
		d->assign( name(), v );
	}
}

double
InputNode::value() const
{
	return m_val;
}

std::string
InputNode::toString() const
{
	std::ostringstream stream;
	stream << "[InputNode]" << "["<< (parent()?parent()->name():"none" )
	       << "][" << name() << "=" << value() << "]";
	return stream.str();
}

NAMESPACE_END
NAMESPACE_END
