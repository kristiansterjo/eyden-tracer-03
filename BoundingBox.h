#pragma once

#include "types.h"
#include "ray.h"
using namespace std;

struct Ray;

namespace {
	inline Vec3f Min3f(const Vec3f a, const Vec3f b)
	{
		return Vec3f(MIN(a.val[0], b.val[0]), MIN(a.val[1], b.val[1]), MIN(a.val[2], b.val[2]));
	}

	inline Vec3f Max3f(const Vec3f a, const Vec3f b)
	{
		return Vec3f(MAX(a.val[0], b.val[0]), MAX(a.val[1], b.val[1]), MAX(a.val[2], b.val[2]));
	}
}

/**
 * @brief Bounding Box class
 */
class CBoundingBox
{
public:
	CBoundingBox(void) = default;
	~CBoundingBox(void)= default;
	
	/**
	 * @brief Resets the bounding box
	 * @details This function resets the member variables \b m_min and \b m_max
	 */
	void clear(void)
	{
		// --- PUT YOUR CODE HERE ---
	}
	
	/**
	 * @brief Extends the bounding box to contain point \b a
	 * @param a A point
	 */
	void extend(Vec3f a)
	{
		// --- PUT YOUR CODE HERE ---

        this->m_max[0] = max(a[0],this->m_max[0]);
		this->m_min[0] = min(a[0],this->m_min[0]);

        this->m_max[1] = max(a[1],this->m_max[1]);
		this->m_min[1] = min(a[1],this->m_min[1]);

        this->m_max[2] = max(a[2],this->m_max[2]);
		this->m_min[2] = min(a[2],this->m_min[2]);
        
	}
	
	/**
	 * @brief Extends the bounding box to contain bounding box \b box
	 * @param box The second bounding box
	 */
	void extend(const CBoundingBox& box)
	{
		// --- PUT YOUR CODE HERE ---
		this->extend(box.m_min);
		
        this->extend(box.m_max);
        
	}
	
	/**
	 * @brief Checks if the current bounding box overlaps with the argument bounding box \b box
	 * @param box The secind bounding box to be checked with
	 */
	bool overlaps(const CBoundingBox& box)
	{
		// --- PUT YOUR CODE HERE ---
        if(this->m_min[0] < box.m_max[0] && box.m_min[0] < this->m_max[0] &&
	 	   this->m_min[1] < box.m_max[1] && box.m_min[1] < this->m_max[1] && 
		   this->m_min[2] < box.m_max[2] && box.m_min[2] < this->m_max[2])
		{
			
			return true;
		}
		else
		{
			return false;
		}
	}
	
	/**
	 * @brief Clips the ray with the bounding box
	 * @param[in] ray The ray
	 * @param[in,out] t0 The distance from ray origin at which the ray enters the bounding box
	 * @param[in,out] t1 The distance from ray origin at which the ray leaves the bounding box
	 */
	void clip(const Ray& ray, float& t0, float& t1)
	{
		// --- PUT YOUR CODE HERE ---
        Vec3f r0, r1, tmp;
        
        float d1 = std::numeric_limits<float>::infinity() * (-1);
        float d2 = std::numeric_limits<float>::infinity();
        
        for(int i =0; i<3; i++) {
            if(ray.dir[i] != 0) {
				r0[i] = (this->m_min[i]-ray.org[i])/ray.dir[i];
                r1[i] = (this->m_max[i]-ray.org[i])/ray.dir[i];
				if( d2<0 || d1>d2) { 
                    t0 = std::numeric_limits<float>::infinity();
                    t1 = std::numeric_limits<float>::infinity();
                    return;
                }
				if(r0[i]>d1) {
                    d1 = r0[i];
                }
				if(r1[i]<d2) { 
                    d2 = r1[i];
                }
                if(r0[i]>r1[i]) {
                    tmp = r1;
                    r1 = r0;
                    r0 = tmp;
				} 
            }
            else{
                r0[i] = (this->m_min[i] - ray.org[i]) / ray.dir[i];
                r1[i] = (this->m_max[i] - ray.org[i]) / ray.dir[i];

				if(d2<0 || d1 > d2) { 
                    t0 = std::numeric_limits<float>::infinity();
                    t1 = std::numeric_limits<float>::infinity();
                    return;
                }
				if(r0[i] > d1) {
                    d1 = r0[i];
                }
				if(r1[i] < d2) { 
                    d2 = r1[i];
                }
                if(r0[i] > r1[i]) {
                    tmp = r1;
                    r1 = r0;
                    r0 = tmp;
				}  
            }
        }
        t0 = d1;
        t1 = d2;
	}
	
	
public:
	Vec3f m_min;	///< The minimal point defying the size of the bounding box
	Vec3f m_max;	///< The maximal point defying the size of the bounding box
};