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

#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include "global.h"

#include "object.h"

#include <string>
#include <vector>

NAMESPACE_BEGIN( PENSE )

NAMESPACE_BEGIN( Device )
class Device;
NAMESPACE_END

typedef std::vector< Device::Device*> DeviceList;


/**
 * Environment is the largest container in the PENSE framework. It can  host
 * virtually unlimited devices in it. It provides shared parameters for all
 * devices in it, those are including but not limited to frequency of the
 * iteration, environment temperature, humudity etc.<br>
 * Additionally through the Environment object you can set a value to a
 * parameter in all the devices in this environment. Assume it contains
 * 3 devices. Calling `env->assign( "foo", "bar" );' will set parameters
 * foos' values to "bar" on all 3 devices.
 */
class Environment : public Object
{
public:
	/**
	 * Here the most important parameter is frequency parameter. It's where
	 * you define 
	 * @param freq frequency of the environment
	 * @param name name of the environment
	 * @param parent parent of the environment
	 * @return 
	 */
	Environment( uint freq = 1000000,
		     const std::string& name = "default system",
		     Object* parent = 0L );
	~Environment();

	/**
	 *@param  d Device to add
	 */
	void
	addDevice( Device::Device* d );

	/**
	 * @param n device name to be deleted
	 * @return true on success
	 */
	bool
	remDevice( const std::string& n);

	/**
	 * Returns pointer to a specific device according to it's name.
	 * @param n name of the requested device
	 * @return pointer to the requested device
	 */
	Device::Device*
	device( const std::string& n );

	/**
	 * Checks if a device exists in the environment or not. Looks up
	 * by name, since devices in an Environment should have unique
	 * names.
	 * @param n name of the device to loop up
	 * @return true if it exists
	 */
	bool contains( const std::string&n );

	/**
	 * Returns the order of the given device.
	 * @param n name of the device
	 * @return order of the device
	 */
	int order( const std::string&n );

	/**
	 * Swaps the given devices' orders.<br>
	 * @param x device to be swapped
	 * @param y device to be swapped
	 */
	void swap( int x, int y );

	/**
	 * Just for debugging purposes.
	 */
	void printInfo() const;

	/**
	 * @return debug information
	 */
	virtual std::string toString() const;

	/**
	 *  Processes the devices in the environment in given order.
	 */
	void process();

	/**
	 * This is a utulity method to do easy operations on the devices.<br>
	 * @code
	 * Environment env;
	 * Device plant( "my plant", &env );
	 * ...
	 * // Sets parameter V of device "my plant" in the environment to 23.5.
	 * env["my plant"]["V"] = 23.5;
	 * @endcode
	 * @param n name of the device
	 * @return reference to the device 
	 */
	Device::Device&
	operator[]( const std::string& n );

	/**
	 * This is where you define how many iterations you're going to do in
	 * one second, hence the frequency of the system. This parameter will
	 * will be provided to all devices in the Environment by parameter
	 * <i>f</i>.
	 * @param f frequency of the system
	 */
	void
	setFrequency( uint f );

	/**
	 * @return the current frequency of the system
	 */
	uint
	frequency() const;
private:
	//! Current frequency of the system
	uint m_freq;
	//! Device list of the environment
	DeviceList m_dList;
};

NAMESPACE_END

#endif
