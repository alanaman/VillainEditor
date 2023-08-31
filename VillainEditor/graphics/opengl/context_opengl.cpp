#include "context_opengl.hpp"
#include "glad/glad.h"

#include "context_opengl.hpp"
#include "logging.hpp"

namespace villain {

void ContextOpengl::initiate() const
{
 int status = gladLoadGL();
 if (!status)
 {
  VLLN_ERR("Could not initialize GLAD");
  exit(1);
 }
}
void ContextOpengl::resizeViewport(int width, int height)
{
 glViewport(0, 0, width, height);
}
void ContextOpengl::clearBuffer()
{
 glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
}