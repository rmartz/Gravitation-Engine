/*
 * bh_node.c
 *
 *  Created on: Jul 20, 2011
 *      Author: rmartz
 */
#include "geometry.h"



#define NUMBER_OF_CHILDREN 8

typedef struct BHTree {
	Point3D* center;
	Point3D* size;

	BHNode* child;
};

typedef struct BHNode {

	double size;

	BHLeaf* value;
	BHNode** child;

} BHNode;
typedef struct BHLeaf {
	Point3D* center;
	double mass;
	void* value;
};

BHNode BH_CreateTree( Point3D size, Point3D center ) {
	BHTree* result = malloc( sizeof( BHTree ) );
	result->center = Point3D_FromPoint( center );
	result->size = Point3D_FromPoint( size );
	result->child = NULL;
}

BHLeaf _BH_CreateLeaf( Point3D center, double mass, void* data ) {
	BHLeaf* result = malloc( sizeof( BHLeaf ) );
	result->center = center;
	result->mass = mass;
	result->data = data;
	return result;
}
BHNode _BH_CreateNode( double size ) {
	BHNode* result = malloc( sizeof( BHNode ) );
	result->size = size;
	result->value = NULL;
	result->child = NULL;
	return result;
}

void BH_InsertValue( BHTree* tree, Point3D* location, double mass, void* data ) {
	// When we insert into the tree, we want to "normalize" the location
	//  by making the location relative to our center.

	// Clone the location so we don't hurt anything outside.
	location = Point3D_FromPoint( location );

	// Create the leaf object we'll actually be inserting.
	BHLeaf* leaf = _BH_CreateLeaf( location, mass, data );

	// Do the insertion.
	_BH_InsertValueToNode( tree->child, leaf );
}
BHNode _BH_InsertValueToNode( BHNode* node, BHLeaf* value ) {
if(!node)
	return NULL;

	if(node->child == NULL) {
		if(node->value == NULL) {
			// An empty node with no value? Seems too good to be true...
			node->value = value;
		} else {
			// Node was a leaf, but now I'm here.
			// Gotta make a new layer of nodes, and move both values to there.

			// Create the new layer
			node->child = malloc( sizeof( BHNode* ) * NUMBER_OF_CHILDREN );
			int i;
			for( i = 0; i < NUMBER_OF_CHILDREN; i++ ) {
				node->child[i] = _BH_CreateNode( node->size / 2 );
			}

			// Recurse with the existing value into the new layer
			BHLeaf* temp = node->value;
			node->value = NULL;
			_BH_InsertValueToNode( node, node->value );

			// Recurse with my point into the new layer.
			_BH_InsertValueToNode( node, value );
		}
	} else {
		// If we have children, decide which child is best to handle this point.

	}
}
