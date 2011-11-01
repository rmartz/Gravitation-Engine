/*
 * Point3D.h
 *
 *  Created on: Aug 18, 2011
 *      Author: rmartz
 */

typedef struct Point_3D* Point3D


/** Creates a new Point3D object defaulting to 0,0,0
  * \return Pointer to a new Point3D object.
  **/
Point3D Point3D_createNew() {
	return Point3D_createFromPos( 0, 0, 0 );
}

/** Creates a new Point3D object from provided coordinates.
  * \param x Absolute position along the X coordinate line
  * \param y Absolute position along the Y coordinate line
  * \param z Absolute position along the Z coordinate line
  * \return Pointer to a new Point3D object.
  **/
Point3D Point3D_createFromPos( double x, double y, double z ) {
	Point3D result = malloc( sizeof(*Point3D) );
	result->x = x;
	result->y = y;
	result->z = z;
	return result;
}

/** Creates a new Point3D object from provided geometric values
  * \param center Point3D representing the location where this Point3D should be centered about.
  * \param radius Distance from the center the Point3D should be.
  * \param angle Rotation about the X,Y coordinates, clockwise facing to -Z, in rotations.
  * \param incline Rotation about the Z,angle coordinates, in rotations. +0.5 is 100% Z, -0.5 is 100% -Z.
  * \return Pointer to a new Point3D object.
  **/
Point3D Point3D_createFromAngle( Point3D center, double radius, double angle, double incline ) {
	int x, y, z;
	x = center->x + sin(angle) * sin(incline) * radius;
	y = center->y + cos(angle) * sin(incline) * radius;
	z = center->z + cos(incline) * radius;
	return Point3D_createFromPos( x, y, z );
}

/** Creates a new Point3D object from a provided Point3D
  * \param source The Point3D object to clone
  * \return Pointer to a new Point3D object with the same properties as the provided Point3D.
  **/
Point3D Point3D_duplicate( Point3D source ) {
	return Point3D_createFromPos( source->x, source->y, source->z );
}

/** Adds the two points together, and stores the result in the first point.
  * \param this The Point3D to store the result of the addition in
  * \param vector The 3DVector to add
  * \param scale The amount to scale the vector by
  **/
void Point3D_addVector( Point3D this, Vector3D vector, double scale ) {
	Vector3D* temp = Vector3D_duplicate( vector );
	Vector3D_scale( temp, scale );

	this->x = temp->x;
	this->y = temp->y;
	this->z = temp->z;

	Vector3D_free( temp );
}

/** Frees the Point3D object
  * \param this A pointer to the Point3D object to free.
  **/
void Point3D_free( Point3D* this ) {

}

