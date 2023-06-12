#!/bin/bash

ROOT_DIR="$1"

cat << EOF > "$ROOT_DIR/src/gui/utils/const.h"
#ifndef SIMPLEMLP_CONST_H
# define SIMPLEMLP_CONST_H

# include <string>

namespace s21 {
  namespace constant {
    const std::string letter_file = "$ROOT_DIR/build/my_letter.bmp";
    const std::string model_autosave_filename = "$ROOT_DIR/build/autosave";
    const std::string empty_file_icon_path = ":/img/empty_file.png";
  }
}

#endif
EOF