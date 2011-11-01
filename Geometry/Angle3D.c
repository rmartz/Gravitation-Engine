
/** Creates a new 3DAngle object from a provided Vector object
  * \param source The 3DVector object used to create the 3DAngle
  * \return Pointer to a new 3DAngle object.
  **/
Angle3D Angle3D_fromVector( Vector3D source ) {
	return (Angle3D)Vector3D_duplicate( source );
}

/** Creates a new 3DAngle object from specified angles
  * \param turn The direction along the X/Y axis for the angle
  * \param incline The direction along the turn/Z axis for the angle
  * \return Pointer to a new 3DAngle object.
  **/
Angle3D Angle3D_fromAngle( double turn, double incline ) {
	return (Angle3D)Vector3D_fromAngle( 1, turn, incline );
}

