#include <cstdlib>
#include <cassert>
#include <string>
#include <array>
#include <vector>
#include <fstream>
#include <iostream>
#include <boost/endian/conversion.hpp>
#include <libpq-fe.h>

// connect URL, formatted as "postgresql://[user[:password]@][netloc][:port][/dbname]"
const std::string conninfo = "postgresql://postgres:password@127.0.0.1:5432/test";


int main(int argc, char* argv[]) {

	// Initialize connection
	PGconn* conn = PQconnectdb(conninfo.c_str());

	// Whether connected
	if (PQstatus(conn) != CONNECTION_OK) {
		std::cerr << "Connection to database failed: " << PQerrorMessage(conn) << std::endl;

		PQfinish(conn); 
		return EXIT_FAILURE;
	}

	// Result pointer
	PGresult* res = NULL;

	// Create a table
	res = PQexec(conn, "drop table if exists tbl_test_pq;"
		"create table tbl_test_pq (id serial primary key, intCol integer not null, floatCol numeric, boolCol boolean, strCol varchar(64), doubleCol numeric, byteCol bytea)");
	if (PQresultStatus(res) != PGRES_COMMAND_OK) {
		std::cerr << PQerrorMessage(conn) << std::endl;

		PQclear(res); PQfinish(conn); return EXIT_FAILURE;
	}
	PQclear(res);

    // whether native endian is different from network
    bool isContinuousByteOrder = (1 == boost::endian::native_to_big(1));
    assert(!isContinuousByteOrder); // if endian is continuous the work is much simpler

	// insert a row
	const std::string sql = "insert into tbl_test_pq values(default, $1::int, $2::real, $3::boolean, $4::varchar(32), $5::double precision, $6::bytea)"; // type hints may not be strictly the same; compatible is OK

	// values 
	int int_value = - 256; // integer value
	auto int_value_network = boost::endian::native_to_big(int_value); // endian convertion; use big endian as network/server does

	float float_value = 3.14159f; // float value
	auto float_value_as_int = reinterpret_cast<int*>(&float_value); // no suitable endian convertor for float; regard it as an integer for the same bytes
	auto float_value_network = boost::endian::native_to_big(*float_value_as_int); // endian convertion

	bool bool_value = true; // boolean values; one byte and thus no need to worry about endian

	std::string str_value = "PG needs cautions for byte orders."; // string value

	double double_value = 2.718281828; // double value 
	auto double_value_as_int = reinterpret_cast<int*>(&double_value);
	const size_t double_as_int_array_size = sizeof(double) / sizeof(int); // double values takes multiple byte-numbers as integer; regard it as integer array
	int double_value_network[double_as_int_array_size];
	for (size_t i = 0; i < double_as_int_array_size; ++i) { // assign reversely
		double_value_network[double_as_int_array_size - 1 - i] = boost::endian::native_to_big(*double_value_as_int); // endian convertion
		++double_value_as_int; // move to next 4-bytes
	}

    std::ifstream binaryFile( "file.ext", std::ios::binary ); // read a binary file
    std::vector<char> binary_value((std::istreambuf_iterator<char>(binaryFile)), (std::istreambuf_iterator<char>())); // binary value; no necessary to consider about endian

	// all cast to bytes; string & binary values needs not to
	typedef const char* _byte_ptr;
	std::vector<_byte_ptr> values;
	values.push_back(reinterpret_cast<_byte_ptr>(&int_value_network));
	values.push_back(reinterpret_cast<_byte_ptr>(&float_value_network));
	values.push_back(reinterpret_cast<_byte_ptr>(&bool_value));
	values.push_back(str_value.c_str());
	values.push_back(reinterpret_cast<_byte_ptr>(double_value_network));
    values.push_back(binary_value.data());

	// lengths
	std::vector<int> lengths;
	auto _byte_length = sizeof(*values.front());

	lengths.push_back(sizeof(int_value_network) / _byte_length);
	lengths.push_back(sizeof(float_value_network) / _byte_length);
	lengths.push_back(sizeof(bool_value) / _byte_length);
	lengths.push_back(0); // length of string values can be ignored
	lengths.push_back(sizeof(double_value_network) / _byte_length);
    lengths.push_back(sizeof(binary_value.front()) * binary_value.size() / _byte_length);

	// formats
	std::vector<int> formats;
	formats.push_back(1);
	formats.push_back(1);
	formats.push_back(1);
	formats.push_back(0); // 0 for string values
	formats.push_back(1);
    formats.push_back(1);

	// execute
	res = PQexecParams(conn, sql.c_str(), (int) values.size(), NULL, values.data(), lengths.data(), formats.data(), 0);
	if (PQresultStatus(res) != PGRES_COMMAND_OK) {
		std::cerr << PQerrorMessage(conn) << std::endl;

		PQclear(res); PQfinish(conn); return EXIT_FAILURE;
	}
	PQclear(res);

    // commit
	PQexec(conn, "COMMIT");

	/* close the connection to the database and cleanup */
	PQfinish(conn);

	return EXIT_SUCCESS;
}