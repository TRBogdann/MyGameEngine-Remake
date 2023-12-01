#include "../window/window.h"
#include "../../settings/settings.h"

class Program
{
    public:
    Program();
    ~Program();
    void useWindow(Window &window);
    void start();
    void terminate();
    bool CheckForError();
    void setCursorMode(Cursor_Mode mode);
    
    
    private:

    Window *_window;
    std::string errorMessage;
    bool terminated=0;
   
};
