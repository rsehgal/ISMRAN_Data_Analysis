/*
**	Filename : Test_Update_Db_For_Deleted_Files.cpp
**	2021-11-10
**	username : rsehgal
*/
/*
** This needs to be run time to time by cron, to update Database for deleted files
*/

#include<iostream>
#include "Database.h"

int main(int argc, char *argv[]){

	ismran::Database d("127.0.0.1","ismran_db","ismran","ismran123");
	//ismran::Database d("127.0.0.1","barcq","barcq","barcq");
   	d.SetVerbose(true);
	d.Connect();
  	//d.InsertFileNameAndPath("/home/rsehgal/ISMRAN_dqm/sourceDir","test1.txt");
  	//d.InsertFileNameAndPath("/home/rsehgal/ISMRAN_dqm/sourceDir","test2.txt");
	//d.UpdateDbForFileNames_Offline("/home/rsehgal/DevShare");
	d.UpdateDbForFileNames_Offline(argv[1]);
	return 0;

}


