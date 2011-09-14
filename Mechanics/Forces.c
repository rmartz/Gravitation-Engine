#include "Forces.h"

Vector3D Forces_getAttractionBetweenPoints( Point3D source, Point3D target, double mass ) {

	Vector3D difference = Vector3D_fromPointDifference( source, target );

	double distance = Vector3D_getMagnitude( difference );

	// Normalize the difference vector to get our unit vector
	Vector3D_normalize( difference );

	double force = mass / (distance * distance );

	// Scale up our unit vector to now be to force vector
	Vector3D_scale( difference, force );

	return difference;
}

Vector3D Forces_sumAttractionsToPoint( Point3D point, GSList masses ) {

	Vector3D result = Vector3D_createNew();

	GSList temp = masses;
	while( temp != NULL ) {
		masspoint target = (masspoint)temp;

		Vector3D force = Forces_getAttractionBetweenPoints( point, target->position, target->mass );

		Vector3D_add( result, force );

		Vector3D_free( force );

		temp = g_slist_next( temp );
	}

	return result;

}
