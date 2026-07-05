#include <iostream>
#include <math.h>
#include "color.h"
#include "vec3.h"
#include "ray.h"

// check if ray hits the sphere with center , solve for t 
double hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = center - r.origin();
    auto a = dot(r.direction(), r.direction());
    auto h = dot(r.direction(), oc);
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = h*h - a*c;

    if (discriminant < 0) {
        return -1.0;
    } else {
        return (h - std::sqrt(discriminant) ) / a;
    }
}

// we use and y not x bcoz x is changing iteratively  inside y and hence we find a pattern of blend when changed to x which repeats itself
color ray_color(const ray& r){
    auto t = hit_sphere(point3(0,0,-1), 0.5, r);
    if (t > 0.0) {
        vec3 N = unit_vector(r.at(t) - vec3(0,0,-1));
        return 0.5*color(N.x()+1, N.y()+1, N.z()+1);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0); // interpolation used for blending: blendedValue=(1−a)⋅startValue+a⋅endValue,
}

int main(){
    auto aepect_ratio = 16.0/9.0;
    int img_width = 400;
    int img_height = int(img_width/aepect_ratio);
    img_height = (img_height<1)? 1: img_height;

    int focal_length = 1.0; // distance between eye and screen
    int viewport_height = 2.0;
    auto viewport_width = viewport_height *(double(img_width)/img_height);//not aespect ratio bcoz since it img_height int and wont give same AR as 16/9
    auto camera_center = point3(0,0,0);

    auto viewport_u = vec3(viewport_width, 0 ,0);
    auto viewport_v = vec3(0, -viewport_height, 0); // neg because we assume y up and in img it increses down
    auto pixel_delta_u = viewport_u / img_width;
    auto pixel_delta_v = viewport_v / img_height;
    auto viewport_upper_left = camera_center - vec3(0,0,focal_length) - viewport_u/2 - viewport_v/2;

    auto pixel_start = viewport_upper_left + 0.5*(pixel_delta_u + pixel_delta_v); //start from upper left corner in 3d co-ordinate 
    std::cout<<"P3\n"<<img_width<<" "<<img_height<<"\n255\n"<<std::endl;

    for(int j = 0; j<img_height; j++){
        std::clog << "\rScanlines remaining: " << (img_height - j) << ' ' << std::flush;
        for(int i = 0; i<img_width; i++){
            auto pixel_center = pixel_start + (i * pixel_delta_u) + (j * pixel_delta_v);// moves as i,j progress
            auto ray_direction = pixel_center - camera_center;//  direction is between pixel_center to eye
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }
    
    std::clog << "\rDone.                 \n";
}