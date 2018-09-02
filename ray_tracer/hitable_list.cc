#include "ray_tracer/hitable_list.h"

namespace trace {

bool HitableList::Hit(const Ray& ray, double t_min, double t_max,
                      HitRecord* hit) const {
  bool hit_something = false;
  for (const auto& hitable : hitables_) {
    if (hitable->Hit(ray, t_min, t_max, hit)) {
      hit_something = true;
      t_max = hit->t;
    }
  }
  return hit_something;
}

}  // namespace trace