#include <doctest/doctest.h>

#define EIGEN_INITIALIZE_MATRICES_BY_ZERO

#include <Eigen/Core>

#include <ode/iterator/fixed_step_iterator.hpp>
#include <ode/method/explicit_method.hpp>
#include <ode/problem/initial_value_problem.hpp>
#include <ode/tableau/explicit/forward_euler.hpp>

TEST_CASE("ODE Test")
{
  using method_type  = ode::explicit_method<ode::forward_euler_tableau<float>>;
  using problem_type = ode::initial_value_problem<Eigen::Vector3f, float>;

  const auto problem  = problem_type
  {
    Eigen::Vector3f(0.0f, 0.0f, 0.0f),
    0.0f,
    [ ] (const Eigen::Vector3f& y, const float h)
    {
      return Eigen::Vector3f(1.0f, 0.0f, 0.0f);
    }
  };

  auto result = method_type::evaluate(problem, 1.0f);

  REQUIRE(result[0] == 1.0f);
  REQUIRE(result[1] == 0.0f);
  REQUIRE(result[2] == 0.0f);

  auto iterator = ode::fixed_step_iterator<method_type, problem_type>(problem, 1.0f);

  iterator++;
  REQUIRE(iterator->value[0] == 1.0f);
  REQUIRE(iterator->value[1] == 0.0f);
  REQUIRE(iterator->value[2] == 0.0f);

  iterator++;
  REQUIRE(iterator->value[0] == 2.0f);
  REQUIRE(iterator->value[1] == 0.0f);
  REQUIRE(iterator->value[2] == 0.0f);
}