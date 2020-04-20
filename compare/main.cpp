#include <iostream>
#include <fstream>

int main()
{
    std::ifstream c("c.txt");
    std::ifstream p("p.txt");

    auto i = 0;

    while( !c.eof() )
    {
        std::string cs;
        std::string ps;

        std::getline(c,cs);
        std::getline(p,ps);

        try
        {
            auto cv = std::stoi( cs );
            auto pv = std::stoi( ps );
            auto v = cv - pv;
            if(v!=0)
            std::cout << i << "|" << cs << "|" << ps << "|" << v << std::endl;
        }
        catch(...)
        {
            if( c.eof() ) return 0;
            return 1;
        }
        i++;
    }

    return 0;
}
