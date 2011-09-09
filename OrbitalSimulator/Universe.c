/*
 * Universe.c
 *
 *  Created on: Sep 6, 2011
 *      Author: rmartz
 */

Universe Universe_createUniverse() {
	Universe universe = malloc( sizeof(Universe) );
	universe->orbitals = g_slist_alloc();

	return universe;
}

Universe Universe_duplicate( Universe source ) {
	Universe universe = Universe_createUniverse();

	GSList temp = universe->orbitals;
	while( temp != NULL ) {
		Orbital duplicate = Orbital_duplicate( temp->data );

		Universe_addOrbital( universe, duplicate );

		temp = g_slist_next( temp );
	}

	return universe;
}

void Universe_freeUniverse( Universe* Universe ) {
	// Free our list of orbitals, as well as all the Orbitals contained in the list.
	g_slist_free_full( (*universe)->orbitals, Orbital_GDestroyNotify );

	// Free ourselves
	free( *universe );

	// Set ourselves to NULL, so we don't get confused later.
	(*universe) = NULL;
}

void Universe_addOrbital( Universe universe, Orbital orbital ) {
	universe->orbitals = g_slist_prepend( universe->orbitals, orbital );
}

// Function prototypes that will be passed to a GLib thread pool to perform the steps involved
//   in a universe tick.
double _tick_scale = 1;
void _Universe_addOrbitalsToCollection( gpointer data, gpointer user_data );
void _Universe_performOrbitalUpdateTick( gpointer data, gpointer user_data );

void Universe_performTick( Universe universe, double tick_scale ) {
	_tick_scale = tick_scale;

	OrbitalCollection* collection = OrbitalCollection_createUniverse();

	GThreadPool* thread_pool = g_thread_pool_new(
			_Universe_addOrbitalsToCollection,
			collection,
			-1, 0, NULL);

	// Iterate over all of our orbitals, adding them to the OrbitalCollection,
	//  and keep track of the identifiers we're given back. We'll need that when we
	//  loop over this again.
	GSList temp = universe->orbitals;
	while( temp != NULL ) {
		g_thread_pool_push( thread_pool, temp->data, NULL );

		temp = g_slist_next( temp );
	}

	// Attempt to free the thread pool, but wait until it's done processing all the tasks.
	g_thread_pool_free( thread_pool, 0, 1 );

	// Now iterate over all the orbitals again, calculating the force applied
	//  to each, and update their respective velocities and positions.
	thread_pool = g_thread_pool_new(
				_Universe_performOrbitalUpdateTick,
				collection,
				-1, 0, NULL);

	temp = universe->orbitals;
	while( temp != NULL ) {
		g_thread_pool_push( thread_pool, temp, NULL );

		temp = g_slist_next( temp );
	}

	// Free the thread pool once it's done processing all its tasks.
	g_thread_pool_free( thread_pool, 0, 1 );

	// Now that we're done, let's clean up.
	OrbitalCollection_freeUniverse( &collection );
}
void _Universe_addOrbitalsToCollection( gpointer data, gpointer user_data ) {
	Orbital orbital = (Orbital)data;
	OrbitalCollection* collection = (OrbitalCollection*)user_data;

	// Set up the structure to add to the OrbitalCollection
	masspoint* mp = malloc( sizeof(masspoint) );
	mp->mass = orbital->mass;
	mp->x = orbital->position->x;
	mp->y = orbital->position->y;
	mp->z = orbital->position->z;

	// Insert the masspoint to our OrbitalCollection
	orbital->user_data = OrbitalCollection_addMassToUniverse( collection, mp );
}
void _Universe_performVelocityUpdateTick( gpointer data, gpointer user_data ) {
	OrbitalCollection* collection = (OrbitalCollection*)user_data;
	Orbital orbital = (Orbital)data;

	// The OrbitalCollection ID for this orbital was stored in the user_data member,
	//  so we can just pass that to the getRelevantPoints to find everything we care about.
	GSList relevant_masses = OrbitalCollection_getRelevantPoints( collection, orbital->user_data );

	// Now that we know all the masses that affect this orbital, let's figure out what they actually do
	Vector3D total_force = Forces_sumAttractionsToPoint( orbital->position, relevant_masses );

	// Use our new-found data to figure where we should be in _tick_scale time...
	Orbital_updateVelocity( orbital, total_force, _tick_scale );
	Orbital_updatePosition( orbital, _tick_scale );

	// Clean up once we're done.
	g_slist_free( relevant_masses );
	Vector3D_free( &total_force );
}


Universe_GFuncFree( gpointer data, gpointer user_data ) {
	Universe universe = (Universe)data;
	Universe_freeUniverse( &universe );
}


