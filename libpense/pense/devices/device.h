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

#ifndef DEVICE_H_
#define DEVICE_H_

#include "../global.h"

#include "../object.h"

#include <string>
#include <map>

NAMESPACE_BEGIN( PENSE )

class Environment;

NAMESPACE_BEGIN( Algorithm )
class Algorithm;
NAMESPACE_END

NAMESPACE_BEGIN( Device )

class InputNode;
class OutputNode;
class InputNodeListRange;

//! InputNode list type for internal usage
typedef std::multimap< std::string, InputNode* > InputNodeList;
//! OutputNode list type for internal usage
typedef std::map< std::string, OutputNode* > OutputNodeList;
//! Algorithm list type for internal usage
typedef std::map< std::string, Algorithm::Algorithm* > AlgorithmList;
//! Element of AlgorithmList
typedef std::pair< std::string, Algorithm::Algorithm* > AlgorithmEntry;
//! Element of InputNodeList
typedef std::pair< std::string, InputNode* > InputNodeEntry;
//! Element of OutputNodeList
typedef std::pair< std::string, OutputNode* > OutputNodeEntry;

/**
 * This is the base class of all devices in PENSE, including but not limited
 * to plants, sources and controllers.<br>
 * Note that parameter <i>f</i> is reserved in all plants, that represents the
 * frequency of the system.
 */
class Device : public Object
{
public:
	/**
	 * Creates an device named name
	 * @param name of the device
	 * @param parent of the device
	 */
	Device( const std::string& name = "Default Device",
		Environment* parent = 0L);

	/**
	 * Frees resources 
	 */
	~Device();

	/**
	 * Adds an algorithm to the device.<br>
	 * Algorithm names should be unique, if two identical named algorithms
	 * are provided, this method will return false on the second one.
	 * WARNING: Note that frequency <i>f</i> is reserved, it represents
	 * frequency. So if you're using <i>f</i> in your algorithms make sure
	 * that it is meant to be used as frequency.
	 * @param a algorithm to be added
	 * @param primary if true algorithm a will be also marked as primary
	 * @return true on success, false on failure
	 */
	bool
	addAlgorithm( Algorithm::Algorithm* a, bool primary  = false );

	/**
	 * Removes an algorithm
	 * @param n name of the algorithm
	 * @return true on success, false on failure
	 */
	bool
	remAlgorithm( const std::string& n );

	/**
	 * @param a algorithm name i.e. "sin(x)" or "fuzzyMotorController"
	 * @return the output node which represents the algorithm a
	 */
	OutputNode*
	outputNode( const std::string& a ) const;

	/**
	 * This is a convenience method to make it easy to assign a value
	 * to parameter p of all algorithms in this device.
	 * @code
	 * Device foo;
	 * foo.addAlgorithm( new Polynomial( "x*y*z" ) );
	 * foo.addAlgorithm( new Polynomial( "x*k*l" ) );
	 * foo["x"] = 4;
	 * @endcode
	 * The above code makes both algorithms' parameter x = 4.
	 * @param p 
	 * @return 
	 */
	InputNodeListRange
	operator[]( const std::string& p );

	/**
	 * This operator can be used to to see if the device's primary
	 * algorithm is around a specific value. The error tolerance value
	 * has dramatic effect on this method. Here is a little demonstration.
	 * @code
	 * // Create a motor with error tolerance 10.0
	 * Device::Device motor( "my motor", 10.0 );
	 * motor.addAlgorithm( new Algorithm::Polynomial( "x*1000", "algo" ) );
	 * motor["x"] = 10.005;
	 * // This will return true
	 * cout << ( motor == 10000 ? "true" : "false" ) << endl;
	 * // Because the motors actual value is 10005 at the moment, and the
	 * // error tolerance is 10, so any value between 9995 and 10015
	 * // evaluates to true.
	 * @endcode
	 * @param v value to be evaluate
	 * @return true if the value v is close enough to the primary 
	 *         algorithm's output node's value.
	 * @see setErrorTolerance( double )
	 * @see Device( const std::string&, double )
	 */
	bool
	operator==( double v ) const;

	/**
	 * @return !operator==( v )
	 */
	bool
	operator!=( double ) const;

	/**
	 * You can assign value of any device to a double with this overloaded
	 * parameter
	 * @return the value of the primary algorithm
	 * @see operator double()
	 */
// 	operator int() const;

	/**
	 * You can assign value of any device to a double with this overloaded
	 * parameter
	 * @code
	 * PENSE::DCMotor foo;
	 * ...
	 * double w = foo;
	 * @endcode
	 * @return the value of the primary algorithm
	 */
// 	operator double() const;
	/**
	 * @return the value of the primary algorithm
	 */
	double
	value() const;

	/**
	 * @param a algorithm's name which this node belongs to
	 * @return the appropriate OutputNode object pointer
	 */
	OutputNode*
	outputNode( const std::string& a );

