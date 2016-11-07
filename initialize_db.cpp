#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <cstddef>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include <pthread.h>

using namespace std;


struct return_structure {
  string items[4];
  string topics[4];  
  int temp_row_count;
  int count_done;
};


int main(int argc, char* argv[])
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   const char* sql;
   string sql_string;  
   return_structure return_value;

   // Initializing the mutex locks
   pthread_mutex_init(&count_mutex, NULL);
   pthread_mutex_init(&callback_mutex, NULL);

   // The first set of functions below open, create, and insert
   // the initial items into our database. None of these operations
   // require us to use the callback function to get results.
   rc = sqlite3_open("locations.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }else{
      fprintf(stderr, "Opened database successfully\n");
   }

   sql = "CREATE TABLE LOCATIONS("  \ // PLAYER LOCATIONS STORED
         "GAME_NUMBER INT PRIMARY KEY NOT NULL," \
         "PLAYER1X INT NOT NULL," \
	 "PLAYER1Y INT NOT NULL," \
	 "PLAYER2X INT NOT NULL," \
	"PLAYER2Y INT NOT NULL," \
	"PLAYER3X INT NOT NULL," \
	"PLAYER3Y INT NOT NULL," \
	"PLAYER4X INT NOT NULL," \
	"PLAYER4Y INT NOT NULL);"; 
 
   rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Table created successfully\n");
   }

   sql_string = "INSERT INTO LOCATIONS VALUES (1, 1, 2, 2,3,3,4,4);";
   sql = sql_string.c_str();
   rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Records created successfully\n");
   }

   sql_string = "INSERT INTO INVENTORY VALUES (5,5,6,6,7,7,8,8,9);";
   sql = sql_string.c_str();
   rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Records created successfully\n");
   }


   sqlite3_close(db);

  
}
