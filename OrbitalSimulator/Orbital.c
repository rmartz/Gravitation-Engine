




Orbital Orbital_createOrbital() {
	Orbital result = malloc(sizeof (*Orbital) );
	result->position = Point3D_createPoint3D();
	result->velocity = Vector3D_createVector3D();
	result->mass = 0;
	result->user_data = NULL;
	return result;
}

Orbital Orbital_duplicate( Orbital source ) {
	Orbital result = malloc(sizeof (*Orbital) );
	result->position = Point3D_duplicatePoint3D( source->position );
	result->velocity = Vector3D_duplicateVector3D( source->velocity );
	result->mass = source->mass;
	result->user_data = source->user_data;
	return result;
}

void Orbital_updatePosition( Orbital orbital, double tick_scale ) {
	Point3D_addVector( orbital->position, orbital->velocity, tick_scale );
}

void Orbital_updateVelocity( Orbital orbital, Vector3D net_force, double tick_scale ) {
	Vector_scale( net_force, tick_scale );
	Vector_addVector( orbital->velocity, net_force );
}

void Orbital_freeOrbital( Orbital* orbital ) {
	Point3D_free( &(orbital->position) );
	Vector3D_free( &(orbital->velocity) );
}

void Orbital_GDestroyNotify( gpointer data ) {
	Orbital_freeOrbital( &data );
}
