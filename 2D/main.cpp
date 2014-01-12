#include <iostream>
#include <exception>
#include <App.hpp>

#include <GOLSortedList.hxx>
#include <stdlib.h>

int main()
{
    App* theApp;

    try {
        theApp = new App();
        theApp->go();
    } catch( const std::exception& e )
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    delete theApp;

    return 0;
}
