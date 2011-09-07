/*
 * OrbitalCollection.h
 *
 *  Created on: Aug 18, 2011
 *      Author: rmartz
 */

#ifndef ORBITALCOLLECTION_H_
#define ORBITALCOLLECTION_H_

#include "3DPoint.h"

typedef void* OrbitalCollection;

/** Creates a new Universe object for organizing masses
  * \param theta The cutoff to be used for accuracy versus speed of the Barnes-Hut algorithm.
  * \return NULL on failure. Otherwise, returns a pointer to a Universe structure.
  **/
void* OrbitalCollection_createUniverse(double theta);

/** Adds a mass-point to a Universe construct
  * \param universe The universe to add the mass-point to
  * \param mass The mass of the mass-point to add
  * \param x, y, z The coordinates to add the mass-point at
  * \return Any kind of unique ID for the point added. NULL on failure.
  **/
void* OrbitalCollection_addMassToUniverse(void* universe, masspoint* point);

/** Generates a list of all relevant mass-points near a provided mass-point (But not including the provided mass-point)
  * \param universe The universe to add the mass-point to
  * \param point A unique ID provided by the addMassToUniverse function to identify point in question
  * \return A GList of mass-point structs. Order does not matter. Must not include the point identified by the "point" param. Mass-points far away from the provided point should be grouped together in a manner similar to the Barnes-Hut algorithm. All points in the universe should be included in this list in some way. NULL on failure.
  **/
GSList* OrbitalCollection_getRelevantPoints(void* universe, void* point);

/** Generates a list of all points added to the universe.
  * \param universe The universe to retrieve all points from.
  * \return A GList of all mass-point structs added to the universe. NULL on failure.
  **/
GSList* OrbitalCollection_getAllPoints(void* universe);

/** Destroys the universe structure, freeing all memory consumed.
  * \param universe A pointer-to-a-pointer of the universe to be destroyed
  * \return 1 on success, 0 on failure.
  **/
int OrbitalCollection_freeUniverse(void** universe);


#endif /* ORBITALCOLLECTION_H_ */
