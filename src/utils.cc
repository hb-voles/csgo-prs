#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <limits>
#include <string>
#include <type_traits>
#include <vector>

#include "utils.h"

// http://cpp.indi.frih.net/blog/2014/09/how-to-read-an-entire-file-into-memory-in-cpp/
/* reading straight into a container:
If you are dealing with files it can be faster to count all the
characters first, then do one big allocation and one big whopper of a read:
    auto const start_pos = in.tellg();
    in.ignore(std::numeric_limits<std::streamsize>::max());
    auto const char_count = in.gcount();
    in.seekg(start_pos);
    auto s = std::string(char_count, char{});
    in.read(&s[0], s.size());
in.ignore() is a safe way to count the bytes in a file but means this method
requires reading the file twice, once to count bytes and once to read them in.
*/
template <typename Container = std::string, typename CharT = char,
          typename Traits = std::char_traits<char> >
Container read_stream_into_container(std::basic_istream<CharT, Traits> &in,
                                     typename Container::allocator_type alloc
                                     = {})
{
    static_assert(
        // Allow only strings...
        std::is_same<
            Container,
            std::basic_string<CharT, Traits,
                              typename Container::allocator_type> >::value
            ||
            // ... and vectors of the plain, signed, and
            // unsigned flavours of CharT.
            std::is_same<
                Container,
                std::vector<CharT, typename Container::allocator_type> >::value
            || std::is_same<
                   Container,
                   std::vector<std::make_unsigned<CharT>,
                               typename Container::allocator_type> >::value
            || std::is_same<
                   Container,
                   std::vector<std::make_signed<CharT>,
                               typename Container::allocator_type> >::value,
        "only strings and vectors of ((un)signed) CharT allowed");

    auto const start_pos = in.tellg();
    if (std::streamsize(-1) == start_pos)
        throw std::ios_base::failure{ "unable to open the file" };

    if (!in.ignore(std::numeric_limits<std::streamsize>::max()))
        throw std::ios_base::failure{ "file too big" };

    auto const char_count = in.gcount();

    if (!in.seekg(start_pos))
        throw std::ios_base::failure{ "error reading the file" };

    auto container = Container(std::move(alloc));
    container.resize(char_count);

    if (0 != container.size()) {
        if (!in.read(reinterpret_cast<CharT *>(&container[0]),
                     container.size()))
            throw std::ios_base::failure{ "error reading the file" };
    }

    return container;
}

std::string get_file_content(std::string file_name)
{
    std::ifstream fin(file_name, std::ios::binary);
    try {
        std::string data = read_stream_into_container(fin);
        fin.close();
        return data;
    }
    catch (std::ios_base::failure err) {
        fin.close();
        throw std::ios_base::failure {
            file_name + std::string(": ") + err.what()
        };
    }
}
