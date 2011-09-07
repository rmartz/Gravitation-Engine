/*
 * 3DVector.h
 *
 *  Created on: Aug 18, 2011
 *      Author: rmartz
 */

#ifndef VECTOR_3D_H_
#define VECTOR_3D_H_

typedef struct Point_3D* Vector3D;


double Vector3D_getMagnitude( Vector3D this );

void Vector3D_normalize( Vector3D this );
void Vector3D_scale( Vector3D this, double scale );
void Vector3D_rotate( Vector3D this, Angle3D axis, double turn );

void Vector3D_free( Vector3D* this );


#endif /* VECTOR_3D_H_ */
