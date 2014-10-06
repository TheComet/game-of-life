#include <iostream>
#include <exception>
#include <app2d/App.hpp>

int main()
{
    App* theApp;

    try {
        theApp = new App();
        theApp->OnInit();
    } catch( const std::exception& e )
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    delete theApp;

    return 0;
}
