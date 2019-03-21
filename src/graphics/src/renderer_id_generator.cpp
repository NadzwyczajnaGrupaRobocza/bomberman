#include "renderer_id_generator.hpp"

#include <boost/uuid/uuid_generators.hpp>

namespace graphics
{
renderer_id renderer_id_generator::generate()
{
    return boost::uuids::random_generator()();
}
}
