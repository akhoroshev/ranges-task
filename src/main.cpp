#include <algorithm>
#include <iostream>
#include <vector>

using data_t = int64_t;
using point_t = std::pair<data_t, data_t>;

template <size_t dim> data_t sq_dist(const point_t &lhs, const point_t &rhs) {
  data_t diff = (std::get<dim>(lhs) - std::get<dim>(rhs));
  return diff * diff;
}

data_t sq_dist(const point_t &lhs, const point_t &rhs) {
  return sq_dist<0>(lhs, rhs) + sq_dist<1>(lhs, rhs);
}

template <typename Iter>
data_t solve(Iter begin, Iter end, std::vector<point_t> &merge_buffer) {
  const auto sz = end - begin;

  if (sz < 2) {
    return std::numeric_limits<data_t>::max();
  }

  const point_t mid_pt = *(begin + sz / 2);

  data_t ans = std::min(solve(begin, begin + sz / 2, merge_buffer),
                        solve(begin + sz / 2, end, merge_buffer));

  std::merge(begin, begin + sz / 2, begin + sz / 2, end, merge_buffer.begin(),
             [](const point_t &lhs, const point_t &rhs) {
               return lhs.second < rhs.second;
             });
  std::copy(merge_buffer.begin(), merge_buffer.begin() + sz, begin);

  const auto offset = ans;

  for (auto fit = begin; fit != end; ++fit) {
    if (sq_dist<0>(mid_pt, *fit) <= offset) {
      for (auto sit = fit + 1; sit != end && sq_dist<1>(*fit, *sit) <= offset;
           ++sit) {
        ans = std::min(ans, sq_dist(*fit, *sit));
      }
    }
  }

  return ans;
}

int main() {
  int N;
  std::cin >> N;
  std::vector<point_t> points;

  points.reserve(N);

  for (auto i = 0; i < N; i++) {
    data_t x, y;
    std::cin >> x >> y;
    points.emplace_back(point_t{x, y});
  }

  std::sort(points.begin(), points.end());

  std::vector<point_t> merge_buffer(N);
  auto res = solve(points.begin(), points.end(), merge_buffer);

  std::cout << res << std::endl;

  return 0;
}