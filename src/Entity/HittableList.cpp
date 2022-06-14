#include "Entity/HittableList.hpp"

HittableList::HittableList() {}

HittableList::HittableList(const std::shared_ptr<Hittable>& object) {
    Add(object);
}

void HittableList::Clear() {
    m_objects.clear();
}

void HittableList::Add(const std::shared_ptr<Hittable>& object) {
    m_objects.push_back(object);
}

bool HittableList::Hit(const Ray& r, const double& t_min, const double& t_max, HitRecord& record) const {
    HitRecord temp_record;
    bool is_hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& object : m_objects) {
        if (object->Hit(r, t_min, closest_so_far, temp_record)) {
            is_hit_anything = true;
            closest_so_far = temp_record.m_t;
            record = temp_record;
        }
    }

    return is_hit_anything;
}