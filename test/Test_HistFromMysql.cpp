#include <iostream>
#include <mysql/mysql.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TApplication.h>
#include <TFile.h>
#include <TGraph.h>
#include <vector>
int main(int argc, char **argv) {
    TApplication app("app", &argc, argv); // Initialize ROOT application

    // Connect to the MySQL database
    MYSQL *conn;
    conn = mysql_init(nullptr);
    if (conn == nullptr) {
        std::cerr << "MySQL initialization failed" << std::endl;
        return 1;
    }

    if (mysql_real_connect(conn, "127.0.0.1", "ismran", "ismran123", "ismran_db", 0, nullptr, 0) == nullptr) {
        std::cerr << "Connection to MySQL database failed: " << mysql_error(conn) << std::endl;
        return 1;
    }

    // Query the database to retrieve data
    //if (mysql_query(conn, "SELECT passingmuons FROM ismran_files where filename like '%06Jun2022%' and passingmuons<>0")) {
    if (mysql_query(conn, "SELECT passingmuons FROM ismran_files where passingmuons<>0")) {
        std::cerr << "MySQL query error: " << mysql_error(conn) << std::endl;
        return 1;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == nullptr) {
        std::cerr << "MySQL result error: " << mysql_error(conn) << std::endl;
        return 1;
    }

    // Create a histogram to store the data
    TH1F *histogram = new TH1F("histogram", "Histogram", 1000, 90000, 95000);

    MYSQL_ROW row;
    std::vector<float> xvec;
    std::vector<float> yvec;
    unsigned short counter=0;
    while ((row = mysql_fetch_row(result))) {
	    counter++;
        double value = std::stod(row[0]);
	std::cout << value << std::endl;
	xvec.push_back(counter);
	yvec.push_back(value);
        histogram->Fill(value);
    }

   TGraph *gr = new TGraph(xvec.size(),&xvec[0],&yvec[0]);
    // Close the database connection
    mysql_free_result(result);
    mysql_close(conn);

    // Create a canvas and draw the histogram
    TCanvas *canvas = new TCanvas("canvas", "Histogram Canvas", 800, 600);
    histogram->Draw();
    gr->GetYaxis()->SetRangeUser(0,100000);
    gr->SetMarkerStyle(8);
    gr->Draw();

    TFile *fp=new TFile("outfromDB.root","RECREATE");
    fp->cd();
    histogram->Write();
    gr->Write();
    fp->Close();
    app.Run(); // Start the ROOT event loop

    return 0;
}

