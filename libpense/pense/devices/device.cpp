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

#include "device.h"

#include "inputnode.h"
#include "outputnode.h"
#include "../algorithms/algorithm.h"
#include "../environment.h"

#include <stdexcept>

NAMESPACE_BEGIN( PENSE )
NAMESPACE_BEGIN( Device )

Device::Device( const std::string& name, Environment* parent )
 : Object( name, parent ),
   m_aIndex( 0 ),
   m_errorTolerance( 0.01 )
{
	addInputNode( new InputNode( "f" ) );
	// Devices default frequency
	(*this)["f"] = 1000000.0;
	// If there is valid environment, let it add this device to its list
	// and override devices default frequency
	if( parent )
	{
		parent->addDevice( this );
	}
}

Device::~Device()
{
	if( parent() )
	{
		static_cast<Environment*>(parent())->remDevice( name() );
	}
}

bool
Device::addAlgorithm( Algorithm::Algorithm *a, bool p )
{
	// Algorithms are supposed to be unique, hence no duplicate
	// names are allowed
	if( m_aList.count( a->name() ) ) return false;

	// If this is the first algorithm or it's being explicitly told
	// us to make this primary algorithm.
	if( p ) m_primaryAlgo = a->name();

	// Insert the algorithm in our map
	m_aList.insert( AlgorithmEntry( a->name(), a ) );

	// Fetch algorithm's parameters
	Algorithm::ConstParameterList pl = a->parameters();

	// For each parameter of the algorithm create an input node
	// on this device
	Algorithm::ParameterList::const_iterator it;
	for( it = pl.begin(); it != pl.end(); ++it )
	{
		addInputNode( new InputNode( (*it).first, a ) );
	}

	// Finaly, create an output node for this algorithm
	addOutputNode( new OutputNode( a->name(), a ) );
	return true;
}

bool
Device::remAlgorithm( const std::string& a )
{
	if( !m_aList.count( a ) ){
		throw std::invalid_argument( a + ": no such algorithm" );
	}
	// Remove input nodes which belong to this algorithm
	InputNodeList::iterator it;
	for( it = m_iNodes.begin(); it != m_iNodes.end(); ++it )
	{
		if( it->second->parent() == m_aList[ a ] )
		{
			delete it->second;
			remInputNode( it );
		}
	}

	// Remove output node of this algorithm
	remOutputNode( a );

	// Remove the algorithm itself.
	return m_aList.erase( a );
}

Algorithm::Algorithm*
Device::algorithm( const std::string& a )
{
	if( !m_aList.count( a ) )
	{
		throw std::invalid_argument( a + ": no such algorithm" );
	}
	return m_aList[a];
}

void
Device::process()
{
	// Iterate through algorithms
	AlgorithmList::iterator it;
	for( it = m_aList.begin(); it != m_aList.end(); ++it )
	{
		// Each algorithms' output node emits new evaluated values
		m_oNodes[ it->second->name() ]->emit( it->second->evaluate() );
	}
}

void
Device::setErrorTolerance( double e )
{
	m_errorTolerance = e;
}

double
Device::errorTolerance() const
{
	return m_errorTolerance;
}

bool
Device::setPrimaryAlgorithm( const std::string& a )
{
	// See if the given algorithm exists
	if( !m_aList.count( a ) ) return false;
	m_primaryAlgo = a;
	return true;
}

double
Device::value() const
{
	OutputNodeList::const_iterator i;
	i = m_oNodes.find( m_primaryAlgo );
	return i->second->value();
}

const std::string&
Device::primaryAlgorithm() const
{
	return m_primaryAlgo;
}

std::string
Device::toString() const
{
	std::ostringstream stream;
	stream << "[Device][" << name() << "][" << m_oNodes.size() << 
		  " output nodes][" << m_iNodes.size() << 
		  " input nodes][" << m_aList.size() <<
		  " algorithms]";
	return stream.str();
}

OutputNode*
Device::outputNode( const std::string& n )
{
	if( !m_oNodes.count( n ) )
		throw std::invalid_argument( n + ": no such output node" );
	return m_oNodes[ n ];
}

