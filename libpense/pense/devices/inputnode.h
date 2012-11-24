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

#ifndef INPUT_NODE_H_
#define INPUT_NODE_H_

#include "../global.h"

#include "node.h"

NAMESPACE_BEGIN( PENSE )

NAMESPACE_BEGIN( Algorithm )
class Algorithm;
NAMESPACE_END

NAMESPACE_BEGIN( Device )

class OutputNode;

/**
 * Input node represents a parameter of an algorithm.<br>
 * Assume you have added an Algorithm::Polynomial x*(y+z) to your Device. 
 * Your Device will have three @link #InputNode input nodes @endlink; x, y,z.
 * You can connect other devices' @link #OutputNode output nodes @endlink to
 * this nodes, so that they will update parameters on update.
 */
class InputNode : public Node
{
public:
	/**
	 * @param name name of the parameter this node is preresenting.
	 * @param parent the algorithm which this input node belongs to
	 * @return 
	 */
	InputNode( const std::string& name = "Default Input Node", 
		   Algorithm::Algorithm *parent = 0L );

	/**
	 * Disconnects itself from connected nodes.
	 */
	~InputNode();

	/**
	 * @param n OutputNode to be connected to
	 * @return true on success
	 */
	bool
	connect( OutputNode* n );

	/**
	 * @param n OutputNode to be disconnected from
	 * @return true on success
	 */
	bool
	disconnect( OutputNode* n );

	/**
	 * Reimplemented connect method to make sure if the parameter n
	 * really represents an OutputNode, by runtime type identification
	 * with dynamic_cast.
	 * @param n node to be connected to
	 * @param recursive if true node n also connects to this node
	 * @return true on success
	 */
	bool
	connect( Node* n, bool recursive = true );

	/**
	 * An InputNode doesn't emit signal, if it tries to, an exception will
	 * will be raised.
	 * @param val value to emit
	 */
	void
	emit( double val );

	/**
	 * When this method is called the input node updates the parameter value
	 * of it's parent algorithm. For instance, assume this node represents
	 * parameter <i>x</i> of it's parent algorithm, then when val is emitted
	 * to this signal, it'll omit it, and assign val to x on it's parent
	 * algorithm.
	 * @param val 
	 */
	void
	omit( double val );

	/**
	 * Assign a value to this input node, it's exactly the same as
	 * omit( double ).
	 * @param v value to assign to this node
	 * @return returns the value it self for convenience
	 */
	double
	operator=( double v );

	/**
	 * This is used to increment the input node's value by v.
	 * @param v increment value
	 * @return returns the updated value of this node for convenience
	 */
	double
	operator+=( double v );

	/**
	 * @return current value of the node
	 */
	double
	value() const;

	/**
	 * @return debug information
	 */
	virtual std::string
	toString() const;
};

NAMESPACE_END
NAMESPACE_END

#endif
