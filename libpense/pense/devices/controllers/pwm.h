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

#include "../device.h"

NAMESPACE_BEGIN( PENSE )

class Environment;

NAMESPACE_BEGIN( Device )
NAMESPACE_BEGIN( Controller )

class PWM : public Device
{
public:
	PWM( const std::string& name = "Default PWM Controller",
	     Environment* e = 0L );
	~PWM();
	void setCycles( uint c );
	uint cycles() const;
	void setAlgorithm( Algorithm::Algorithm* a );
	Algorithm::Algorithm* algorithm();
	/**
	 * Processes the device for one iteration.<br>
	 * Can throw std::logic_error if frequency of the system is less
	 * than 100Hz
	 */
	void
	process();
private:
	uint m_cycles;
	uint m_process;
};

NAMESPACE_END
NAMESPACE_END
NAMESPACE_END
