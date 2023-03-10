#include"../include/catalogoDrivers.h"

struct catDrivers{
	GHashTable* catDrivers;
};

CatDrivers initCatDrivers(){
	CatDrivers drivers = malloc(sizeof(struct catDrivers));

    drivers->catDrivers = g_hash_table_new_full(g_str_hash, g_str_equal,(GDestroyNotify) NULL,(GDestroyNotify) deleteDriver);
    return drivers;
}

void destroiCatDrivers(CatDrivers drivers){
	g_hash_table_destroy(drivers->catDrivers);
	free(drivers);
}

void insereDriver(CatDrivers drivers, Driver d){
	g_hash_table_insert(drivers->catDrivers, getDriverId(d), d);
}

void updateDriver(CatDrivers drivers, Driver d){
	g_hash_table_replace(drivers->catDrivers, getDriverId(d), d);
}


int contemDriver(CatDrivers drivers, char* key){
	return (int) g_hash_table_contains(drivers->catDrivers, key);
}


Driver procuraDriver(CatDrivers drivers, char* key){
	return (Driver) g_hash_table_lookup(drivers->catDrivers, key);
}

void foreachDriver(CatDrivers drivers, GHFunc func, gpointer info){
	g_hash_table_foreach(drivers->catDrivers, (GHFunc) func, info);
}