void
Device::printInfo() const
{
	using std::cout;
	using std::endl;
	AlgorithmList::const_iterator at;
	cout << "-------[" << name() << "]-------" << endl 
             << "[Algorithms]" << endl;
	for( at = m_aList.begin(); at != m_aList.end(); ++at )
	{
		cout << "\t[" << at->first << "]" << *(at->second) << endl;
	}
	cout << "[/Algorithms]" << endl;
	
	InputNodeList::const_iterator it;
	cout << "[InputNodes]" << endl;
	for( it = m_iNodes.begin(); it != m_iNodes.end(); ++it )
	{
		cout << "\t" << *(it->second) << endl;
	}
	cout << "[/InputNodes]" << endl;

	OutputNodeList::const_iterator ot;
	cout << "[OutputNodes]" << endl;
	for( ot = m_oNodes.begin(); ot != m_oNodes.end(); ++ot )
	{
		cout << "\t" << *(ot->second) << endl;
	}
	cout << "[/OutputNodes]" << endl << "----------------------------" << endl;
}

/******************************************************************************
 *				OPERATOR OVERLOADING
 *****************************************************************************/
InputNodeListRange
Device::operator[]( const std::string& p )
{
	if( !m_iNodes.count( p ) )
	{
		throw std::invalid_argument( p + ": parameter does not exist." );
	}
	return InputNodeListRange( m_iNodes.equal_range( p ), this );
}

bool
Device::operator==( double v ) const
{
	OutputNodeList::const_iterator i;
	i = m_oNodes.find( m_primaryAlgo );
	double upperBound = i->second->value() + m_errorTolerance;
	double bottomBound = i->second->value() - m_errorTolerance;
	return ( v > bottomBound && v < upperBound );
}

bool
Device::operator!=( double v ) const
{
	return !((*this)==v);
}

// int
// Device::operator int() const
// {
// 	return static_cast<int>(value());
// }
// 
// double
// Device::operator double() const
// {
// 	return value();
// }
/******************************************************************************
 *				PROTECTED METHODS
 *****************************************************************************/

void
Device::addInputNode( InputNode* n )
{
	if( m_iNodes.count( n->name() ) )
	{
		(*n) = m_iNodes.find( n->name() )->second->value();
	}
	m_iNodes.insert( InputNodeEntry( n->name(), n ) );
}

void
Device::remInputNode( const InputNodeList::iterator& it )
{
	m_iNodes.erase( it );
}

void
Device::addOutputNode( OutputNode* n, bool t )
{
	m_oNodes.insert( OutputNodeEntry( n->name(), n ) );
	if( t )
	{
		m_primaryAlgo = n->name();
	}
}

void
Device::remOutputNode( const std::string& a )
{
	m_oNodes.erase( a );
}

/******************************************************************************
 *				INPUT NODES WRAPPER
 *****************************************************************************/

InputNodeListRange::InputNodeListRange( std::pair< InputNodeList::iterator, InputNodeList::iterator > i,
					const Device::Device* d )
 : m_b( i.first ), m_e( i.second ), m_parent( d )
{	
}

InputNodeListRange& 
InputNodeListRange::operator=( double v )
{
	InputNodeList::iterator it;
	for( it = m_b; it != m_e; ++it )
	{
		*(it->second) = v;
	}
	return *this;
}

InputNodeListRange& 
InputNodeListRange::operator+=( double v )
{
	InputNodeList::iterator it;
	for( it = m_b; it != m_e; ++it )
		*(it->second) += v;
	return *this;
}

double
InputNodeListRange::value() const
{
	return m_b->second->value();
}

void
InputNodeListRange::connect( OutputNode* n )
{
	InputNodeList::iterator it;
	for( it = m_b; it != m_e; ++it )
		it->second->connect( n );
}

void
InputNodeListRange::disconnect( OutputNode* n )
{
	InputNodeList::iterator it;
	for( it = m_b; it != m_e; ++it )
		it->second->disconnect( n );
}

/******************************************************************************
 *		STATIC (DIS)CONNECT UTULITY FUNCTIONS
 *****************************************************************************/
void connect( Device* src, const std::string& o,
		     Device* dst, const std::string& i )
{
	if( src && dst )
	{
		(*dst)[i].connect( src->outputNode( o ) );
	}
	else
	{
		throw std::invalid_argument( "Source and destination devices "
					     " should not be NULL" );
	}
}

void disconnect( Device* src, const std::string& o,
			Device* dst, const std::string& i )
{
	if( src && dst )
	{
		(*dst)[i].disconnect( src->outputNode( o ) );
	}
	else
	{
		throw std::invalid_argument( "Source and destination devices "
					     " should not be NULL" );
	}
}
NAMESPACE_END
NAMESPACE_END

