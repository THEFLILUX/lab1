#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>
#include "SpatialBase.h"
#include "Point.h"
using namespace std;

namespace utec {
namespace spatial {

/**
 * BasicSpatial implementation
 */
template <typename Point>
class BasicSpatial : public SpatialBase<Point> {
 private:
  std::vector<Point> pointVector;

 public:
  BasicSpatial() {};
  void insert(const Point& new_point) override {
    pointVector.push_back(new_point);
  }

  double ED(Point point1, Point point2){
      double result = pow((point1.get(0) - point2.get(0)), 2) + pow((point1.get(1) - point2.get(1)), 2);

      return sqrt(result);
  }

  // El punto de referencia no necesariamente es parte del dataset
  Point nearest_neighbor(const Point& reference) override {
    std::vector<pair<Point, double>> distances;
    for (auto i = pointVector.begin(); i != pointVector.end(); ++i){
      double dist = ED(reference, *i);
      distances.push_back(make_pair(*i, dist));
    }

    std::sort(distances.begin(), distances.end(), [](auto &left, auto &right) { return left.second < right.second; });

    return distances[0].first;
  }
};

}  // namespace spatial
}  // namespace utec
