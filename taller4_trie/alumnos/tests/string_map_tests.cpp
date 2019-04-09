#include <gtest/gtest.h>
#include "string_map.h"

TEST(string_map_test, vacio) {
    string_map<int> vacio;

    EXPECT_TRUE(vacio.empty());
    EXPECT_EQ(vacio.count("hola"), 0);
}

TEST(string_map_test, asignar) {
    string_map<int> singleton;
    singleton["hola"] = 1;

    EXPECT_EQ(singleton["hola"], 1);
    EXPECT_EQ(singleton.size(), 1);
}

TEST(string_map_test, obtener) {
    string_map<int> sin_prefijos;
    string_map<int> con_prefijos;

    sin_prefijos["hola"] = 1;
    sin_prefijos["chau"] = 2;
    sin_prefijos["adios"] =  3;

    con_prefijos["c"] =  1;
    con_prefijos["casa"] =  2;
    con_prefijos["casona"] =  3;

    EXPECT_EQ(sin_prefijos["hola"], 1);
    EXPECT_EQ(sin_prefijos["chau"], 2);
    EXPECT_EQ(sin_prefijos["adios"], 3);

    EXPECT_EQ(con_prefijos["c"], 1);
    EXPECT_EQ(con_prefijos["casa"], 2);
    EXPECT_EQ(con_prefijos["casona"], 3);
}

TEST(string_map_test, redefinir) {
    string_map<int> con_prefijos;

    con_prefijos["c"] =  1;
    con_prefijos["casa"] =  2;
    con_prefijos["casona"] =  3;

    con_prefijos["c"] =  2;
    EXPECT_EQ(con_prefijos["c"], 2);
    con_prefijos["c"] =  3;
    EXPECT_EQ(con_prefijos["c"], 3);
}

TEST(string_map_test, count) {
    string_map<int> vacio;
    string_map<int> sin_prefijos;
    string_map<int> con_prefijos;

    sin_prefijos["hola"] = 1;
    sin_prefijos["chau"] = 2;
    sin_prefijos["adios"] =  3;

    con_prefijos["c"] =  1;
    con_prefijos["casa"] =  2;
    con_prefijos["casona"] =  3;

	EXPECT_FALSE(vacio.count("a") == 1);
	EXPECT_FALSE(vacio.count("aaaa") == 1);
	EXPECT_FALSE(vacio.count("adios") == 1);

	EXPECT_TRUE(sin_prefijos.count("hola") == 1);
	EXPECT_TRUE(sin_prefijos.count("chau") == 1);
	EXPECT_TRUE(sin_prefijos.count("adios") == 1);

	EXPECT_FALSE(sin_prefijos.count("h") == 1);
	EXPECT_FALSE(sin_prefijos.count("ho") == 1);
	EXPECT_FALSE(sin_prefijos.count("hol") == 1);

	EXPECT_TRUE(con_prefijos.count("c") == 1);
	EXPECT_TRUE(con_prefijos.count("casa") == 1);
	EXPECT_TRUE(con_prefijos.count("casona") == 1);
	EXPECT_FALSE(con_prefijos.count("ca") == 1);
	EXPECT_FALSE(con_prefijos.count("cas") == 1);
	EXPECT_FALSE(con_prefijos.count("caso") == 1);
}

TEST(string_map_test, copiar) {
    string_map<int> sin_prefijos;
    string_map<int> con_prefijos;

    sin_prefijos["hola"] = 1;
    sin_prefijos["chau"] = 2;
    sin_prefijos["adios"] =  3;

    con_prefijos["c"] =  1;
    con_prefijos["casa"] =  2;
    con_prefijos["casona"] =  3;

    string_map<int> copia(sin_prefijos);

	EXPECT_TRUE(copia.count("hola") == 1);
	EXPECT_TRUE(copia.count("chau") == 1);
	EXPECT_TRUE(copia.count("adios") == 1);

	EXPECT_FALSE(copia.count("h") == 1);
	EXPECT_FALSE(copia.count("ho") == 1);
	EXPECT_FALSE(copia.count("hol") == 1);

	EXPECT_EQ(sin_prefijos["hola"], copia["hola"]);
	EXPECT_EQ(sin_prefijos["chau"], copia["chau"]);
	EXPECT_EQ(sin_prefijos["adios"], copia["adios"]);

	string_map<int> copia2(con_prefijos);

	EXPECT_TRUE(copia2.count("c") == 1);
	EXPECT_TRUE(copia2.count("casa") == 1);
	EXPECT_TRUE(copia2.count("casona") == 1);
	EXPECT_FALSE(copia2.count("ca") == 1);
	EXPECT_FALSE(copia2.count("cas") == 1);
	EXPECT_FALSE(copia2.count("caso") == 1);

	EXPECT_EQ(copia2["c"], 1);
	EXPECT_EQ(copia2["casa"], 2);
	EXPECT_EQ(copia2["casona"], 3);
}

