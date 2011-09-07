/*
 * main.c
 *
 *  Created on: Sep 6, 2011
 *      Author: rmartz
 */


int main( int argc, char** argv ) {

	Universe universe = Universe_createUniverse();


	Orbital orbital;
	int i;
	for( i = 0; i < 3; i++ ) {
		orbital = Orbital_createOrbital();
		Universe_addOrbital( universe, orbital );
	}

	StartSimulation( universe, 1, 0.5 );

	for( i = 0; i < 10; i++ ) {
		// Write the current universe state to a file


		// Advance the current state
		AdvanceTick();
	}

	StopSimulation();
}
