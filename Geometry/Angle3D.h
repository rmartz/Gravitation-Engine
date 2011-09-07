/*
 * 3DAngle.h
 *
 *  Created on: Aug 23, 2011
 *      Author: rmartz
 */

#ifndef ANGLE_3D_H_
#define ANGLE_3D_H_

struct Angle_3D {
	double incline;
	double turn;
};
typedef struct Angle_3D* Angle3D;

/** Creates a new 3DAngle object from a provided Vector object
  * \param source The 3DVector object used to create the 3DAngle
  * \return Pointer to a new 3DAngle object.
  **/
Angle3D Angle3D_fromVector( Vector3D source );

/** Creates a new 3DAngle object from specified angles
  * \param turn The direction along the X/Y axis for the angle
  * \param incline The direction along the turn/Z axis for the angle
  * \return Pointer to a new 3DAngle object.
  **/
Angle3D Angle3D_fromAngle( double turn, double incline );


#endif /* ANGLE_3D_H_ */