TEST(string_map_test, no_aliasing) {
    string_map<int> singleton;
    singleton["hola"] = 1;

	string_map<int> copia(singleton);
	copia["hare"] =  2;
	ASSERT_FALSE(singleton.count("hare") == 1);
}


TEST(string_map_test, TrieDeTries) {
    string_map<int> vacio;
    string_map<int> singleton;
    string_map<int> sin_prefijos;
    string_map<int> con_prefijos;
    string_map<string_map<int>> dicc_dicc;

    singleton["hola"] = 1;

    sin_prefijos["hola"] = 1;
    sin_prefijos["chau"] = 2;
    sin_prefijos["adios"] =  3;

    con_prefijos["c"] =  1;
    con_prefijos["casa"] =  2;
    con_prefijos["casona"] =  3;

    dicc_dicc["vacio"] =  vacio;
    dicc_dicc["singleton"] =  singleton;
    dicc_dicc["sin_prefijos"] =  sin_prefijos;
    dicc_dicc["con_prefijos"] =  con_prefijos;

	EXPECT_FALSE(dicc_dicc["vacio"].count("hola") == 1);

	EXPECT_EQ(dicc_dicc["singleton"]["hola"], 1);

	EXPECT_EQ(dicc_dicc["sin_prefijos"]["hola"], 1);
	EXPECT_EQ(dicc_dicc["sin_prefijos"]["chau"], 2);
	EXPECT_EQ(dicc_dicc["sin_prefijos"]["adios"], 3);

	EXPECT_EQ(dicc_dicc["con_prefijos"]["c"], 1);
	EXPECT_EQ(dicc_dicc["con_prefijos"]["casa"], 2);
	EXPECT_EQ(dicc_dicc["con_prefijos"]["casona"], 3);

}

TEST(string_map_test, eraseUnicaClave) {
    string_map<int> singleton;
    singleton["hola"] = 1;

    EXPECT_TRUE(singleton.count("hola") == 1);

    singleton.erase("hola");

    EXPECT_FALSE(singleton.count("hola") == 1);
}


TEST(string_map_test, erase) {
    string_map<int> sin_prefijos;
    string_map<int> con_prefijos;

    sin_prefijos["hola"] = 1;
    sin_prefijos["chau"] = 2;
    sin_prefijos["adios"] =  3;

    con_prefijos["c"] =  1;
    con_prefijos["casa"] =  2;
    con_prefijos["casona"] =  3;

    con_prefijos.erase("c");
    EXPECT_FALSE(con_prefijos.count("c") == 1);

    EXPECT_TRUE(con_prefijos.count("casa") == 1);
    EXPECT_TRUE(con_prefijos.count("casona") == 1);

    con_prefijos.erase("casona");
    EXPECT_FALSE(con_prefijos.count("casona") == 1);

    EXPECT_TRUE(con_prefijos.count("casa") == 1);

    con_prefijos.erase("casa");
    EXPECT_FALSE(con_prefijos.count("casa") == 1);

    sin_prefijos.erase("hola");
    EXPECT_FALSE(sin_prefijos.count("hola") == 1);

    sin_prefijos.erase("chau");
    EXPECT_FALSE(sin_prefijos.count("chau") == 1);

    sin_prefijos.erase("adios");
    EXPECT_FALSE(sin_prefijos.count("adios") == 1);
}


int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
