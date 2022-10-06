#pragma once
#include "context.hpp"

namespace villain {

class ContextOpengl : public GraphicsContext
{
public:
 ContextOpengl() = default;
 ~ContextOpengl() = default;

 void initiate() const override;
};
}