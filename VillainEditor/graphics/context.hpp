#pragma once

namespace villain {

class GraphicsContext
{
public:
 GraphicsContext() = default;
 virtual ~GraphicsContext() = default;
 virtual void initiate() const = 0;
};
}