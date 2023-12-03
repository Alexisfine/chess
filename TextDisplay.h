#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <vector>
#include "XDisplay.h"

class TextDisplay: public XDisplay {
  std::vector<std::vector<char>> theDisplay;
  const int gridSize;
 public:
  TextDisplay(int n);
  displayType disType() override;
  void notify(Cell &c) override;
  ~TextDisplay() override;
  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
