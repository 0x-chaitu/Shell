#ifndef INPUT_HANDLER
#define INPUT_HANDLER
// int readLine();
void interactiveLoop(int status, int argc, char **argv);
struct Args {   // Structure declaration
  int argc;           // 
  char **argv;       // 
};
#endif