	/**
	 * @param a algorithm's name to get
	 * @return Algorithm::Algorithm pointer
	 */
	Algorithm::Algorithm*
	algorithm( const std::string& a );

	/**
	 * Process the device one step, which means; evaluating all the
	 * algorithms this device has, so the output nodes will be updated
	 * with new generated data. The other devices connected to this
	 * device should also be explicitly processed.
	 */
	virtual void process();

	/**
	 * The error tolerance value is used in == operator of this
	 * class.<br>
	 * For instance, assume the current value of the primary output node
	 * is 2500.0001, and if our target value is 2500.0, computer will
	 * think these values are not equal (and he's right). To overcome
	 * such situation we tolerate error. For this particular case,
	 * let us use default error tolerance 0.01<br>
	 * When error tolerance is 0.01 any number between 2500.01 and 2499.09
	 * will be interpreted as equal to 2500.
	 * @param e error tolerance
	 * @see ==(double)
	 */
	void
	setErrorTolerance( double e );
	
       	/**
       	 * @return the current error tolerance value
       	 */
	double
       	errorTolerance() const;

	/**
	 * Sets the primaty algorithm.<br>
	 * This sets the algorithm to be used when operator == called on this
	 * class.
	 * @param a 
	 * @return true on success, false on failure
	 */
	bool
	setPrimaryAlgorithm( const std::string& a );

	/**
	 * @return name of the current primary algorithm 
	 */
	const std::string&
	primaryAlgorithm() const;

	/**
	 * This is supposed to be used with output stream, std::cout,
	 * it prints an information defining this object.
	 * @code
	 * Device::Device foo( "foo" );
	 * cout << foo << endl;
	 * @endcode
	 * @return 
	 */
	virtual std::string
	toString() const;

	/**
	 * This prints verbose debug information to stdout
	 */
	void
	printInfo() const;
protected:
	/**
	 * Adds node n to the input node list
	 * @param n node to be added to the input node list
	 */
	void
	addInputNode( InputNode* n );

	/**
	 * Removes input node which is represented by InputNodeList::iterator it
	 * @param it iterator pointing to the input node to be removed
	 */
	void
	remInputNode( const InputNodeList::iterator& it );	

	/**
	 * Adds node n to the the output node list
	 * @param n node to be added to the output node list
	 * @param t if true this is primary output node
	 */
	void
       	addOutputNode( OutputNode* n, bool t = false );

	/**
	 * Removes output node which represents algorithm a
	 * @param a algorithm's name
	 */
	void
	remOutputNode( const std::string& a );
private:
	//! Input node list
	InputNodeList m_iNodes;

	//! Output node list
	OutputNodeList m_oNodes;

	//! Algorithm list
	AlgorithmList m_aList;

	//! Algorithm index
	uint m_aIndex;

	//! Error tolerance
	double m_errorTolerance;

	//! Name of the primary algorithm
	std::string m_primaryAlgo;
};


/**
 * This is a utulity proxy class which is not meant to be used stand-alone.<br>
 * This class essentially transports all the operations from it's interface
 * to the input nodes it contains.
 */
class InputNodeListRange
{
public:
	/**
	 * @param  range this parameter is supposed to be come from
	 *               std::multimap::equal_range, to be more accurate from
	 *               m_iNodes
	 * @param parent parent of this InputNodeListRange
	 */
	InputNodeListRange( std::pair< InputNodeList::iterator, InputNodeList::iterator > range,
			    const Device* parent );
	/**
	 * This operator assign value v to all input nodes it contains, which
	 * is defined by std::multimap::equal_range.<br>
	 * In essence, what this method do is to call operator== on all input
	 * nodes it contains with parameter v.
	 * @param v the value to be assigned to all input nodes of this range
	 * @return the updated input node list range.
	 */
	InputNodeListRange&
	operator=( double v );

	/**
	 * It's almost the same as operatar==. It calls operator+= on all
	 * input noes with parameter v
	 * @param v 
	 * @return the updated input node list range
	 */
	InputNodeListRange&
	operator+=( double v );

	/**
	 * Connects all input nodes this class is representing to output node n
	 * @param n node to be connected
	 */
	void
	connect( OutputNode* n );

	/**
	 * Disconnects all input nodes from the given output node n
	 * @param n output node to be disconnected from
	 */
	void
	disconnect( OutputNode* n );

	/**
	 * @return begin iterator
	 */
	InputNodeList::iterator
	begin() const;

	/**
	 * @return current value of the node list
	 */
	double
	value() const;

	/**
	 * @return end iterator
	 */
	InputNodeList::iterator
	end() const;
private:
	InputNodeList::iterator m_b, m_e;
	const Device* m_parent;
};

void connect( Device* src, const std::string& o,
		     Device* dst, const std::string& i );

void disconnect( Device* src, const std::string& o,
			Device* dst, const std::string& i );

NAMESPACE_END
NAMESPACE_END

#endif
