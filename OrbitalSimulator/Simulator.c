/*
 * Simulator.c
 *
 *  Created on: Sep 6, 2011
 *      Author: rmartz
 */

Universe current = NULL;
GQueue* universe_buffer = NULL;

int terminate_daemon = 0;
GThread* renderUniverseThread = NULL;
gpointer RenderUniverseDaemonThread( gpointer data ) {
	while( !terminate_daemon ) {
		RenderUniverse();
	}

	// Set this up so we know the daemon thread is gone
	renderUniverseThread = NULL;
	terminate_daemon = 0;
}


int buffer_clear_requested = 0;
Universe buffer_clear_last_good = NULL;

double _time_tick = 1.0;
double _theta = 0.5;

void StartSimulation( Universe start, double time_tick, double theta ) {
	// Block the RenderUniverse thread, if it's running
	G_LOCK( UNIVERSE_RENDER_BUSY );

	// If the RenderUniverse thread isn't running, start it up.
	if( renderUniverseThread == NULL ) {
		renderUniverseThread = g_thread_create( RenderUniverseDaemonThread,
												NULL, 0, NULL);
	}

	// Clear the universe_buffer if it exists, create it if otherwise
	if( universe_buffer ) {
		g_queue_foreach( universe_buffer, Universe_GFuncFree, NULL );
		g_queue_clear( universe_buffer );
	} else {
		universe_buffer = g_queue_new();
	}
	// Free the current universe if it exists, then set it to our start
	Universe_freeUniverse( &current );
	current = start;

	// Clear the various global variables
	buffer_clear_requested = 0;
	buffer_clear_last_good = NULL;

	// Set the time_tick and theta globals
	_time_tick = time_tick;
	_theta = theta;

	// Unblock the RenderUniverse thread
	G_UNLOCK( UNIVERSE_RENDER_BUSY );
}
void StopSimulation() {
	terminate_daemon = 1;
}

// This will begin the process of calculating the next
G_LOCK_DEFINE( UNIVERSE_RENDER_BUSY );
void RenderUniverse() {
	G_LOCK( UNIVERSE_RENDER_BUSY ); {
		if( buffer_clear_requested ) {
			if( buffer_clear_last_good ) {
				// Clear everything in the buffer after buffer_clear_last_good

			} else {
				// Clear the entire buffer
				g_queue_foreach( universe_buffer, Universe_GFuncFree, NULL );
				g_queue_clear( universe_buffer );
			}

			buffer_clear_requested = 0;
		}

		// Find the last Universe
		Universe tail = g_queue_peek_tail( universe_buffer );
		if( tail == NULL ) {
			tail = current;
		}

		// Clone it
		Universe temp = Universe_duplicate( tail );

		// Perform a tick
		Universe_performTick( temp );

		// Add it to the Universe queue
		g_queue_push_tail( universe_buffer, temp );

	} G_UNLOCK( UNIVERSE_RENDER_BUSY );
}


void AdvanceTick() {

	Universe temp = g_queue_pop_head( universe_buffer );
	while( temp == NULL ) {
		// The buffer rendering process is taking too long.
		// Let's wait until he's done, then try again.
		G_LOCK( UNIVERSE_RENDER_BUSY );
		G_UNLOCK( UNIVERSE_RENDER_BUSY );

		temp = g_queue_pop_head( universe_buffer );
	}

	// Swap out the new guy for the "current" step, and free the old guy
	Universe old = current;
	current = temp;
	Universe_freeUniverse( &old );

}

// This will be called any time there is user input or the determinism of the simulation is compromised.
void FlagBufferClear() {
	FlagBufferClearAfter( NULL );
}

// This may happen, for instance, whenever a guided orbital chooses a path based on predicted futures.
void FlagBufferClearAfter( Universe last_good ) {
	buffer_clear_requested = 1;
	buffer_clear_last_good = last_good;
}
