#pragma once

namespace villain {

class GraphicsContext
{
public:
 GraphicsContext() = default;
 virtual ~GraphicsContext() = default;
 virtual void initiate() const = 0;

 virtual void resizeViewport(int width, int height) = 0;
};
}