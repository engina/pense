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

#include "outputnode.h"

#include "inputnode.h"
#include "../algorithms/algorithm.h"

#include <stdexcept>

NAMESPACE_BEGIN( PENSE )
NAMESPACE_BEGIN( Device )

OutputNode::OutputNode( const std::string& n, Algorithm::Algorithm *p )
 : Node( n, (Object*)p )
{
}

OutputNode::~OutputNode()
{
}

bool
OutputNode::connect( InputNode* n )
{
	return Node::connect( n, false );
}

bool
OutputNode::disconnect( InputNode* n )
{
	return Node::disconnect( n );
}

bool
OutputNode::connect( Node* n, bool r )
{
	if( dynamic_cast< InputNode* >( n ) )
	{
		return Node::connect( n, r );
	}
	else
	{
		return false;
	}
}

void
OutputNode::omit( double )
{
	throw std::logic_error( "Output nodes shouldn't omit signal." );
}

std::string
OutputNode::toString() const
{
	std::ostringstream stream;
	stream << "[OutputNode][" << (parent()?parent()->name():"none") << "][" << name() << "="
	       << value() << "]";
	return stream.str();
}

NAMESPACE_END
NAMESPACE_END
