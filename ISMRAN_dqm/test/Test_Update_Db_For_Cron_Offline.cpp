/*
**	Filename : Test_Update_Db_For_Cron_Offline.cpp
**	2021-11-11
**	username : rsehgal
*/
/*
** This needs to be run only when offline update needs to be done
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
	//d.UpdateDbForTargetFiles_Cron_Offline("/media/rsehgal/BACKUP/dqm_test");
	d.UpdateDbForTargetFiles_Cron_Offline(argv[1]);
	return 0;

}


