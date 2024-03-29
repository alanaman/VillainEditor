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
  ERROR("Could not initialize GLAD");
  exit(1);
 }
}
void villain::ContextOpengl::resizeViewport(int width, int height)
{
 glViewport(0, 0, width, height);
}
}