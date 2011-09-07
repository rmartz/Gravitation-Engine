/*
 * Universe.h
 *
 *  Created on: Aug 25, 2011
 *      Author: rmartz
 */

#ifndef UNIVERSE_H_
#define UNIVERSE_H_

struct Universe_Instance {
	GSList orbitals;
};
typedef struct Universe_Instance* Universe

Universe Universe_createUniverse();
Universe Universe_duplicate( Universe source );
void Universe_freeUniverse( Universe* Universe );
void Universe_addOrbital( Universe universe, Orbital orbital );
void Universe_performTick( Universe universe );

Universe_GFuncFree( gpointer data, gpointer user_data );

#endif /* UNIVERSE_H_ */
