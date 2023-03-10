#include"../include/catalogoUsers.h"

struct catUsers{
	GHashTable* catUsers;
};

CatUsers initCatUsers(){
	CatUsers users = malloc(sizeof(struct catUsers));

    users->catUsers = g_hash_table_new_full(g_str_hash, g_str_equal,(GDestroyNotify) deleteUserKey,(GDestroyNotify) deleteUser);
    return users;
}

void destroiCatUsers(CatUsers users){
	g_hash_table_destroy(users->catUsers);
	free(users);
}

void insereUser(CatUsers users, User u){
	g_hash_table_insert(users->catUsers, getUserUName(u), u);
}


int contemUser(CatUsers users, char* key){
	return (int) g_hash_table_contains(users->catUsers, key);
}


User procuraUser(CatUsers users, char* key){
	return (User) g_hash_table_lookup(users->catUsers, key);
}

void foreachUser(CatUsers Users, GHFunc func, gpointer info){
	g_hash_table_foreach(Users->catUsers, (GHFunc) func, info);
}