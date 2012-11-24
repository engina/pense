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

#include "node.h"

NAMESPACE_BEGIN( PENSE )
NAMESPACE_BEGIN( Device )

Node::Node( const std::string& name, Object* parent )
 : Object( name, parent )
{
}

Node::~Node()
{
	NodeList::iterator it;
	for( it = m_nodeList.begin(); it != m_nodeList.end(); ++it )
	{
		(*it)->disconnect( this, false );
	}
}

bool
Node::connect( Node* n, bool r )
{
	m_nodeList.push_back( n );
	if( r )
	{
		return n->connect( this, false );
	}
	return true;
}

bool
Node::disconnect( Node* n, bool r )
{
	NodeList::iterator it;
	for( it = m_nodeList.begin(); it != m_nodeList.end(); ++it )
	{
		if( (*it) == n )
		{
			m_nodeList.erase( it );
			if( r )
			{
				return n->disconnect( this, false );
			}
			return true;
		}
	}
	return false;
}

void
Node::emit( double v )
{
	m_val = v;
	NodeList::const_iterator it;
	for( it = m_nodeList.begin(); it != m_nodeList.end(); ++it )
	{
		(*it)->omit( v );
	}
}

double
Node::value() const
{
	return m_val;
}

ConstNodeList
Node::nodes() const
{
	return m_nodeList;
}

std::string
Node::toString() const
{
	std::ostringstream stream;
	stream << "[Node][" << name() << "][Connected to " << 
		  m_nodeList.size() << " nodes]";
	return stream.str();
}

NAMESPACE_END
NAMESPACE_END
