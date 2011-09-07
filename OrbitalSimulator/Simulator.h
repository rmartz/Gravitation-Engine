/*
 * Simulator.h
 *
 *  Created on: Sep 6, 2011
 *      Author: rmartz
 */

#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include <pthread.h>

#include "universe.h"

/** Starts the simulation with a provided Universe starting point and using global constants for accuracy and speed
  * \param start The Universe to start the simulation with.
  * \param time_tick How to scale changes in position and velocity. Higher numbers makes a faster universe.
  * \param theta A cutoff between accuracy and speed in the sumulation.
  **/
void StartSimulation( Universe start, double time_tick, double theta );
void StopSimulation();

// This will begin the process of calculating the next
void RenderUniverse();

// Advance the current instant
void AdvanceTick();

// This will be called any time there is user input or the determinism of the simulation is compromised.
void FlagBufferClear();

// This may happen, for instance, whenever a guided orbital chooses a path based on predicted futures.
void FlagBufferClearAfter( Universe last_good );

#endif /* SIMULATOR_H_ */
