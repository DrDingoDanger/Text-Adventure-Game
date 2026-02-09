/**
 * @author L Nicole Wilson [n.wilson@uleth.ca]
 * @date 2022.09.10, 2024.09.13, 2026.01
 */
#include "Placebo.hpp"

#include <iostream>
#include <string>

Placebo::Placebo() {
  std::cout << returnPlacebo() << '\n';
}

Placebo::~Placebo() {}

std::string Placebo::returnPlacebo() {
  return "Placebo-o-o!";
}
