#include "cseries/cseries.h"
#include "shell/shell.h"

int main(int argc, const char *argv[])
{
    #warning TODO: reference other platforms
    // fuck_code_in_the_eye();
    // rasterizer_preinitialize__fill_you_up_with_the_devils_cock();
    // physical_memory_allocate();

    if (shell_initialize())
    {
        main_loop();
        shell_dispose();
    }

    return 0;
}
