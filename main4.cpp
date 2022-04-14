
#include <list>
#define TESTED_NAMESPACE std
#define _pair TESTED_NAMESPACE::pair
#include "map.hpp"
#include <map>

template <typename T>
std::string     printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
        o << "key: " << iterator->first << " | value: " << iterator->second;
        if (nl)
                o << std::endl;
        return ("");
}

template <typename T_MAP>
void    printSize(T_MAP const &mp, bool print_content = 1)
{
        std::cout << "size: " << mp.size() << std::endl;
        std::cout << "max_size: " << mp.max_size() << std::endl;
        if (print_content)
        {
                typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
                std::cout << std::endl << "Content is:" << std::endl;
                for (; it != ite; ++it)
				{
					std::cout << "- " << printPair(it, false) << std::endl;
					//break;
				}
        }
        std::cout << "###############################################" << std::endl;
}

template <typename T1, typename T2>
void    printReverse(TESTED_NAMESPACE::map<T1, T2> &mp)
{
        typename TESTED_NAMESPACE::map<T1, T2>::iterator it = mp.end(), ite = mp.begin();

        std::cout << "printReverse:" << std::endl;
        while (it != ite) {
                it--;
                std::cout << "-> " << printPair(it, false) << std::endl;
        }
        std::cout << "_______________________________________________" << std::endl;
}
#define T1 int
#define T2 int
typedef _pair<const T1, T2> T3;
int             main(void)
{
        std::list<T3> lst;
        unsigned int lst_size = 7;
        for (unsigned int i = 0; i < lst_size; ++i)
                lst.push_back(T3(lst_size - i, i));
//
        TESTED_NAMESPACE::map<T1, T2> mp(lst.begin(), lst.end());
        TESTED_NAMESPACE::map<T1, T2>::iterator it = mp.begin(), ite = mp.end();
std::cout << "a " << std::endl;
        TESTED_NAMESPACE::map<T1, T2> mp_range(it, --(--ite));
        for (int i = 0; it != ite; ++it)
                it->second = ++i * 5;
//
        it = mp.begin(); ite = --(--mp.end());
        TESTED_NAMESPACE::map<T1, T2> mp_copy(mp);
        for (int i = 0; it != ite; ++it)
                it->second = ++i * 7;

        std::cout << "\t-- PART ONE --" << std::endl;
        printSize(mp);
        printSize(mp_range);
        printSize(mp_copy);

        //mp = mp_copy;
        //mp_copy = mp_range;
        //mp_range.clear();
//
        //std::cout << "\t-- PART TWO --" << std::endl;
        //printSize(mp);
        //printSize(mp_range);
        //printSize(mp_copy);
        //return (0);
}