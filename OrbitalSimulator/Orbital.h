/*
 * Orbital.h
 *
 *  Created on: Aug 18, 2011
 *      Author: rmartz
 */

#ifndef ORBITAL_H_
#define ORBITAL_H_

#include "3DPoint.h"
#include "3DVector.h"

struct _Orbital {
	3DPoint position;
	3DVector velocity;
	double mass;
	void* user_data;
};
typedef struct _Orbital* Orbital;

Orbital Orbital_createOrbital();
Orbital Orbital_duplicate( Orbital source );

void Orbital_updatePosition( Orbital orbital, double tick_scale );
void Orbital_updateVelocity( Orbital orbital, Vector3D net_force, double tick_scale );

void Orbital_GDestroyNotify( gpointer data );


#endif /* ORBITAL_H_ */
