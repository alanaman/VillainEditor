#pragma once
#include "graphics/context.hpp"

namespace villain {

class ContextOpengl : public GraphicsContext
{
public:
 ContextOpengl() = default;
 ~ContextOpengl() = default;

 void initiate() const override;
 void resizeViewport(int width, int height) override;
 void clearBuffer() override;

};
}