#include "src/server/server.h"
#include "src/client/client.h"
#include "src/core/database/database.h"
#include <iostream>
#include <iomanip>


/*
void test_db() {
    CDBConnection db("localhost", "logger", "root", "dbpassword");

    QueryResult a = db.get_record("show tables");
    QueryResultList b = db.get_record_list("select * from Logger");


    std::cout << std::endl;
    for (auto it = a.begin(); it != a.end(); it++)
        std::cout << (*it) << " ";

    std::cout << std::endl;

    for (auto it = b.begin(); it != b.end(); it++) {
        for (auto col = (*it).begin(); col != (*it).end(); col++)
            std::cout << (*col) << " ";
        std::cout << std::endl;
    }
}
*/

/*
namespace mpl
{
#define make_ns_type(ns, tname) template <ns::tname val> struct tname { enum : ns::tname { value = val }; };
    make_ns_type(std, int8_t)   make_ns_type(std, uint8_t)   make_ns_type(std, int16_t)  make_ns_type(std, uint16_t)
    make_ns_type(std, int32_t)  make_ns_type(std, uint32_t)  make_ns_type(std, int64_t)  make_ns_type(std, uint64_t)

    template<class first, class second>
    struct pair {};

    struct nothing { nothing() = delete; enum { value = 0 }; };

    template<class... tail>
    struct map { };

    template<class first, class second, class... tail>
    struct map<mpl::pair<first, second>, tail...> : map<tail...> { };

    template <class... empty>
    struct at { using type = nothing; };

    template< class first, class second, class... tail, class key>
    struct at<mpl::map<mpl::pair<first, second>, tail...>, key>
    {
        using type = typename std::conditional< std::is_same<first, key>::value, // if pair_key == key
                second,                          // true: found, break recursion
                typename mpl::at<mpl::map<tail...>, key>::type // false: go to the next pair
        >::type;
    };

};

class A
{

};

#pragma pack(1)
*/


int main(int argc, char* argv[]) {
    /*
    std::vector<std::reference_wrapper<int>> h;

    int a =3;
    int b = 5;

    h.emplace_back(std::ref(a));
    h.emplace_back(std::ref(b));

    h[1] += 5;

    std::unique_ptr<int> qwe = std::make_unique<int>(5);
    std::unique_ptr<int> qwe2;
    qwe2 = std::move(qwe);

    struct S
    {
        char h;
        int a;
        float b;
        double c;
    };




    unsigned char c = 0xFF;
    S* y = (S*)malloc(sizeof(S) + 8);
    for(auto i = 0 ; i < sizeof(S) + 8; ++i)
        (*(((unsigned char*)y) + i)) = 0xff;

    y->a = 0;
    y->b = 0;
    y->c = 0;
    y->h = 0;

    // 0 1 2 3 4

    auto size = sizeof(S);

    typedef mpl::map<
            mpl::pair<mpl::int16_t<1>, float>,
            mpl::pair<mpl::int16_t<2>, double>,
            mpl::pair<mpl::int16_t<3>, A>> theMap;

    mpl::at<theMap, mpl::int16_t<1>>::type g;
    //auto h = typeid(g).name();
    */

    time_t t = time(NULL);
    tm* aTm = localtime(&t);
    std::cout
            << "[START] TIME: "
            << aTm->tm_year+1900 << "/" << std::setfill ('0') << std::setw (2)
            << aTm->tm_mon+1 << "/" << std::setfill ('0') << std::setw (2)
            << aTm->tm_mday << " " << std::setfill ('0') << std::setw (2)
            << aTm->tm_hour << ":" << std::setfill ('0') << std::setw (2)
            << aTm->tm_min << ":" << std::setfill ('0') << std::setw (2)
            << aTm->tm_sec << std::endl;

    CServer s;
    // CClient s;
    s.start();

    // test_db();
    return 0;
}