#include <iostream>
using namespace std;

#define OTL_ODBC
//#define ODBCVER 0x0250
#include <otlv4.h>

otl_connect db;

int main()
{
    otl_connect::otl_initialize(); // initialize ODBC environment
    try
    {
        db.rlogon("DRIVER=SQLite3 ODBC Driver;Database=authentication.db;LongNames=0;Timeout=1000;NoTXN=0;SyncPragma=NORMAL;StepAPI=0;"); 

        otl_cursor::direct_exec
            (
            db,
            "drop table test_tab",
            otl_exception::disabled // disable OTL exceptions
            ); // drop table

        otl_cursor::direct_exec
            (
            db,
            "create table test_tab(f1 int, f2 varchar(30))"
            );  // create table
    }
    catch(otl_exception& p)
    {
        cerr << p.msg << endl;
        cerr << p.stm_text << endl;
        cerr << p.sqlstate << endl;
        cerr << p.var_info << endl;
    }

    db.logoff();

    return 0;
}