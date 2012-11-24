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

#ifndef MOTOR_H_
#define MOTOR_H_

#include "../device.h"

#include <string>

NAMESPACE_BEGIN( PENSE )
class Environment;

NAMESPACE_BEGIN( Device )
NAMESPACE_BEGIN( Plant )

/**
 * This class represents a DC electric motor's mathematical modelling.<br>
 * Basically, in each iteration the device is accelerated by the following
 * equation:
 * \f[ \frac{\partial\omega}{\partial t}=\frac{T_s}{J}(1-\frac{\omega}{\omega_f}) \f]
 * Where \f$ T_s \f$ is stall torque defined as follows:
 * \f[ T_s=\frac{k_t V}{R} \f]
 * and \f$ \omega_f \f$ is final angular velocity of the motor, also defined as:
 * \f[ \omega_f=\frac{T_s}{k_e} \f]
 * In above equations; <br>
 * \f$ J \f$ refers to moment of inertia of the load which is usually rotor and
 * the load itself<br>
 * \f$ k_t \f$ is torque constant <br>
 * \f$ k_e \f$ is voltage constant <br>
 * Also note that motor takes Environment frequency into account.<br>
 * NOTE:This motor model should be improved.
 */
class DCMotor : public Device
{
public:
	/**
	 * @param n name of the motor
	 * @param parent parent of this motor
	 */
	DCMotor(  const std::string& n = "default motor",
		Environment* parent = 0L );
	/**
	 * Frees resources
	 */
	~DCMotor();

	/**
	 * Set loads moment of inertia
	 * @param e moment of inertia
	 */
	void
	setLoad( const std::string& e );

	/**
	 * Iterate motor simulation
	 */
	void
	process();
private:
};

NAMESPACE_END
NAMESPACE_END
NAMESPACE_END

#endif
