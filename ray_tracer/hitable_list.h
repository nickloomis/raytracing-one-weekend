#ifndef RAY_TRACER_HITABLE_LIST_H_
#define RAY_TRACER_HITABLE_LIST_H_

#include <list>
#include <memory>

#include "ray_tracer/hitable.h"

namespace trace {

class HitableList : public Hitable {
 public:
  HitableList() {}

  bool Hit(const Ray& ray, double t_min, double t_max, HitRecord* hit) const;

  void Add(std::unique_ptr<Hitable> hitable) {
    hitables_.push_back(std::move(hitable));  // TODO(nloomis): push_back for lists?
  }

 private:
  std::list<std::unique_ptr<Hitable>> hitables_;
};

}  // namespace trace

#endif  // RAY_TRACER_HITABLE_LIST_H_