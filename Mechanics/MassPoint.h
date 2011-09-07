/*
 * MassPoint.h
 *
 *  Created on: Sep 6, 2011
 *      Author: rmartz
 */

#ifndef MASSPOINT_H_
#define MASSPOINT_H_

struct masspoint {
 double mass;
 Point3D position;
 void* user_data;
};
typedef masspoint MassPoint;

#endif /* MASSPOINT_H_ */
