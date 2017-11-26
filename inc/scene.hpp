#ifndef HW4_SCENE_HPP
#define HW4_SCENE_HPP

#include <memory>
#include <vector>

#include "bvh.hpp"
#include "object.hpp"

namespace hw4 {
    class Scene {
        std::vector<std::unique_ptr<Object>> m_objects;
        BVH<Object> m_bvh;
    public:
        Scene() {}

        const std::vector<std::unique_ptr<Object>>& objects() const { return this->m_objects; }
        std::vector<std::unique_ptr<Object>>& objects() { return this->m_objects; }

        const BVH<Object>& bvh() const { return this->m_bvh; }
        Scene& regen_bvh() {
            std::vector<Object*> objects;

            for (const auto& o : this->m_objects) {
                objects.push_back(o.get());
            }

            this->m_bvh = BVH<Object>::construct(
                objects,
                [](const auto& o) -> const auto& { return o.aabb(); }
            );

            return *this;
        }
    };
}

#endif