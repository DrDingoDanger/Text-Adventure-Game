/**
 * @author L Nicole Wilson [n.wilson@uleth.ca]
 * @date 2022.09.10, 2024.09.13, 2026.01
 */
#ifndef PLACEBO_HPP_INCLUDED
#define PLACEBO_HPP_INCLUDED

#include <string>
/**
 * @class Placebo Placebo.hpp "Placebo.hpp"
 * @brief A placeholder class that does nothing.
 */
class Placebo {
 public:
  /**
   * @brief Default constructor
   */
  Placebo();

  /**
   * @brief Destructor
   */
  virtual ~Placebo();

  /**
   * @brief Returns a string just to have something to do.
   * @return Returns the string "Placebo-o-o!"
   */
  std::string returnPlacebo();
};

#endif //PLACEBO_HPP_INCLUDED
