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

#include "environment.h"

#include "devices/device.h"

#include <stdexcept>

NAMESPACE_BEGIN( PENSE )

Environment::Environment( uint f, const std::string& n, Object* p )
 : Object( n, p ),
   m_freq( f )
{
}

Environment::~Environment()
{
}

bool
compare( Device::Device* d, const std::string&n )
{
	return ( d->name() == n );
}

bool
Environment::contains( const std::string& n )
{
	DeviceList::const_iterator it;
	for( it = m_dList.begin(); it != m_dList.end(); ++it )
	{
		if( (*it)->name() == n )
		{
			return true;
		}
	}
	return false;
}

void
Environment::addDevice( Device::Device* d )
{
	if( contains( d->name() ) )
	{
		throw std::invalid_argument( d->name() +
				             ": the device already exist." );
	}
	(*d)["f"] = static_cast<double>(frequency());
	m_dList.push_back( d );
}

bool
Environment::remDevice( const std::string& n )
{
	DeviceList::iterator it;
	for( it = m_dList.begin(); it != m_dList.end(); ++it )
	{
		if( (*it)->name() == n )
		{
			m_dList.erase( it );
			return true;
		}
	}
	return false;
}

void
Environment::process()
{
	DeviceList::iterator it;
	for( it = m_dList.begin(); it != m_dList.end(); ++it )
	{
		(*it)->process();
	}
}

int
Environment::order( const std::string&n )
{
	DeviceList::const_iterator it;
 	int i = 0;
	for( it = m_dList.begin(); it != m_dList.end(); ++it, i++ )
	{
		if( (*it)->name() == n )
		{
			return i;
		}
	}
	return -1;
}

void
Environment::swap( int x, int y )
{
	if( x > m_dList.size() || y > m_dList.size() )
	{
		throw std::out_of_range( "Swap values are out of boundary." );
	}
	Device::Device *tmp = m_dList[x];
	m_dList[x] = m_dList[y];
	m_dList[y] = tmp;
}

Device::Device*
Environment::device( const std::string& n )
{
	DeviceList::iterator it;
	for( it = m_dList.begin(); it != m_dList.end(); ++it )
	{
		if( (*it)->name() == n )
		{
			return *it;
		}
	}
	throw std::invalid_argument( n + ": no such device" );
}

Device::Device&
Environment::operator[]( const std::string& n )
{
	return *( device( n ) );
}

void
Environment::setFrequency( uint f )
{
	m_freq = f;
	DeviceList::iterator it;
	for( it = m_dList.begin(); it != m_dList.end(); ++it )
	{
		(*(*it))["f"] = f;
	}
}

uint
Environment::frequency() const
{
	return m_freq;
}

void
Environment::printInfo() const
{
	std::cout << "[Environment][" << name() << "][" << m_freq << 
		  " Hz][" << m_dList.size() << " devices]" << std::endl;
	std::cout << "[Devices (in order)]" << std::endl;
	for( int i = 0; i < m_dList.size(); i++ )
	{
		std::cout << "\t" << *(m_dList[i]) << std::endl;
	}
	std::cout << "[/Devices]" << std::endl;
}

std::string
Environment::toString() const
{
	std::ostringstream stream;
	stream << "[Environment][" << name() << "][" << m_freq << 
		  " Hz][" << m_dList.size() << 
		  " devices]";
	return stream.str();
}

NAMESPACE_END
