#include "App/App.h"
#include "Math/Vector.h"
#include <stddef.h>

int main(void) {

  struct App app;

  init_app(&app);

  app_run(&app);

  app_destroy(&app);
}
