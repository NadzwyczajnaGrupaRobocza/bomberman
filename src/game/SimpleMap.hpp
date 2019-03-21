#include <tuple>
#include <vector>

#include "ExplosionRange.hpp"
#include "Map.hpp"
#include "WallPositionsGenerator.hpp"

#include "glm/glm.hpp"
#include "graphics/renderer_id.hpp"
#include "graphics/renderer_pool.hpp"
#include "physics/PhysicsEngine.hpp"

class SimpleMap : public Map
{
public:
    SimpleMap(physics::PhysicsEngine& pEngine,
              const WallPositionsGenerator& wall_positions_generator,
              graphics::renderer_pool& rEngine);
    ~SimpleMap() override;

    ExplosionRange get_explosion_range(std::pair<int, int> start_point,
                                       int range) const;

private:
    physics::PhysicsEngine& physics_engine;
    std::vector<physics::PhysicsEngine> walls;
    graphics::renderer_pool& graphics_engine;
    const int map_size{10};
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
    Distance get_range_in_increasing_direction(const int start_point,
                                               const int range) const
    {
        if (can_move_forward(start_point, range, map_size))
        {
            constexpr auto step = 1;
            return get_range_in_increasing_direction<Distance>(
                       start_point + step, range - step) +
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
