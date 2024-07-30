#ifndef HITTABLELIST_HPP
#define HITTABLELIST_HPP

#include "Entity/Hittable.hpp"

#include <memory>
#include <vector>

struct HittableList : public Hittable {
    std::vector<std::shared_ptr<Hittable>> m_objects;

    HittableList();
    HittableList(std::shared_ptr<Hittable> object);

    void Clear();
    void Add(std::shared_ptr<Hittable> object);
    bool Hit(const Ray& r, const Interval& ray_t, HitRecord& record) const override;
};

#endif