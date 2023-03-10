#include"../include/catalogoRides.h"

struct catRides{
	GHashTable* catRides;
};

CatRides initCatRides(){
	CatRides rides = malloc(sizeof(struct catRides));

    rides->catRides = g_hash_table_new_full(g_str_hash, g_str_equal,(GDestroyNotify) deleteRideKey,(GDestroyNotify) deleteRide);
    return rides;
}

void destroiCatRides(CatRides rides){
	g_hash_table_destroy(rides->catRides);
	free(rides);
}

void insereRide(CatRides rides, Ride r){
	g_hash_table_insert(rides->catRides, getIdRides(r), r);
}


int contemRide(CatRides rides, char* key){
	return (int) g_hash_table_contains(rides->catRides, key);
}


Ride procuraRide(CatRides rides, char* key){
	return (Ride) g_hash_table_lookup(rides->catRides, key);
}

void foreachRide(CatRides rides, GHFunc func, gpointer info){
	g_hash_table_foreach(rides->catRides, (GHFunc) func, info);
}