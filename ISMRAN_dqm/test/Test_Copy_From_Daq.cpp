/*
 * TestMysql.cpp
 *
 *  Created on: Jun 22, 2017
 *      Author: rsehgal
 */

#include "Database.h"

int main(){

	//ismran::Database d; //Default constructor hardcode in the class
	ismran::Database d("127.0.0.1","ismran_db","ismran","ismran123");
	//ismran::Database d("10.10.1.192","ismran_db","ismran","ismran123");
	//ismran::Database d("127.0.0.1","barcq","barcq","barcq");
   	d.SetVerbose(true);
	d.Connect();
  	d.InsertFileNameAndPath("/home/rsehgal/ISMRAN_dqm/sourceDir","test1_10Nov2021.txt");
  	d.InsertFileNameAndPath("/home/rsehgal/ISMRAN_dqm/sourceDir","test2_11Nov2021.txt");
  	d.InsertFileNameAndPath("/home/rsehgal/ISMRAN_dqm/sourceDir","test3_10Nov2021.txt");
  	//d.InsertFileNameAndPath("/home/rsehgal/ISMRAN_dqm/sourceDir","test2.txt");
	return 0;

}


