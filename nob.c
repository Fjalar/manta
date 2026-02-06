// This is your build script. You only need to "bootstrap" it once with `cc -o nob nob.c`
// (you can call the executable whatever actually) or `cl nob.c` on MSVC. After that every
// time you run the `nob` executable if it detects that you modifed nob.c it will rebuild
// itself automatically thanks to NOB_GO_REBUILD_URSELF (see below)

// nob.h is an stb-style library https://github.com/nothings/stb/blob/master/docs/stb_howto.txt
// What that means is that it's a single file that acts both like .c and .h files, but by default
// when you include it, it acts only as .h. To make it include implementations of the functions
// you must define NOB_IMPLEMENTATION macro. This is done to give you full control over where
// the implementations go.
#define NOB_IMPLEMENTATION
#include "nob.h"

// Some folder paths that we use throughout the build process.
#define BUILD_FOLDER "build/"
#define SRC_FOLDER   "src/"

int main(int argc, char **argv)
{
    NOB_GO_REBUILD_URSELF(argc, argv);

    if (!nob_mkdir_if_not_exists(BUILD_FOLDER)) return 1;

    Nob_Cmd cmd = {0};

    // specify compiler
    nob_cmd_append(&cmd, "gcc");

    // optimization
    nob_cmd_append(&cmd, "-s");

    nob_cmd_append(&cmd, "-D_GLFW_WAYLAND");

    nob_cmd_append(&cmd, SRC_FOLDER "main.c");
    nob_cmd_append(&cmd, SRC_FOLDER "gl.c");

    // statically link glfw
    nob_cmd_append(&cmd, SRC_FOLDER "libglfw3.a");

    // dynamically link stuff required by glfw
    nob_cmd_append(&cmd, "-lpthread");
    nob_cmd_append(&cmd, "-ldl");
    nob_cmd_append(&cmd, "-lm");

    nob_cmd_append(&cmd, "-o");
    nob_cmd_append(&cmd, BUILD_FOLDER "main");

    if (!nob_cmd_run(&cmd)) return 1;

    return 0;
}
