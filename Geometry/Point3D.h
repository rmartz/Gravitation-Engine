/*
 * Point3D.h
 *
 *  Created on: Aug 18, 2011
 *      Author: rmartz
 */

#ifndef POINT_3D_H_
#define POINT_3D_H_

struct Point_3D {
	double x;
	double y;
	double z;
};
typedef struct Point_3D* Point3D


/** Creates a new Point3D object defaulting to 0,0,0
  * \return Pointer to a new Point3D object.
  **/
Point3D Point3D_createNew();

/** Creates a new Point3D object from provided coordinates.
  * \param x Absolute position along the X coordinate line
  * \param y Absolute position along the Y coordinate line
  * \param z Absolute position along the Z coordinate line
  * \return Pointer to a new Point3D object.
  **/
Point3D Point3D_createFromPos( double x, double y, double z );

/** Creates a new Point3D object from provided geometric values
  * \param center Point3D representing the location where this Point3D should be centered about.
  * \param radius Distance from the center the Point3D should be.
  * \param angle Rotation about the X,Y coordinates, clockwise facing to -Z, in rotations.
  * \param incline Rotation about the Z,angle coordinates, in rotations. +0.5 is 100% Z, -0.5 is 100% -Z.
  * \return Pointer to a new Point3D object.
  **/
Point3D Point3D_createFromAngle( Point3D center, double radius, double angle, double incline );

/** Creates a new Point3D object from a provided Point3D
  * \param source The Point3D object to clone
  * \return Pointer to a new Point3D object with the same properties as the provided Point3D.
  **/
Point3D Point3D_duplicate( Point3D source );

/** Adds the two points together, and stores the result in the first point.
  * \param this The Point3D to store the result of the addition in
  * \param vector The 3DVector to add
  * \param scale The amount to scale the vector by
  **/
void Point3D_addVector( Point3D this, Vector3D vector, double scale );


#endif /* POINT_3D_H_ */
