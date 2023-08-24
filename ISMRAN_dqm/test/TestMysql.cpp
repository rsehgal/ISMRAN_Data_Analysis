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
   	d.SetVerbose(true);
	d.Connect();
	std::string query = "select * from ismran_files";
	d.Select(query);
     	std::string insertQuery = "insert into ismran_files values ('/home/rsehgal/test2','test2.root',0,'8908jkjjlkjl',1)";
	d.Insert(insertQuery);
	d.Select(query);

  	d.InsertFileNameAndPath("/home/rsehgal/test3","test3.root");
	d.Select(query);
    	/*
	int numOfRecords = d.GetNumOfRows("scatteringdata");
	std::cout<<"Num of Records : " << numOfRecords << std::endl;

	int numOfColumns = d.GetNumOfColumns("scatteringdata");
	std::cout<< "Num of Columns : " << numOfColumns << std::endl;

	double energy = 2.6;
	std::string material = "Fe";
	double thickness = 20.5;
	double fwhm = 30.6;
	query = "insert into scatteringdata values("+std::to_string(energy)+",'"+material+"',"+std::to_string(thickness)+","+std::to_string(fwhm)+")";
	std::cout << "Final Query : " << query << std::endl;

	d.Insert(query);

	//d.Delete("scatteringdata");*/
	return 0;

}


