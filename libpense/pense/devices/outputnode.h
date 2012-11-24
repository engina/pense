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

#ifndef OUTPUT_NODE_H_
#define OUTPUT_NODE_H_

#include "../global.h"

#include "node.h"
#include <string>

NAMESPACE_BEGIN( PENSE )

NAMESPACE_BEGIN( Algorithm )
class Algorithm;
NAMESPACE_END

NAMESPACE_BEGIN( Device )

class Device;

class InputNode;

/**
 * OutputNode object is basically a node that can only emit (send) signals but not
 * receive (omit) them.<br>
 * In a Device, OutputNode represents an algorithms output. For instance, equation
 * \f$ \sin(x)\cos(y) \f$. This equation can be represented with two InputNode
 * objects and one OutputNode object. The result of this algorithm is emitted by this
 * OutputNode object.
 */
class OutputNode : public Node
{
public:
	/**
	 * @param a algorithms name which we're representing
	 * @param parent algorithm which we're representing
	 */
	OutputNode( const std::string& a = "Default Output Node",
		    Algorithm::Algorithm *parent = 0L );

	/**
	 * Frees resources and disconnects itself from connected nodes.
	 */
	~OutputNode();

	/**
	 * @param n InputNode to be connected to
	 * @return true on success
	 */
	bool connect( InputNode* n );

	/**
	 * Reimplemented connect method which does runtime type identity
	 * checking with dynamic_cast.
	 * @param n node to be connected to
	 * @param recursive if true Node n also connects itself to this
	 * @return true on success
	 */
	bool connect( Node* n, bool recursive );

	/**
	 * @param n InputNode to be disconnected from
	 * @return true on success
	 */
	bool disconnect( InputNode* n );

	/**
	 * An OutputNode should never omit a signal, remember that output nodes
	 * are supposed to be one way, i.e. they only emit signals not omit
	 * them.
	 * @param v
	 */
	void omit( double v );

	/**
	 * @return debug information
	 */
	virtual std::string
	toString() const;
};

NAMESPACE_END
NAMESPACE_END

#endif
