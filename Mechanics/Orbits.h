/*
 * Orbits.h
 *
 *  Created on: Sep 6, 2011
 *      Author: rmartz
 */

#ifndef ORBITS_H_
#define ORBITS_H_

Vector3D Orbits_findCircularOrbitalVelocity( Orbital orbital, Orbital center, Angle3D axis );
Vector3D Orbits_findElipticalOrbitalVelocity( Orbital orbital, Orbital center, Angle3D axis, double apoapsis, double periapsis, int direction );

#endif /* ORBITS_H_ */
