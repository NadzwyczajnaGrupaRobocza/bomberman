#include "RendererIdGenerator.hpp"

#include <boost/uuid/uuid_generators.hpp>

namespace graphics
{
RendererId RendererIdGenerator::generate() const
{
    return boost::uuids::random_generator()();
}
}
