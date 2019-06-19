#include <tuple>
#include <vector>

#include "ExplosionRange.hpp"
#include "Map.hpp"
#include "WallPositionsGenerator.hpp"
#include "math/Size2u.hpp"

#include "glm/glm.hpp"
#include "graphics/renderer_id.hpp"
#include "graphics/renderer_pool.hpp"
#include "physics/PhysicsEngine.hpp"

class SimpleMap : public Map
{
public:
    SimpleMap(physics::PhysicsEngine& pEngine,
              const WallPositionsGenerator& wall_positions_generator,
              graphics::renderer_pool& rEngine, math::Size2u map_size);
    ~SimpleMap() override;

    ExplosionRange get_explosion_range(std::pair<int, int> start_point,
                                       int range) const;

private:
    physics::PhysicsEngine& physics_engine;
    std::vector<physics::PhysicsEngine> walls;
    graphics::renderer_pool& graphics_engine;
    const math::Size2u map_size;
    std::vector<physics::PhysicsId> physics_ids;
    std::vector<graphics::renderer_id> render_ids;

    template <typename Distance>
    Distance get_range_in_decreasing_direction(const int start_point,
                                               const int range) const
    {
        if (can_move_backward(start_point, range))
        {
            constexpr auto step = 1;
            return get_range_in_decreasing_direction<Distance>(
                       start_point - step, range - step) +
                   Distance{step};
        }
        else
        {
            constexpr auto zero_range = Distance{0};
            return zero_range;
        }
    }

    static bool can_move_backward(const int start_point, const int range);

    template <typename Distance>
    Distance get_range_in_increasing_direction(int start_point, int range,
                                               int limit) const
    {
        if (can_move_forward(start_point, range, limit))
        {
            constexpr auto step = 1;
            return get_range_in_increasing_direction<Distance>(
                       start_point + step, range - step, limit) +
                   Distance{step};
        }
        else
        {
            constexpr auto zero_range = Distance{0};
            return zero_range;
        }
    }

    static bool can_move_forward(const int start_point, const int range,
                                 const int map_size);
};
