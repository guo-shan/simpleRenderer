#ifndef BVH_H
#define BVH_H

#include "../Math/Vec.h"
#include "../Core/Hittable.h"
#include "../Core/HittableList.h"
#include "AABB.h"

#include <algorithm>

inline bool box_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b, int axis) {
	AABB box_a, box_b;

	if (!a->bounding_box(0, 0, box_a) || !b->bounding_box(0, 0, box_b)) {
		std::cerr << "No bounding box in BVH_Node constructor." << std::endl;
	}
	return box_a.min()[axis] < box_b.min()[axis];
}

bool box_x_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) {
	return box_compare(a, b, 0);
}

bool box_y_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) {
	return box_compare(a, b, 1);
}

bool box_z_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) {
	return box_compare(a, b, 2);
}

class BVH_Node : public Hittable {
public:
	BVH_Node() {}
	BVH_Node(const Hittable_List& list, float time0, float time1)
		: BVH_Node(list.objects, 0, list.objects.size(), time0, time1) {}
	//�ڵ�ݹ鹹�죬�ȵݹ黮�ֽڵ㣬�ٵݹ鷵�ذ�Χ��
	BVH_Node(const std::vector<std::shared_ptr<Hittable>>& src_objects,
		unsigned int start, unsigned int end, float time0, float time1) {
		// ȫ�ֶ���list
		auto objects = src_objects;

		// �����޷�ȷ����ȡ���������
		int axis = random_int(0, 2);
		auto comparator = (axis == 0) ? box_x_compare : (axis == 1) ? box_y_compare : box_z_compare;

		unsigned int object_span = end - start;

		// list�ڽ�һ������ʱ������������ָ���������
		if (object_span == 1) {
			left = right = objects[start];
		}
		// list�������������壬���������Ữ��
		else if (object_span == 2) {
			if (comparator(objects[start], objects[start + 1])) {
				left = objects[start];
				right = objects[start + 1];
			}
			else {
				left = objects[start + 1];
				right = objects[start];
			}
		}
		// �����廮�֣���������������ȡ��λ������
		else {
			std::sort(objects.begin() + start, objects.begin() + end, comparator);

			auto mid = start + object_span / 2;
			left = std::make_shared<BVH_Node>(objects, start, mid, time0, time1);
			right = std::make_shared<BVH_Node>(objects, mid, end, time0, time1);
		}

		AABB box_left, box_right;

		// �ݹ��ȡ���������Ӻ�����������
		if (!left->bounding_box(time0, time1, box_left) || !right->bounding_box(time0, time1, box_right)) {
			std::cerr << "No bounding box in BVH_Node constructor." << std::endl; // ��������ƽ��
		}
		// ������Ӽ���Ϊ�������ӽ���
		box = surrounding_box(box_left, box_right);
	}

	virtual bool hit(const Ray& r, float t_min, float t_max, Object& rec) const override;

	virtual bool bounding_box(float time0, float time1, AABB& output_box) const override;

public:
	std::shared_ptr<Hittable> left;
	std::shared_ptr<Hittable> right;
	AABB box;
};

bool BVH_Node::hit(const Ray& r, float t_min, float t_max, Object& rec) const {
	if (!box.hit(r, t_min, t_max)) return false;
	bool hit_left = left->hit(r, t_min, t_max, rec);
	bool hit_right = right->hit(r, t_min, hit_left ? rec.t : t_max, rec);
	return hit_left || hit_right;
}

bool BVH_Node::bounding_box(float time0, float time1, AABB& output_box) const {
	output_box = box;
	return true;
}

#endif