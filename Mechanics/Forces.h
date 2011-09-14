/*
 * Forces.h
 *
 *  Created on: Sep 6, 2011
 *      Author: rmartz
 */

#ifndef FORCES_H_
#define FORCES_H_

Vector3D Forces_getAttractionBetweenPoints( Point3D source, Point3D target, double mass );
Vector3D Forces_sumAttractionsToPoint( Point3D point, GSList masses );


#endif /* FORCES_H_ */
