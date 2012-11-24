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

#ifndef NODE_H_
#define NODE_H_

#include "../global.h"

#include "../object.h"


#include <string>
#include <list>

NAMESPACE_BEGIN( PENSE )
NAMESPACE_BEGIN( Device )

/**
 * Parameter list type
 */
class Node;
typedef std::list<Node*> NodeList;

/**
 * Safe node list type that you can use in your programs.
 */
typedef const NodeList& ConstNodeList;

/**
 * This is the abstract base class of nodes.<br>
 * Every node should be derived from this class. Node objects are capable of
 * connecting each other and keeping a list of connections.<br>
 * Nodes disconnects upon destruction.
 */
class Node : public Object
{
public:
	/**
	 * Node c-tor
	 * @param name name of the node 
	 * @param parent parent of this node. This is usually an algorithm.
	 */
	Node( const std::string& name, Object* parent );

	/**
	 * Disconnects itself from all connected nodes.
	 */
	~Node();

	/**
	 * Connects this node to the node n provided by the user.
	 * When update() is called, this node will call update()
	 * of each node whome this node connected to.
	 * @param n the node to be connected to
	 * @param recursive if true node n also connects to this node.
	 * @return true on success, false on failure
	 */
	virtual bool
	connect( Node* n, bool recursive = true );

	/**
	 * Disconnects the FIRST occurence of node n from this node.<br>
	 * No more updates will be received by n from this node nor no more
	 * updates will be sent.
	 * @param n node to be disconnected
	 * @param recursive should the node being disconnected also
	 *                  disconnet itself from this node
	 * @return true on success, false on failure
	 */
	virtual bool
	disconnect( Node* n, bool recursive = true  );

	/**
	 * Emits value v to all connected nodes.<br>
	 * What is internally happening is all nodes omit( double ) method
	 * is being called with value v.
	 * @param v value to be emitted
	 */
	virtual void
	emit( double v );

	/**
	 * Omit emitted signal from other nodes. <br>
	 * Since this is a pure virtual method you should implement this.
	 * This is where you define what your node really does.
	 * @param v received value
	 */
	virtual void
	omit( double v ) = 0;


	/**
	 * Nodes keep a copy of the value they've transmitted and with
	 * this method you can retrive the last value of this node.
	 * @return value of the node
	 */
	double
	value() const;

	/**
	 * @return the list of connected nodes.
	 */
	ConstNodeList
	nodes() const;

	/**
	 * @return debug information
	 */
	virtual std::string
	toString() const;
protected:
	//! Current value of this node, i.e. last omitted value
	double m_val;
private:
	//! Connected node list
	NodeList m_nodeList;
};

NAMESPACE_END
NAMESPACE_END

#endif
